# tests/CMakeLists.txt
find_package(GTest REQUIRED)

add_executable(log_test TestMonitor.cpp)

target_link_libraries(log_test PRIVATE 
    GTest::gtest_main 
    pthread 
    monitor_core
)

add_test(NAME MonitoraTests COMMAND log_test)

add_custom_target(valgrind
    COMMAND valgrind --leak-check=full $<TARGET_FILE:log_test>
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running Valgrind on tests..."
)

target_compile_options(log_test PRIVATE --coverage -fprofile-arcs -ftest-coverage)
target_link_options(log_test PRIVATE --coverage -fprofile-arcs -ftest-coverage)
target_compile_options(monitor_core PRIVATE --coverage -fprofile-arcs -ftest-coverage)
target_link_options(monitor_core PRIVATE --coverage -fprofile-arcs -ftest-coverage)

add_custom_target(coverage
    COMMAND gcov ${CMAKE_SOURCE_DIR}/src/core/*.cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating gcov coverage reports..."
)