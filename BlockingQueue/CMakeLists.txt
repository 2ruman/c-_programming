
cmake_minimum_required(VERSION 3.0) # Local cmake version is 3.22.1 though

project(BlockingQueue)

set(PROGRAM_NAME ${PROJECT_NAME}_TEST)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # To generate compile_commands.json file

file(GLOB SRC_FILES CONFIGURE_DEPENDS # Use GLOB_RECURSE instead for recursive search
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

foreach(SRC_FILE ${SRC_FILES})
  message("SRC_FILE : " ${SRC_FILE})
endforeach()

add_executable(${PROGRAM_NAME} ${SRC_FILES})

target_link_libraries(${PROGRAM_NAME} PRIVATE pthread) # Equivalent to "-pthread" flag for unix-like OS