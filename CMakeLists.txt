cmake_minimum_required(VERSION 3.20.0)
project(GTKmm_App)

# add CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

# Let's nicely support folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# supported by the Ninja and Makefiles generators, will be ignored by others.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

# set c++ std
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

# For SHARED and MODULE libraries, POSITION_INDEPENDENT_CODE is ON by default.
# For executables and STATIC libraries, it's OFF by default.
include(CheckPIESupported)
check_pie_supported(OUTPUT_VARIABLE output LANGUAGES C CXX) # <output> var has details about error!
if(CMAKE_C_LINK_PIE_SUPPORTED OR CMAKE_CXX_LINK_PIE_SUPPORTED)
	message(STATUS "Current compiler supports PIE at the link time.\n")
	set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -no-pie")
else()
	message(WARNING "PIE is NOT supported at link time. output message: \n${output}")
endif()

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