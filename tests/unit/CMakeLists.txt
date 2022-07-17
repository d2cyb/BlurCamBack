message(STATUS "Unit Tests enabled")

set(UNIT_TESTS_PROJECT_NAME ${PROJECT_NAME}_unit)

find_package(Catch2 CONFIG REQUIRED)

set(UNIT_TESTS_SRC
    ${PROJECT_SOURCE_DIR}/tests/unit/BlurVideo.test.cpp
)

add_executable(${UNIT_TESTS_PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/tests/tests-main.cpp
    ${UNIT_TESTS_SRC}
)

target_link_libraries(${UNIT_TESTS_PROJECT_NAME} PRIVATE
    ${APP_LIBRARY_NAME}
    Catch2::Catch2
)

get_target_property(linked_libraries ${UNIT_TESTS_PROJECT_NAME} LINK_LIBRARIES)
message(STATUS "Unit test linked libraries: ${linked_libraries}")

include(CTest)
include(Catch)
catch_discover_tests(${UNIT_TESTS_PROJECT_NAME})
