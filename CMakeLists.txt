cmake_minimum_required( VERSION 4.0.6 )

set( CMAKE_EXPORT_COMPILE_COMMANDS TRUE )

project( Particle )

set( CMAKE_CXX_COMPILER g++ )
set( CMAKE_CXX_STANDARD 23 )

file( GLOB_RECURSE SOURCE_FILES src/*.cpp )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

target_compile_options( ${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic )

find_package( SDL3 REQUIRED )
target_link_libraries( ${PROJECT_NAME} PRIVATE SDL3::SDL3 )
target_include_directories( ${PROJECT_NAME} PRIVATE inc ${SDL3_INCLUDE_DIRS} )

