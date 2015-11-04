project(compression)

cmake_policy(SET CMP0020 NEW)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Multimedia)

set(SOURCES

)

set(HEADERS

)

add_executable(compression ${SOURCES} ${HEADERS})

target_link_libraries(compression Qt5::Core Qt5::Multimedia)
