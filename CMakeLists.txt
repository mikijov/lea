# Lea - Lightweight UI for your tools.
# Copyright (C) 2022   Milutin Jovanović
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.10)

project(lea VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Suggest you run:
      cmake -H. -B${CMAKE_SOURCE_DIR}/build"
      )
endif ()

if( CMAKE_COMPILER_IS_GNUCC )
        set( CMAKE_C_FLAGS
                "${CMAKE_C_FLAGS} -std=c17 -pedantinc -Wall -fmessage-length=0" )
        message( STATUS "Setting GNUCC flags:" ${CMAKE_C_FLAGS} )
endif( CMAKE_COMPILER_IS_GNUCC )
if( CMAKE_COMPILER_IS_GNUCXX )
        set( CMAKE_CXX_FLAGS
                "${CMAKE_CXX_FLAGS} -std=c++17 -pedantic -Wall -fmessage-length=0" )
        message( STATUS "Setting GNUCXX flags:" ${CMAKE_CXX_FLAGS} )
endif( CMAKE_COMPILER_IS_GNUCXX )

include(ExternalProject)

# dP
# 88
# 88        dP    dP .d8888b.
# 88        88    88 88'  `88
# 88        88.  .88 88.  .88
# 88888888P `88888P' `88888P8

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

# dP                           888888ba           oo       dP                   d8888b.
# 88                           88    `8b                   88                       `88
# 88        dP    dP .d8888b. a88aaaa8P' 88d888b. dP .d888b88 .d8888b. .d8888b.  aaad8'
# 88        88    88 88'  `88  88   `8b. 88'  `88 88 88'  `88 88'  `88 88ooood8     `88
# 88        88.  .88 88.  .88  88    .88 88       88 88.  .88 88.  .88 88.  ...     .88
# 88888888P `88888P' `88888P8  88888888P dP       dP `88888P8 `8888P88 `88888P' d88888P
#                                                                  .88
#                                                              d8888P

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

#            dP   dP
#            88   88
# .d8888b. d8888P 88  .dP  88d8b.d8b. 88d8b.d8b.
# 88'  `88   88   88888"   88'`88'`88 88'`88'`88
# 88.  .88   88   88  `8b. 88  88  88 88  88  88
# `8888P88   dP   dP   `YP dP  dP  dP dP  dP  dP
#      .88
#  d8888P

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
# include_directories(${GTK_INCLUDE_DIRS})
# link_directories(${GTK_LIBRARY_DIRS})
# add_definitions(${GTK_CFLAGS_OTHER})
# list(JOIN GTKMM_INCLUDE_DIRS "," MSG)
# message(WARNING "includes:" ${MSG})
# list(JOIN GTKMM_LIBRARIES "," MSG)
# message(WARNING "libs:" ${MSG})

# dP oo dP                           dP   oo .8888b
# 88    88                           88      88   "
# 88 dP 88d888b. 88d888b. .d8888b. d8888P dP 88aaa  dP    dP
# 88 88 88'  `88 88'  `88 88'  `88   88   88 88     88    88
# 88 88 88.  .88 88    88 88.  .88   88   88 88     88.  .88
# dP dP 88Y8888' dP    dP `88888P'   dP   dP dP     `8888P88
#                                                        .88
#                                                    d8888P

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

# dP
# 88
# 88        .d8888b. .d8888b.
# 88        88ooood8 88'  `88
# 88        88.  ... 88.  .88
# 88888888P `88888P' `88888P8

add_executable(lea
  src/main.cpp
  src/lea.hpp
  src/lea.cpp
  src/lea_config.hpp
  src/lea_config.cpp
  src/lea_tray.hpp
  src/lea_tray.cpp
  src/lea_icon.hpp
  src/lea_icon.cpp
  src/lea_notification.hpp
  src/lea_notification.cpp
  src/lea_timer.hpp
  src/lea_timer.cpp
  src/lea_menu.hpp
  src/lea_menu.cpp
  )
add_dependencies(lea lua)
# target_link_libraries(foo PUBLIC ${GLIB_LIBRARIES})
target_include_directories(lea PUBLIC ${GTKMM_INCLUDE_DIRS})
target_link_libraries(lea lua ${GTKMM_LIBRARIES})
target_compile_options(lea PRIVATE "-Wno-deprecated-declarations")

# add_subdirectory( doxygen )
