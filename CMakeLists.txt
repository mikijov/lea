cmake_minimum_required(VERSION 3.10)

include(ExternalProject)

ExternalProject_Add(
  project_lua
  URL "https://www.lua.org/ftp/lua-5.4.4.tar.gz"
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/lua-5.4.4
  CONFIGURE_COMMAND ""
  BUILD_COMMAND make all test
  BUILD_ALWAYS true
  BUILD_IN_SOURCE true
  INSTALL_COMMAND make install INSTALL_TOP=${CMAKE_CURRENT_BINARY_DIR}/install
)
ExternalProject_Get_property(project_lua SOURCE_DIR)
add_library(lua STATIC IMPORTED)
set_property(TARGET lua PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/install/lib/liblua.a)
add_dependencies(lua project_lua)

project(lea)
set(CMAKE_C_STANDARD 11)
add_executable(lea main.cpp)
add_dependencies(lea lua)
target_link_libraries(lea lua)

