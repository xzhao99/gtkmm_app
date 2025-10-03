# set the current project name
set(CURR_PROJ_NAME MyMeshViewer)

# add hearders and source
set(MY_SRC 
  "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/MainApplication.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/MyGLArea.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/MwGLArea.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/MachineWorks.cpp"
)

set(MY_HEADERS 
  "${CMAKE_CURRENT_SOURCE_DIR}/MainApplication.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/MyGLArea.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/MwGLArea.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/MachineWorks.h"
)

# MachineWorks_FOUND, MachineWorks_INCLUDE_DIR, MachineWorks_LIBRARIES
find_package(MachineWorks REQUIRED) 
find_package(X11 REQUIRED)
if(X11_FOUND)
  message(STATUS "X11 found? ${X11_FOUND}")
  message(STATUS "X11 include directories: ${X11_INCLUDE_DIR}")
  message(STATUS "X11 libraries: ${X11_LIBRARIES}")
endif()

# create executable
add_executable(${CURR_PROJ_NAME} ${MY_HEADERS} ${MY_SRC})

# include/link options
target_include_directories(${CURR_PROJ_NAME} PRIVATE
  ${GTKMM_INCLUDE_DIRS}
  ${EPOXY_INCLUDE_DIRS}
  ${X11_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${CURR_PROJ_NAME} PRIVATE
  ${GTKMM_LIBRARIES}
  ${EPOXY_LIBRARIES}
  glm::glm OpenGL::GL ${X11_LIBRARIES}
)

target_link_directories(${CURR_PROJ_NAME} PRIVATE ${GTKMM_LIBRARY_DIRS})

target_compile_options(${CURR_PROJ_NAME} PRIVATE
  ${GTKMM_CFLAGS_OTHER}
  "-lX11"
)

if(MachineWorks_FOUND)
  target_include_directories(${CURR_PROJ_NAME} PRIVATE ${MachineWorks_INCLUDE_DIR})
	target_link_libraries(${CURR_PROJ_NAME} PRIVATE ${MachineWorks_LIBRARIES})
else()
	message(FATAL_ERROR "MachineWorks library is NOT found!")
endif()

# format the source code
include(ClangTools)
AddClangFormat(${CURR_PROJ_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/")