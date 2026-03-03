cmake_minimum_required( VERSION 4.0.6 )

set( CMAKE_EXPORT_COMPILE_COMMANDS TRUE )

project( Particle )

set( CMAKE_CXX_COMPILER g++ )
set( CMAKE_CXX_STANDARD 23 )

file( GLOB_RECURSE SOURCE_FILES src/*.cpp )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    message( STATUS "Enabling Debug Mode" )
    message( STATUS "Enabling AddressSanitizer (ASan)" )
    target_compile_options( ${PROJECT_NAME} PRIVATE -fsanitize=address -fno-omit-frame-pointer -g )
    target_link_options( ${PROJECT_NAME} PRIVATE -fsanitize=address )
endif( )

target_compile_options( ${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic )

find_package( SDL3 REQUIRED )
find_package( nlohmann_json REQUIRED )
target_link_libraries( ${PROJECT_NAME} PRIVATE SDL3::SDL3 nlohmann_json::nlohmann_json )
target_include_directories( ${PROJECT_NAME} PRIVATE inc ${SDL3_INCLUDE_DIRS} )

