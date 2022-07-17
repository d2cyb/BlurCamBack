cmake_minimum_required(VERSION 3.2)

project(BlurCamBack
        VERSION 0.0.1
        LANGUAGES CXX)

# build output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# compiller settings
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)
find_package(fmt)

if (NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
    add_compile_definitions(SPDLOG_FMT_EXTERNAL)
endif()

set(APP_EXECUTABLE_NAME ${PROJECT_NAME})
set(APP_LIBRARY_NAME ${PROJECT_NAME}_LIB)

set(APP_INC
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/BlurVideo.hpp
)
source_group(include FILES ${APP_INC})

set(APP_SRC
    ${PROJECT_SOURCE_DIR}/src/BlurVideo.cpp
)
source_group(src FILES ${APP_SRC})

add_executable(${APP_EXECUTABLE_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)
add_library(${APP_LIBRARY_NAME} ${APP_SRC} ${APP_INC})

include_directories(
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${OpenCV_INCLUDE_DIRS}
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${APP_LIBRARY_NAME} PRIVATE
    ${OpenCV_LIBS}
    fmt::fmt
    spdlog::spdlog
)

target_link_libraries(${APP_EXECUTABLE_NAME} PRIVATE
   ${APP_LIBRARY_NAME}
)

message(STATUS "Compiler is ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

if (MSVC)
    target_compile_options(${APP_EXECUTABLE_NAME} PRIVATE
        /W4
    )
    target_compile_options(${APP_LIBRARY_NAME} PRIVATE
        /W4
    )
else ()
    target_compile_options(${APP_EXECUTABLE_NAME} PRIVATE
        -Wall -Wextra -Werror -pedantic
    )
    target_compile_options(${APP_LIBRARY_NAME} PRIVATE
        -Wall -Wextra -Werror -pedantic
    )
endif()


install(TARGETS ${APP_EXECUTABLE_NAME} RUNTIME DESTINATION bin)

# LINTS
set(ENABLE_TIDY_CHECK ON)
find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
if (ENABLE_TIDY_CHECK)
    if(NOT CLANG_TIDY_COMMAND)
        message(WARNING "Could not find clang-tidy!")
        set(CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE)
    else()
        set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
        message(STATUS "clang-tidy enabled")
    endif()
else()
    message(STATUS "clang-tidy disabled ")
endif()

# valgrind
# ctest -T memcheck 
find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
INCLUDE(Dart)

# TESTS
add_subdirectory(tests)

get_target_property(linked_libraries ${APP_LIBRARY_NAME} LINK_LIBRARIES)
message(STATUS "App library linked libraries: ${linked_libraries}")
