add_antlr4(c_grammar C.g4 PACKAGE_NAME c)

# Library part
add_library(mcc_library STATIC)
target_sources(mcc_library
  PRIVATE
  src/mcc_main.cpp

  src/ir_visitor.cpp
)
target_include_interface_directories(mcc_library include)
target_link_libraries(mcc_library
  PRIVATE
  mcc_project_options
  mcc_project_warnings
)

target_link_system_libraries(mcc_library
  PUBLIC
  mcc_project_options
  mcc_project_warnings
  c_grammar
  llvm::llvm
)

# Executable part
add_executable(mcc)
target_sources(mcc
  PRIVATE
  src/main.cpp
)
target_link_libraries(mcc
  PRIVATE
  mcc_library
  mcc_project_options
  mcc_project_warnings
)

# Tests
if(mcc_BUILD_TESTING)
  add_subdirectory(test)
endif()