cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 20)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

project(fivehead LANGUAGES CXX)

include(cmake/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#8.1.1")
CPMAddPackage("gh:palacaze/sigslot#v1.2.1")

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
    src/game.cpp
    src/controller.cpp
    src/ui.cpp
    src/logic.cpp
)

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE fmt::fmt
    PRIVATE Pal::Sigslot
)
