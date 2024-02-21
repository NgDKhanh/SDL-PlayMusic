#Sample CMakeLists to build SDL project written by NgDKhanh based on Cmake of Quang N Le
cmake_minimum_required(VERSION 3.5.0)
project(sdl_playmusic VERSION 0.1.0 LANGUAGES C CXX)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17) # Default to C++17
endif()

set(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_CXX_FLAGS "-std=c++14") 
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -Wall -Wextra -Wpedantic -g")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Needed so that cmake uses our find modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#find all essential packages
find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
    include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
)

#Custom libraries

#Add sub-modules

#Setting sources code and executable names
set(SOURCE_DIR src) 

file(GLOB SDL_PROJECT_SOURCES ${SOURCE_DIR}/*.cpp)
set(EXECUTABLE sdl_playmusic)

#add main executable
add_executable(${EXECUTABLE} ${SDL_PROJECT_SOURCES} main/main.cpp)
target_link_libraries(${EXECUTABLE} PUBLIC 
                                            SDL2::Main SDL2::Image 
                                            GL
                                            SDL2::Net SDL2::Mixer SDL2::TTF SDL2::GFX 
                                            tag
)
target_include_directories(${EXECUTABLE} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
