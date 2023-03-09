
cmake_minimum_required(VERSION 3.0) # Local cmake version is 3.22.1

project(BlockingQueue)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES CONFIGURE_DEPENDS # GLOB_RECURSE for recursive search
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

message("SRC_FILE : " ${SRC_FILES})

add_executable(${PROJECT_NAME}_TEST ${SRC_FILES})

