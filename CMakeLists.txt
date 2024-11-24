cmake_minimum_required(VERSION 3.20)
project(pe-debugger LANGUAGES C CXX)

if(MSVC)
  add_compile_options(
    /W4
    /Wall
  )
endif()

add_executable(pe-debugger
  WIN32
  ${CMAKE_CURRENT_SOURCE_DIR}/pe_debugger.cpp
)

target_compile_features(pe-debugger
  PRIVATE cxx_std_14
)

target_link_options(pe-debugger PRIVATE "/subsystem:console")

add_executable(pe-debuggee
  ${CMAKE_CURRENT_SOURCE_DIR}/pe_debuggee.c
)

target_compile_features(pe-debuggee
  PRIVATE c_std_11
)
