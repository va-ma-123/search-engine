cmake_minimum_required(VERSION 3.10)

project(SEARCHENGINE)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCE_FILES
	src/main.cpp
	src/inverted_index.cpp
)

add_executable(search_engine ${SOURCE_FILES})
