# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# src_sources at src/CMakeLists.txt:5 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS 225/cs225-final-project-fa22/src/*.cpp")
set(OLD_GLOB
  "/workspaces/CS 225/cs225-final-project-fa22/src/algorithms.cpp"
  "/workspaces/CS 225/cs225-final-project-fa22/src/transit.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS 225/cs225-final-project-fa22/build/CMakeFiles/cmake.verify_globs")
endif()

# src_sources at src/CMakeLists.txt:5 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS 225/cs225-final-project-fa22/src/*.h")
set(OLD_GLOB
  "/workspaces/CS 225/cs225-final-project-fa22/src/algorithms.h"
  "/workspaces/CS 225/cs225-final-project-fa22/src/transit.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS 225/cs225-final-project-fa22/build/CMakeFiles/cmake.verify_globs")
endif()

# tests_src at CMakeLists.txt:131 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS 225/cs225-final-project-fa22/tests/*.cpp")
set(OLD_GLOB
  "/workspaces/CS 225/cs225-final-project-fa22/tests/tests.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS 225/cs225-final-project-fa22/build/CMakeFiles/cmake.verify_globs")
endif()