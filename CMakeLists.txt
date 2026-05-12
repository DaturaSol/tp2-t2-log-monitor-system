# CmakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(LogMonitor 
  VERSION 1.0 
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_COVERAGE "Enable code coverage instrumentation" ON)

if(ENABLE_COVERAGE)
    message(STATUS "Build with Coverage enabled")
    add_compile_options(--coverage -fprofile-arcs -ftest-coverage)
    add_link_options(--coverage -fprofile-arcs -ftest-coverage)
else()
    message(STATUS "Build for Performance (No Coverage)")
endif()


if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Build with DEBUG type")
    set(CMAKE_BUILD_TYPE Debug)
endif()


add_subdirectory(src)

enable_testing()
add_subdirectory(tests)


file(GLOB_RECURSE ALL_CXX_SOURCE_FILES 
    "src/*.cpp" "include/*.hpp" "tests/*.cpp"
)

add_custom_target(format
    COMMAND clang-format -i ${ALL_CXX_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Formatting code with clang-format..."
)

add_custom_target(cppcheck
    COMMAND cppcheck --enable=warning ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running cppcheck..."
)

add_custom_target(cpplint
    COMMAND cpplint --filter=-legal/copyright ${ALL_CXX_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running cpplint..."
)

add_custom_target(doxygen
    COMMAND doxygen doxygen.conf
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
    COMMENT "Generating Doxygen documentation..."
)