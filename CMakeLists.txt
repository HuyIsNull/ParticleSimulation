cmake_minimum_required( VERSION 4.0.6 )

set( CMAKE_EXPORT_COMPILE_COMMANDS TRUE )
set( FETCHCONTENT_FULLY_DISCONNECTED TRUE )

project( Particle )

set( CMAKE_CXX_COMPILER g++ )
set( CMAKE_CXX_STANDARD 23 )

file( GLOB_RECURSE SOURCE_FILES src/*.cpp )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    message( STATUS "Enabling Debug Mode" )
    target_compile_options( ${PROJECT_NAME} PRIVATE -fsanitize=address -fno-omit-frame-pointer -g )
    target_link_options( ${PROJECT_NAME} PRIVATE -fsanitize=address )
endif( )

target_compile_options( ${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic )

include( FetchContent ) 

if( FETCHCONTENT_FULLY_DISCONNECTED )
    set( REQUIRED_MODE REQUIRED )
else( )
    set( REQUIRED_MODE QUIET )
endif( )

find_package( SDL3 ${REQUIRED_MODE} )
if( NOT SDL3_FOUND )
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG SDL-1.2.15
    )
    FetchContent_MakeAvailable( SDL3 )
endif( )

find_package( nlohmann_json ${REQUIRED_MODE} )
if( NOT nlohmann_json_FOUND )
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.10.5
    )
    FetchContent_MakeAvailable( nlohmann_json )
endif( )


target_link_libraries( ${PROJECT_NAME} PRIVATE SDL3::SDL3 nlohmann_json::nlohmann_json )
target_include_directories( ${PROJECT_NAME} PRIVATE inc ${SDL3_INCLUDE_DIRS} )

