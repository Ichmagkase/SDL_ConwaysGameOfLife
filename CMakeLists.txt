cmake_minimum_required(VERSION 3.11)

project(SDL_ConwaysGameOfLife)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(gol)

target_sources(gol
    PRIVATE
        "src/main.cpp"
        "src/engine.cpp"
        "src/renderer.cpp" 
)

target_include_directories(gol PRIVATE src/include)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/infile.txt" infile.txt COPYONLY)

if(WIN32)
    add_subdirectory(SDL)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT gol)

else()
    find_package(SDL3 REQUIRED)
endif()

target_link_libraries(gol PRIVATE SDL3::SDL3)
