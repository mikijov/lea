cmake_minimum_required(VERSION 3.10)

project(lea VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

add_executable(lea main.cpp)
add_dependencies(lea lua)
target_link_libraries(lea lua Qt5::Widgets)

