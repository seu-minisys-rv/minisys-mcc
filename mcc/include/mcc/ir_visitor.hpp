#ifndef MCC_IR_VISITOR_HPP
#define MCC_IR_VISITOR_HPP

#include <CVisitor.h>

namespace mcc {
class Ir_visitor : public c::CVisitor {
 public:
  auto visitPrimaryExpression(c::CParser::PrimaryExpressionContext* context) -> std::any override;
  auto visitGenericSelection(c::CParser::GenericSelectionContext* context) -> std::any override;
  auto visitGenericAssocList(c::CParser::GenericAssocListContext* context) -> std::any override;
  auto visitGenericAssociation(c::CParser::GenericAssociationContext* context) -> std::any override;
  auto visitPostfixExpression(c::CParser::PostfixExpressionContext* context) -> std::any override;
  auto visitArgumentExpressionList(c::CParser::ArgumentExpressionListContext* context) -> std::any override;
  auto visitUnaryExpression(c::CParser::UnaryExpressionContext* context) -> std::any override;
  auto visitUnaryOperator(c::CParser::UnaryOperatorContext* context) -> std::any override;
  auto visitCastExpression(c::CParser::CastExpressionContext* context) -> std::any override;
  auto visitMultiplicativeExpression(c::CParser::MultiplicativeExpressionContext* context) -> std::any override;
  auto visitAdditiveExpression(c::CParser::AdditiveExpressionContext* context) -> std::any override;
  auto visitShiftExpression(c::CParser::ShiftExpressionContext* context) -> std::any override;
  auto visitRelationalExpression(c::CParser::RelationalExpressionContext* context) -> std::any override;
  auto visitEqualityExpression(c::CParser::EqualityExpressionContext* context) -> std::any override;
  auto visitAndExpression(c::CParser::AndExpressionContext* context) -> std::any override;
  auto visitExclusiveOrExpression(c::CParser::ExclusiveOrExpressionContext* context) -> std::any override;
  auto visitInclusiveOrExpression(c::CParser::InclusiveOrExpressionContext* context) -> std::any override;
  auto visitLogicalAndExpression(c::CParser::LogicalAndExpressionContext* context) -> std::any override;
  auto visitLogicalOrExpression(c::CParser::LogicalOrExpressionContext* context) -> std::any override;
  auto visitConditionalExpression(c::CParser::ConditionalExpressionContext* context) -> std::any override;
  auto visitAssignmentExpression(c::CParser::AssignmentExpressionContext* context) -> std::any override;
  auto visitAssignmentOperator(c::CParser::AssignmentOperatorContext* context) -> std::any override;
  auto visitExpression(c::CParser::ExpressionContext* context) -> std::any override;
  auto visitConstantExpression(c::CParser::ConstantExpressionContext* context) -> std::any override;
  auto visitDeclaration(c::CParser::DeclarationContext* context) -> std::any override;
  auto visitDeclarationSpecifiers(c::CParser::DeclarationSpecifiersContext* context) -> std::any override;
  auto visitDeclarationSpecifiers2(c::CParser::DeclarationSpecifiers2Context* context) -> std::any override;
  auto visitDeclarationSpecifier(c::CParser::DeclarationSpecifierContext* context) -> std::any override;
  auto visitInitDeclaratorList(c::CParser::InitDeclaratorListContext* context) -> std::any override;
  auto visitInitDeclarator(c::CParser::InitDeclaratorContext* context) -> std::any override;
  auto visitStorageClassSpecifier(c::CParser::StorageClassSpecifierContext* context) -> std::any override;
  auto visitTypeSpecifier(c::CParser::TypeSpecifierContext* context) -> std::any override;
  auto visitStructOrUnionSpecifier(c::CParser::StructOrUnionSpecifierContext* context) -> std::any override;
  auto visitStructOrUnion(c::CParser::StructOrUnionContext* context) -> std::any override;
  auto visitStructDeclarationList(c::CParser::StructDeclarationListContext* context) -> std::any override;
  auto visitStructDeclaration(c::CParser::StructDeclarationContext* context) -> std::any override;
  auto visitSpecifierQualifierList(c::CParser::SpecifierQualifierListContext* context) -> std::any override;
  auto visitStructDeclaratorList(c::CParser::StructDeclaratorListContext* context) -> std::any override;
  auto visitStructDeclarator(c::CParser::StructDeclaratorContext* context) -> std::any override;
  auto visitEnumSpecifier(c::CParser::EnumSpecifierContext* context) -> std::any override;
  auto visitEnumeratorList(c::CParser::EnumeratorListContext* context) -> std::any override;
  auto visitEnumerator(c::CParser::EnumeratorContext* context) -> std::any override;
  auto visitEnumerationConstant(c::CParser::EnumerationConstantContext* context) -> std::any override;
  auto visitAtomicTypeSpecifier(c::CParser::AtomicTypeSpecifierContext* context) -> std::any override;
  auto visitTypeQualifier(c::CParser::TypeQualifierContext* context) -> std::any override;
  auto visitFunctionSpecifier(c::CParser::FunctionSpecifierContext* context) -> std::any override;
  auto visitAlignmentSpecifier(c::CParser::AlignmentSpecifierContext* context) -> std::any override;
  auto visitDeclarator(c::CParser::DeclaratorContext* context) -> std::any override;
  auto visitDirectDeclarator(c::CParser::DirectDeclaratorContext* context) -> std::any override;
  auto visitVcSpecificModifer(c::CParser::VcSpecificModiferContext* context) -> std::any override;
  auto visitGccDeclaratorExtension(c::CParser::GccDeclaratorExtensionContext* context) -> std::any override;
  auto visitGccAttributeSpecifier(c::CParser::GccAttributeSpecifierContext* context) -> std::any override;
  auto visitGccAttributeList(c::CParser::GccAttributeListContext* context) -> std::any override;
  auto visitGccAttribute(c::CParser::GccAttributeContext* context) -> std::any override;
  auto visitNestedParenthesesBlock(c::CParser::NestedParenthesesBlockContext* context) -> std::any override;
  auto visitPointer(c::CParser::PointerContext* context) -> std::any override;
  auto visitTypeQualifierList(c::CParser::TypeQualifierListContext* context) -> std::any override;
  auto visitParameterTypeList(c::CParser::ParameterTypeListContext* context) -> std::any override;
  auto visitParameterList(c::CParser::ParameterListContext* context) -> std::any override;
  auto visitParameterDeclaration(c::CParser::ParameterDeclarationContext* context) -> std::any override;
  auto visitIdentifierList(c::CParser::IdentifierListContext* context) -> std::any override;
  auto visitTypeName(c::CParser::TypeNameContext* context) -> std::any override;
  auto visitAbstractDeclarator(c::CParser::AbstractDeclaratorContext* context) -> std::any override;
  auto visitDirectAbstractDeclarator(c::CParser::DirectAbstractDeclaratorContext* context) -> std::any override;
  auto visitTypedefName(c::CParser::TypedefNameContext* context) -> std::any override;
  auto visitInitializer(c::CParser::InitializerContext* context) -> std::any override;
  auto visitInitializerList(c::CParser::InitializerListContext* context) -> std::any override;
  auto visitDesignation(c::CParser::DesignationContext* context) -> std::any override;
  auto visitDesignatorList(c::CParser::DesignatorListContext* context) -> std::any override;
  auto visitDesignator(c::CParser::DesignatorContext* context) -> std::any override;
  auto visitStaticAssertDeclaration(c::CParser::StaticAssertDeclarationContext* context) -> std::any override;
  auto visitStatement(c::CParser::StatementContext* context) -> std::any override;
  auto visitLabeledStatement(c::CParser::LabeledStatementContext* context) -> std::any override;
  auto visitCompoundStatement(c::CParser::CompoundStatementContext* context) -> std::any override;
  auto visitBlockItemList(c::CParser::BlockItemListContext* context) -> std::any override;
  auto visitBlockItem(c::CParser::BlockItemContext* context) -> std::any override;
  auto visitExpressionStatement(c::CParser::ExpressionStatementContext* context) -> std::any override;
  auto visitSelectionStatement(c::CParser::SelectionStatementContext* context) -> std::any override;
  auto visitIterationStatement(c::CParser::IterationStatementContext* context) -> std::any override;
  auto visitForCondition(c::CParser::ForConditionContext* context) -> std::any override;
  auto visitForDeclaration(c::CParser::ForDeclarationContext* context) -> std::any override;
  auto visitForExpression(c::CParser::ForExpressionContext* context) -> std::any override;
  auto visitJumpStatement(c::CParser::JumpStatementContext* context) -> std::any override;
  auto visitCompilationUnit(c::CParser::CompilationUnitContext* context) -> std::any override;
  auto visitTranslationUnit(c::CParser::TranslationUnitContext* context) -> std::any override;
  auto visitExternalDeclaration(c::CParser::ExternalDeclarationContext* context) -> std::any override;
  auto visitFunctionDefinition(c::CParser::FunctionDefinitionContext* context) -> std::any override;
  auto visitDeclarationList(c::CParser::DeclarationListContext* context) -> std::any override;
};
}  // namespace mcc

#endif