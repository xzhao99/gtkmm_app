# set the current project name
set(CURR_PROJ_NAME MyMeshViewer)

# add hearders and source
set(MY_SRC 
  "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/MainApplication.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/MyGLArea.cpp"
)

set(MY_HEADERS 
  "${CMAKE_CURRENT_SOURCE_DIR}/MainApplication.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/MyGLArea.h"
)

# create executable
add_executable(${CURR_PROJ_NAME} ${MY_HEADERS} ${MY_SRC})

# include/link options
target_include_directories(MyMeshViewer PRIVATE
  ${GTKMM_INCLUDE_DIRS}
  ${EPOXY_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(MyMeshViewer PRIVATE
  ${GTKMM_LIBRARIES}
  ${EPOXY_LIBRARIES}
  glm::glm OpenGL::GL
)

target_link_directories(${CURR_PROJ_NAME} PRIVATE ${GTKMM_LIBRARY_DIRS})

target_compile_options(MyMeshViewer PRIVATE
  ${GTKMM_CFLAGS_OTHER}
)

# format the source code
include(ClangTools)
AddClangFormat(${CURR_PROJ_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/")