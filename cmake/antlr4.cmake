# - A wrapper for antlr4
# The antlr4 conan recipe dosen't import antlr4 executable. This fixes that problem.
include_guard(GLOBAL)

find_package(antlr4 CONFIG REQUIRED)

if(DEFINED antlr4_PACKAGE_FOLDER_DEBUG)
  set(antlr4_path ${antlr4_PACKAGE_FOLDER_DEBUG})
else()
  set(antlr4_path ${antlr4_PACKAGE_FOLDER_RELEASE})
endif()

if(DEFINED openjdk_BIN_DIRS_DEBUG)
  set(java_path ${openjdk_BIN_DIRS_DEBUG})
else()
  set(java_path ${openjdk_BIN_DIRS_RELEASE})
endif()

function(add_antlr4 target_name grammar_file)
  set(options)
  set(one_value_args PACKAGE_NAME)
  set(multi_value_args)
  cmake_parse_arguments(_add_antlr4 "${options}" "${one_value_args}" "${multi_value_args}" "${ARGN}")

  if(_add_antlr4_PACKAGE_NAME)
    set(package_name_arg -package ${_add_antlr4_PACKAGE_NAME})
  endif()

  set(output_dir ${CMAKE_BINARY_DIR}/_antlr/${target_name})
  cmake_path(GET grammar_file STEM grammar_name)

  add_custom_command(
    OUTPUT "${output_dir}/${grammar_name}Lexer.cpp" "${output_dir}/${grammar_name}Parser.cpp"
    COMMAND
      ${java_path}/java -classpath ${antlr4_path}/res/antlr-complete.jar org.antlr.v4.Tool
      -encoding UTF-8
      -Dlanguage=Cpp
      ${package_name_arg}
      -no-listener
      -visitor ${grammar_file}
      -o ${output_dir}
    DEPENDS ${grammar_file}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )

  add_library(${target_name})
  target_include_directories(${target_name}
    PUBLIC
    ${output_dir}
  )
  target_sources(${target_name}
    PRIVATE
    "${output_dir}/${grammar_name}Lexer.cpp"
    "${output_dir}/${grammar_name}Parser.cpp"
  )
  target_find_dependencies(${target_name}
    PUBLIC_CONFIG
    antlr4-runtime
  )
  target_link_libraries(${target_name}
    PUBLIC
    antlr4_static
  )
endfunction()
