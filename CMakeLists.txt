cmake_minimum_required(VERSION 3.20)

project(app)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StartingApp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WorkingWithClass.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/StartingApp.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WorkingWithClass.hpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)

set(CMAKE_BUILD_TYPE Debug)

if(ENABLE_DEBUG)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g)
endif()

add_custom_target(
    clang-format
    COMMAND clang-format
    --dry-run
    -Werror
    ${SOURCES}
    ${HEADERS}
)
