add_antlr4(bread_grammar Bread.g4 PACKAGE_NAME bread)

# Executable part
add_executable(sample)
target_sources(sample
  PRIVATE
  src/main.cpp
)
target_link_libraries(sample
  PRIVATE
  mcc_project_options
  mcc_project_warnings
  bread_grammar
  llvm::llvm
)

# Tests
if(mcc_BUILD_TESTING)
  add_subdirectory(test)
endif()