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

set(GENERATED_SOURCES_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/generated-src")

set(ENUM_JSONS)

set(ENUM_GENERATOR_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/script/EnumGenerator")

set(ENUM_GENERATOR "${ENUM_GENERATOR_FOLDER}/EnumGenerator.py")
set(ENUM_GENERATOR_DEPENDENCIES
    ${PYTHON_SCRIPT_ENUM_GENERATOR}
    "${ENUM_GENERATOR_FOLDER}/EnumPattern.h.in"
    "${ENUM_GENERATOR_FOLDER}/EnumPattern.cpp.in")

set(GENERATED_SOURCES)
    
foreach(ENUM_JSON ${ENUM_JSONS})
    get_filename_component(FILENAME ${ENUM_JSON} NAME_WE)
    set(HEADER_OUT ${GENERATED_SOURCES_FOLDER}/${FILENAME}.h)
    set(CPP_OUT ${GENERATED_SOURCES_FOLDER}/${FILENAME}.cpp)
    list(APPEND GENERATED_SOURCES ${HEADER_OUT} ${CPP_OUT})
    add_custom_command(
        OUTPUT ${HEADER_OUT} ${CPP_OUT}
        DEPENDS ${ENUM_JSON} ${SCRIPT_DEPENDENCIES}
        COMMAND python ${ENUM_GENERATOR} ${ENUM_JSON} ${GENERATED_SOURCES_FOLDER}
        COMMENT "Generating ${HEADER_OUT} and ${CPP_OUT} from ${ENUM_JSON}")
endforeach(ENUM_JSON)

target_sources(
    DBFLib
    PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Item.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Item.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/StatsList.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/StatsDensity.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/StatsDensity.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/RunesList.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/RuneProperties.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/RuneProperties.cpp"
        
        ${GENERATED_SOURCES})

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
