# set current project name
set(CURR_PROJ_NAME gtkmm_test)

message(STATUS "")
message(STATUS "[${CURR_PROJ_NAME}] subproject build starts ...")

FILE(GLOB MY_SRC 
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
FILE(GLOB MY_HEADERS 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_executable(${CURR_PROJ_NAME} ${MY_HEADERS} ${MY_SRC})

target_include_directories(${CURR_PROJ_NAME} PUBLIC 
    ${GTKMM_INCLUDE_DIRS}
    ${EPOXY_INCLUDE_DIRS}
    )

target_link_directories(${CURR_PROJ_NAME} PUBLIC ${GTKMM_LIBRARY_DIRS})

target_link_libraries(${CURR_PROJ_NAME} PUBLIC 
    ${GTKMM_LIBRARIES}
    ${EPOXY_LIBRARIES}
    glm::glm OpenGL::GL
    )

# format the source code
include(ClangTools)
AddClangFormat(${CURR_PROJ_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/")

message(STATUS "[${CURR_PROJ_NAME}] subproject build ended.")
message(STATUS "")