message(STATUS "Benchmark Tests enabled")

set(BENCHMARK_TESTS_PROJECT_NAME ${PROJECT_NAME}_bench)

find_package(Catch2 CONFIG REQUIRED)

set(UNIT_TESTS_SRC
    ${PROJECT_SOURCE_DIR}/tests/perf/BlurVideo.perf.test.cpp
)

add_executable(${BENCHMARK_TESTS_PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/tests/tests-main.cpp
    ${UNIT_TESTS_SRC}
)

target_link_libraries(${BENCHMARK_TESTS_PROJECT_NAME} PRIVATE
    ${APP_LIBRARY_NAME}
    Catch2::Catch2
)

get_target_property(linked_libraries ${BENCHMARK_TESTS_PROJECT_NAME} LINK_LIBRARIES)
message(STATUS "Benckmark linked libraries: ${linked_libraries}")

include(CTest)
include(Catch)
catch_discover_tests(${BENCHMARK_TESTS_PROJECT_NAME})
