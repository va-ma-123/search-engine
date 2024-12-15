cmake_minimum_required(VERSION 3.10)

project(SEARCHENGINE)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCE_FILES
	src/main.cpp
	src/inverted_index.cpp
	src/bm25.cpp
)

add_executable(search_engine ${SOURCE_FILES})

target_link_libraries(search_engine pthread)