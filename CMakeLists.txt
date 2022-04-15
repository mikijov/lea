cmake_minimum_required(VERSION 3.10)

project(lea VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
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

ExternalProject_Add(
  project_LuaBridge3
  GIT_REPOSITORY "https://github.com/kunitoki/LuaBridge3"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  BUILD_ALWAYS true
  BUILD_IN_SOURCE true
  INSTALL_COMMAND ""
)
ExternalProject_Get_property(project_LuaBridge3 SOURCE_DIR)
# list(JOIN SOURCE_DIR "," MSG)
# message(WARNING "includes:" ${MSG})
include_directories(${SOURCE_DIR}/Distribution/LuaBridge)

# find_package(GTK2 2.24 REQUIRED gtk gtkmm)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
# include_directories(${GTK_INCLUDE_DIRS})
# link_directories(${GTK_LIBRARY_DIRS})
# add_definitions(${GTK_CFLAGS_OTHER})

# find_package(PkgConfig REQUIRED)
# pkg_check_modules(LIBNOTIFY QUIET libnotify)
# find_path(LIBNOTIFY_INCLUDE_DIRS
#     NAMES notify.h
#     HINTS ${LIBNOTIFY_INCLUDEDIR}
#           ${LIBNOTIFY_INCLUDE_DIRS}
#     PATH_SUFFIXES libnotify
# )
# find_library(LIBNOTIFY_LIBRARIES
#     NAMES notify
#     HINTS ${LIBNOTIFY_LIBDIR}
#           ${LIBNOTIFY_LIBRARY_DIRS}
# )
# include(FindPackageHandleStandardArgs)
# FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibNotify
#   REQUIRED_VARS LIBNOTIFY_INCLUDE_DIRS LIBNOTIFY_LIBRARIES
#   VERSION_VAR LIBNOTIFY_VERSION)
# mark_as_advanced(
#     LIBNOTIFY_INCLUDE_DIRS
#     LIBNOTIFY_LIBRARIES
# )
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)


list(JOIN GTKMM_INCLUDE_DIRS "," MSG)
message(WARNING "includes:" ${MSG})
list(JOIN GTKMM_LIBRARIES "," MSG)
message(WARNING "libs:" ${MSG})

add_executable(lea
  main.cpp
  lea.cpp
  lea_tray.cpp
  lea_icon.cpp
  lea_notification.cpp
  lea_timer.cpp
  lea_menu.cpp
  )
add_dependencies(lea lua)
# target_link_libraries(foo PUBLIC ${GLIB_LIBRARIES})
target_include_directories(lea PUBLIC ${GTKMM_INCLUDE_DIRS})
target_link_libraries(lea lua ${GTKMM_LIBRARIES})
target_compile_options(lea PRIVATE "-Wno-deprecated-declarations")
