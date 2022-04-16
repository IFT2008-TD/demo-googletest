

set(TEST_SOURCES test_tugabudoire.cpp ${PROJECT_SOURCE_DIR}/Tugabudoire.cpp ${PROJECT_SOURCE_DIR}/Tugabudoire.h)

add_executable(
       test_tugabudoire
       ${TEST_SOURCES}
)

target_include_directories(test_tugabudoire PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
       test_tugabudoire
        gtest_main
        gtest
        pthread
)

include(GoogleTest)
gtest_discover_tests(test_tugabudoire)