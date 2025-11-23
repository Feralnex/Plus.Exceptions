cmake_minimum_required(VERSION 3.26)
project(Plus.Exceptions)

# CMakeLists.txt
set(CMAKE_CXX_STANDARD 20)

# Fetch the Plus library from GitHub
include(FetchContent)
FetchContent_Declare(
  Plus
  GIT_REPOSITORY https://github.com/Feralnex/Plus.git
  GIT_TAG master
)
FetchContent_MakeAvailable(Plus)

# Add your source files
set(SOURCES
    Source/Error.cpp
)

# Create the library
add_library(Exceptions SHARED ${SOURCES})

# Include directories from Plus library
target_include_directories(Exceptions PRIVATE ${plus_SOURCE_DIR})
