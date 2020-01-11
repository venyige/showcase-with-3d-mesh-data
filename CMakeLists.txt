cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set (CMAKE_AUTOMOC ON)
#set (CMAKE_AUTOUIC ON)
#set (CMAKE_AUTORCC ON)
#set(CMAKE_BUILD_TYPE DEBUG)
#find_package(Qt5 COMPONENTS Core)

project(triangular_mesh_conversion_utility)

set(SOURCES
    src/main.cpp
    src/write_stl.cpp
    src/basewriter.cpp
    src/mesh.cpp
    src/basereader.cpp
    src/read_obj.cpp
    )
set(HEADERS
    src/include/basewriter.h
    src/include/write_stl.h
    src/include/util.h
    src/include/mesh.h
    src/include/basereader.h
    src/include/read_obj.h
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC src/include)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "tcmu" CXX_STANDARD 17 CXX_EXTENSIONS OFF)
