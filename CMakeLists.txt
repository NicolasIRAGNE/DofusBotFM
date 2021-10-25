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

add_library(DBFLib)

target_sources(
    DBFLib
    PRIVATE 
        "src/Item.cpp"
        "src/Item.h"
        "src/StatsList.h"
        "src/StatsDensity.h"
        "src/StatsDensity.cpp"
        "src/RunesList.h"
        "src/RuneProperties.h"
        "src/RuneProperties.cpp")

add_executable(DofusBotFM)
target_sources(DofusBotFM PRIVATE "src/main.cpp")
target_link_libraries(DofusBotFM DBFLib)
target_include_directories(DBFLib PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")

#######################################################
#                        TEST                         #
#######################################################

# Add a way to access private headers for testing
# Use set_property(TARGET <YourProject> PROPERTY DBFLib_PRIVATE_HEADERS 1) to enable it
target_include_directories(DBFLib PUBLIC "$<BUILD_INTERFACE:$<$<BOOL:$<TARGET_PROPERTY:DBFLib_PRIVATE_HEADERS>>:${CMAKE_CURRENT_SOURCE_DIR}/src>>")

enable_testing()
add_subdirectory(test)
