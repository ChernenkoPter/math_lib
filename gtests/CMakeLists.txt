include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME}_tests ${TEST_FILES})

enable_testing()
target_link_libraries(${PROJECT_NAME}_tests PRIVATE GTest::gtest_main)
target_include_directories(${PROJECT_NAME}_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_NAME}_tests PRIVATE WITH_TESTS)
target_compile_features(${PROJECT_NAME}_tests PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)