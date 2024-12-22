cmake_minimum_required(VERSION 3.10)

# Set project name and language
project(coral_jni)

# Include paths

# Source files
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../coral/src/main/native/cpp/coral_jni.cpp)

# Shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Link libcoral and dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE edgetpu coral tensorflow-lite)
