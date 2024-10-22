#include "BreadLexer.h"
#include "BreadParser.h"
#include "BreadVisitor.h"

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/IRBuilder.h>

namespace {
// NOLINTBEGIN(*non-const-global*)
std::unique_ptr<llvm::LLVMContext> llvm_context;
std::unique_ptr<llvm::IRBuilder<>> builder;
std::unique_ptr<llvm::Module> mod;

std::map<std::string, llvm::Function*> functable;
std::map<std::string, llvm::Value*> local_vars;
// NOLINTEND(*non-const-global*)

class Ir_visitor : public bread::BreadVisitor {
 public:
  auto visitProg(bread::BreadParser::ProgContext* context) -> std::any override {
    for (auto const& it : context->func()) {
      it->accept(this);
    }

    return 0;
  }

  auto visitDiv(bread::BreadParser::DivContext* context) -> std::any override {
    return builder->CreateSDiv(std::any_cast<llvm::Value*>(context->left->accept(this)),
                               std::any_cast<llvm::Value*>(context->right->accept(this)));
  }

  auto visitAdd(bread::BreadParser::AddContext* context) -> std::any override {
    return builder->CreateAdd(std::any_cast<llvm::Value*>(context->left->accept(this)),
                              std::any_cast<llvm::Value*>(context->right->accept(this)));
  }

  auto visitSub(bread::BreadParser::SubContext* context) -> std::any override {
    return builder->CreateSub(std::any_cast<llvm::Value*>(context->left->accept(this)),
                              std::any_cast<llvm::Value*>(context->right->accept(this)));
  }

  auto visitBrack(bread::BreadParser::BrackContext* context) -> std::any override {
    return context->expr()->accept(this);
  }

  auto visitMul(bread::BreadParser::MulContext* context) -> std::any override {
    return builder->CreateMul(std::any_cast<llvm::Value*>(context->left->accept(this)),
                              std::any_cast<llvm::Value*>(context->right->accept(this)));
  }

  auto visitLit(bread::BreadParser::LitContext* context) -> std::any override {
    int value{std::stoi(context->INT()->getSymbol()->getText())};
    auto i32{builder->getInt32Ty()};
    return reinterpret_cast<llvm::Value*>(  // NOLINT(*reinterpret-cast*)
        llvm::ConstantInt::get(i32, static_cast<std::uint64_t>(value)));
  }

  // Function call support

  auto visitFunc(bread::BreadParser::FuncContext* context) -> std::any override {
    local_vars.clear();

    context->prot()->accept(this);

    for (auto const& it : context->expr()) {
      it->accept(this);
    }

    return 0;
  }

  auto visitProt(bread::BreadParser::ProtContext* context) -> std::any override {
    auto argl{
        std::any_cast<std::pair<std::vector<llvm::Type*>, std::vector<std::string>>>(context->argl()->accept(this))};
    auto fname{context->name->getText()};

    auto i32{builder->getInt32Ty()};
    auto prototype{llvm::FunctionType::get(i32, argl.first, false)};
    llvm::Function* fn{llvm::Function::Create(prototype, llvm::Function::ExternalLinkage, fname, mod.get())};
    llvm::BasicBlock* body{llvm::BasicBlock::Create(*llvm_context, "body", fn)};
    builder->SetInsertPoint(body);

    functable[fname] = fn;

    // Set up arguments as local variables

    int i{};
    for (auto const& it : argl.second) {
      local_vars[it]
          = reinterpret_cast<llvm::Value*>(fn->getArg(static_cast<unsigned int>(i)));  // NOLINT(*reinterpret-cast*)
      i++;
    }

    return 0;
  }

  auto visitArgl(bread::BreadParser::ArglContext* context) -> std::any override {
    std::pair<std::vector<llvm::Type*>, std::vector<std::string>> ret;

    for (auto const& it : context->SYMNAME()) {
      ret.first.push_back(builder->getInt32Ty());
      ret.second.push_back(it->getSymbol()->getText());
    }

    return ret;
  }

  auto visitCall(bread::BreadParser::CallContext* context) -> std::any override {
    auto func{functable[context->name->getText()]};

    std::vector<llvm::Value*> args;

    std::cout << "Call to " << context->name->getText() << " has " << context->expr().size() << " args\n";

    for (auto const& it : context->expr()) {
      args.push_back(std::any_cast<llvm::Value*>(it->accept(this)));
    }

    return reinterpret_cast<llvm::Value*>(builder->CreateCall(func, args));  // NOLINT(*reinterpret-cast*)
  }

  auto visitRet(bread::BreadParser::RetContext* context) -> std::any override {
    builder->CreateRet(std::any_cast<llvm::Value*>(context->expr()->accept(this)));

    return 0;
  }

  auto visitAss(bread::BreadParser::AssContext* context) -> std::any override {
    if (local_vars.find(context->name->getText()) == local_vars.end()) {
      std::cout << "Assigning to undeclared variable " << context->name->getText() << " is not allowed.\n";
      std::exit(EXIT_FAILURE);  // NOLINT(*mt-unsafe*)
    }

    local_vars[context->name->getText()] = std::any_cast<llvm::Value*>(context->expr()->accept(this));

    return local_vars[context->name->getText()];
  }

  auto visitVar(bread::BreadParser::VarContext* context) -> std::any override {
    if (local_vars.find(context->name->getText()) == local_vars.end()) {
      std::cout << "Accessing to undeclared variable " << context->name->getText() << " is not allowed.\n";
      std::exit(EXIT_FAILURE);  // NOLINT(*mt-unsafe*)
    }

    return local_vars[context->name->getText()];
  }

  auto visitDecl(bread::BreadParser::DeclContext* context) -> std::any override {
    // We assign the element in the map to null to indicate that the variable has been declared.
    // The assignment expression checks that the variable has been declared by performing a find()
    // over the local variable map.
    local_vars[context->name->getText()] = nullptr;

    return 0;
  }
};
}  // namespace

auto main(int argc, char const* argv[]) -> int {
  if (argc != 2) {
    std::cerr << "Usage: sample <bread_source_file>\n";
    std::exit(EXIT_FAILURE);  // NOLINT(*mt-unsafe*)
  }

  std::ifstream stream{argv[1]};  // NOLINT(*bounds-pointer-arithmetic*)

  antlr4::ANTLRInputStream input{stream};
  bread::BreadLexer lexer{&input};
  antlr4::CommonTokenStream tokens{&lexer};
  bread::BreadParser parser{&tokens};
  bread::BreadParser::ProgContext* tree{parser.prog()};

  llvm_context = std::make_unique<llvm::LLVMContext>();
  builder      = std::make_unique<llvm::IRBuilder<>>(*llvm_context);
  mod          = std::make_unique<llvm::Module>("hello", *llvm_context);

  Ir_visitor irv;
  irv.visitProg(tree);

  std::cout << "Running built LLVM IR...\n";

  llvm::ExecutionEngine* execution_engine{
      llvm::EngineBuilder(std::move(mod)).setEngineKind(llvm::EngineKind::Interpreter).create()};
  llvm::Function* main{execution_engine->FindFunctionNamed(llvm::StringRef("main"))};
  auto result{execution_engine->runFunction(main, {})};

  std::cout << result.IntVal.getLimitedValue() << "\n";

  return 0;
}