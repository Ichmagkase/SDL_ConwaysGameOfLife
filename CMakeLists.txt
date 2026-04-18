cmake_minimum_required(VERSION 3.11)

project(SDL_ConwaysGameOfLife)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(gol)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT gol)

target_sources(gol
    PRIVATE
        src/main.cpp
        "src/engine.cpp"
  "src/renderer.cpp" "src/include/engine.h")

target_include_directories(gol
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/thirdparty/include"
)

if(WIN32)
    set(SDL3_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/thirdparty/libs/win64/SDL3.lib")
    set(SDL3_DLL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/thirdparty/libs/win64/SDL3.dll")

    target_link_libraries(gol PRIVATE "${SDL3_LIB_PATH}")

    add_custom_command(TARGET gol POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_DLL_PATH}"
        $<TARGET_FILE_DIR:gol>
    )
else()
    find_package(SDL3 REQUIRED)
    target_link_libraries(gol PRIVATE SDL3::SDL3)
endif()