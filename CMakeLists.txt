cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(h3r VERSION 0.1.0 LANGUAGES C)

include(cmake/warnings.cmake)
include(cmake/sanitizers.cmake)
include(cmake/CPM.cmake)

cpmaddpackage("gh:EBI-Metagenomics/lip@0.5.2")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

file(GLOB H3R_SOURCES "*.c")
file(GLOB H3R_HEADERS "*.h")
list(FILTER H3R_SOURCES EXCLUDE REGEX "test_.*")
list(FILTER H3R_HEADERS EXCLUDE REGEX "test_.*")

add_library(h3r ${H3R_SOURCES})
add_library(H3R::h3r ALIAS h3r)
target_link_libraries(h3r PRIVATE LIP::lip)
target_link_libraries(h3r INTERFACE $<$<BOOL:${UNIX}>:m>)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/h3r)
file(COPY ${H3R_HEADERS} DESTINATION ${PROJECT_BINARY_DIR}/h3r)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(h3r PUBLIC -DH3R_STATIC_DEFINE)
endif()

target_include_directories(
  h3r
  PUBLIC $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
         $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  PRIVATE ${PROJECT_SOURCE_DIR}
)

set_target_properties(h3r PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(h3r PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

install(
  TARGETS h3r
  EXPORT h3r-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
install(DIRECTORY ${PROJECT_BINARY_DIR}/h3r DESTINATION include)

export(
  TARGETS h3r
  NAMESPACE H3R::
  FILE h3r-targets.cmake)
install(
  EXPORT h3r-targets
  NAMESPACE H3R::
  DESTINATION lib/cmake/h3r)

install(
  FILES ${PROJECT_SOURCE_DIR}/README.md ${PROJECT_SOURCE_DIR}/LICENSE
  DESTINATION share/docs/h3r)

include(CMakePackageConfigHelpers)
set(PROJECT_CONFIG ${PROJECT_BINARY_DIR}/h3r-config.cmake)
set(VERSION_CONFIG ${PROJECT_BINARY_DIR}/h3r-config-version.cmake)
configure_package_config_file(h3r-config.cmake.in ${PROJECT_CONFIG}
                              INSTALL_DESTINATION lib/cmake/h3r)
write_basic_package_version_file(${VERSION_CONFIG}
                                 COMPATIBILITY SameMajorVersion)
install(FILES ${PROJECT_CONFIG} ${VERSION_CONFIG} DESTINATION lib/cmake/h3r)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  enable_testing()
  file(GLOB H3R_TEST_SOURCES "test_*.c")
  file(COPY h3r.mp DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  foreach(source ${H3R_TEST_SOURCES})
    get_filename_component(x ${source} NAME_WE)
    add_executable(${x} ${source})
    target_link_libraries(${x} PRIVATE h3r)
    target_link_libraries(${x} PRIVATE LIP::lip)
    add_test(NAME ${x} COMMAND ${x} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  endforeach()
endif()
