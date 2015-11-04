project(compression)

cmake_policy(SET CMP0020 NEW)

set(CMAKE_AUTOMOC ON)

cmake_minimum_required(VERSION 3.3)

find_package(Qt5Core)
find_package(Qt5Multimedia)

set(SOURCES
	main.cpp
)

set(HEADERS

)

add_executable(compression ${SOURCES} ${HEADERS})

target_link_libraries(compression Qt5::Core Qt5::Multimedia)
