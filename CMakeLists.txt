cmake_minimum_required(VERSION 3.10)
project(Tuner VERSION 1.0 LANGUAGES CXX)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Switching between system libraries and FetchContent
option(FETCH_LIBS "Use FetchContent to download libraries" ON)

if(FETCH_LIBS)
    include(FetchContent)
    
    # Fetch SDL3
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.26
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    
    # Fetch SDL_ttf
    FetchContent_Declare(
        SDL3_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-3.2.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    
    # Configure SDL3 options
    set(SDL_SHARED ON CACHE BOOL "Build SDL3 as shared library")
    set(SDL_STATIC OFF CACHE BOOL "Don't build SDL3 as static library")
    
    # Configure SDL_ttf options
    set(SDL3TTF_SAMPLES OFF CACHE BOOL "Don't build SDL_ttf samples")
    set(SDL3TTF_VENDORED ON CACHE BOOL "Use vendored dependencies for SDL_ttf")
    
    # Make both available
    FetchContent_MakeAvailable(SDL3 SDL3_ttf)
else()
    # Find system-installed packages
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
    find_package(SDL3_ttf REQUIRED CONFIG)
endif()

# Source files
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/App.cpp
    ${PROJECT_SOURCE_DIR}/src/Recorder.cpp
    ${PROJECT_SOURCE_DIR}/src/Graph.cpp
    ${PROJECT_SOURCE_DIR}/src/Sound.cpp
    ${PROJECT_SOURCE_DIR}/src/Text.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link SDL3 and SDL_ttf
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SDL3::SDL3 
    SDL3_ttf::SDL3_ttf
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -Wall 
        -Wextra 
        -Wno-unused-parameter
    )
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets/fonts
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/fonts
)

# For IDEs: make source groups by folders
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES})