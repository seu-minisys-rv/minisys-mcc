cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(fix_msvc)
include(mcc_options)
include(mcc_fetch_project_options)

project(mcc VERSION 1.0.0 LANGUAGES C CXX)

# Propagate customized project_options. That is,
# - Some global project settings like default C++ version and so on.
# - `mcc_project_options` and `mcc_project_warnings` interface libraries that contain C++ options
include(mcc_custom_project_options)

# workaround: RPATH stuff
# !!!NOT RECOMMENDED!!! see https://github.com/ossf/wg-best-practices-os-developers/blob/main/docs/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C%2B%2B.md
include(rpath)

include(llvm)
include(antlr4)

if(mcc_BUILD_TESTING)
  # Include CTest before any tests
  include(CTest)

  # Add handy test wrappers
  include(add_test)

  # Common test config
  add_test_config(common
    DEPENDENCIES_CONFIG
    Catch2

    LIBRARIES
    mcc_project_options
    mcc_project_warnings

    SYSTEM_LIBRARIES
    Catch2::Catch2WithMain

    EXECUTE_ARGS
    --reporter xml
  )
endif()

# Add src
add_subdirectory(mcc)
add_subdirectory(sample)

# Package the project
# for products, using `package_project(TARGETS app)` to pack the executable should be enough
package_project(
  TARGETS
  mcc
  sample
  mcc_project_options
  mcc_project_warnings
)

detect_architecture(arch)
set(CPACK_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${arch}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)

include(CPack)