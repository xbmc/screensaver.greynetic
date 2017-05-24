project(screensaver.greynetic)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(Kodi REQUIRED)

include_directories(${KODI_INCLUDE_DIR}/..) # Hack way with "/..", need bigger Kodi cmake rework to match right include ways

set(GREYNETIC_SOURCES src/GreyNetic.cpp)

set(DEPLIBS)

build_addon(screensaver.greynetic GREYNETIC DEPLIBS)

include(CPack)
