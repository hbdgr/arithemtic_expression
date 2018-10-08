file(GLOB test_sources "*.cpp")

# tests with catch2
set(test_name "tests")
add_executable(${test_name} ${test_sources})

target_link_libraries(${test_name} Catch2::Catch2 my_lib)
add_test (NAME all_tests COMMAND ${test_name})
