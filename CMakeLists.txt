project(screensaver.greynetic)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(Kodi REQUIRED)

if(APP_RENDER_SYSTEM STREQUAL "gl" OR NOT APP_RENDER_SYSTEM)
  find_package(OpenGL REQUIRED)
  set(DEPLIBS ${OPENGL_LIBRARIES})
  set(includes ${OPENGL_INCLUDE_DIR})
  add_definitions(-DHAS_OPENGL)
elseif(APP_RENDER_SYSTEM STREQUAL "gles")
  find_package(OpenGLES2 REQUIRED)
  set(DEPLIBS ${OPENGLES2_LIBRARIES})
  set(includes ${OPENGLES2_INCLUDE_DIR})
  add_definitions(-DHAS_GLES2)
endif()

include_directories(${includes} ${KODI_INCLUDE_DIR}/..) # Hack way with "/..", need bigger Kodi cmake rework to match right include ways

set(GREYNETIC_SOURCES src/GreyNetic.cpp)
if(NOT WIN32)
  list(APPEND GREYNETIC_SOURCES src/shaders/GUIShader.cpp
                                src/shaders/Matrix.cpp
                                src/shaders/Shader.cpp)
  set(GREYNETIC_HEADERS src/shaders/GUIShader.h
                        src/shaders/Matrix.h
                        src/shaders/Shader.h)
endif()

build_addon(screensaver.greynetic GREYNETIC DEPLIBS)

include(CPack)
