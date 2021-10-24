cmake_minimum_required(VERSION 3.5)

project(DofusBotFM)

#######################################################
#                       FLAGS                         #
#######################################################

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

#######################################################
#                       BUILD                         #
#######################################################

add_library(${PROJECT_NAME}Lib)

target_sources(
    ${PROJECT_NAME}Lib
    PRIVATE 
        "src/Item.cpp"
        "src/Item.h"
        "src/StatsList.h"
        "src/StatsDensity.h"
        "src/StatsDensity.cpp"
        "src/RunesList.h"
        "src/RuneProperties.h"
        "src/RuneProperties.cpp")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE "src/main.cpp")
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)

#######################################################
#                        TEST                         #
#######################################################

enable_testing()
add_subdirectory(test)
