cmake_minimum_required(VERSION 3.20.0)
project(Example_App)

# add CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")


# set c++ std
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0>=4.10)


message(STATUS "GTKMM_INCLUDE_DIRS: ${GTKMM_INCLUDE_DIRS}")
message(STATUS "GTKMM_LIBRARY_DIRS: ${GTKMM_LIBRARY_DIRS}")
message(STATUS "GTKMM_LIBRARIES: ${GTKMM_LIBRARIES}")

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${GTKMM_INCLUDE_DIRS})
target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC ${GTKMM_LIBRARY_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${GTKMM_LIBRARIES})

# CMake is gonna read the 'CMakeLists.txt' file located under 'example':
add_subdirectory(src)

# format the source code
include(ClangTools)
AddClangFormat(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src")

# diagnostics with color
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options("/diagnostics:color")
endif()