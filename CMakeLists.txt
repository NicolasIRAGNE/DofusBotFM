cmake_minimum_required(VERSION 3.5)

project(DofusBotFM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(
	${PROJECT_NAME}
	"src/main.cpp"
	"src/Item.cpp"
	"src/Item.h"
	"src/StatsList.h"
	"src/StatsDensity.h"
	"src/StatsDensity.cpp"
	"src/RunesList.h"
	"src/RuneProperties.h"
	"src/RuneProperties.cpp")
