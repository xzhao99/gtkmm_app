cmake_minimum_required(VERSION 3.20.0)
project(GTKmm_App)

# add CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")


# set c++ std
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0>=4.10)
pkg_check_modules(EPOXY REQUIRED epoxy)

find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

message(STATUS "")
message(STATUS "[${PROJECT_NAME}] GTKMM_INCLUDE_DIRS: ${GTKMM_INCLUDE_DIRS}")
message(STATUS "[${PROJECT_NAME}] GTKMM_LIBRARY_DIRS: ${GTKMM_LIBRARY_DIRS}")
message(STATUS "[${PROJECT_NAME}] GTKMM_LIBRARIES: ${GTKMM_LIBRARIES}")
message(STATUS "[${PROJECT_NAME}] GTKMM_CFLAGS_OTHER: ${GTKMM_CFLAGS_OTHER}")
message(STATUS "")

# CMake is gonna read the 'CMakeLists.txt' file located under 'example':
#add_subdirectory(src_test)
#add_subdirectory(src_gpt)
add_subdirectory(src)

# diagnostics with color
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options("/diagnostics:color")
endif()