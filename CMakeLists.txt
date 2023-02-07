cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 20)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

#set(CPPPROPERTIES_BUILD_EXAMPLES OFF)
#set(CPPPROPERTIES_BUILD_TESTS OFF)
#set(CPPPROPERTIES_ENABLE_JSON OFF)
#set(CPPPROPERTIES_ENABLE_XML OFF)

project(fivehead LANGUAGES CXX)

include(cmake/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#8.1.1")
CPMAddPackage("gh:palacaze/sigslot#v1.2.1")
#CPMAddPackage("gh:Tectu/cpp-properties#main")
#CPMAddPackage("gh:Tectu/cpp-properties#10d813f9510184c3f9a9873f3551a6f9dccd4670")


add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
)

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/include
#PRIVATE ${cppproperties_SOURCE_DIR}#/cppproperties
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE fmt::fmt
    PRIVATE Pal::Sigslot
#PRIVATE cppproperties-static
#    PUBLIC cppproperties-shared2
#   PRIVATE cppproperties
)
