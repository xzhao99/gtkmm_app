
message("")
message("************************************************************")
message("* FindMachineWorks starts                                  *")
message("************************************************************")

# find the MachineWorks_DIR from the local env list
if(DEFINED ENV{LI_DIR})
  message(STATUS "MachineWorks_DIR(LI_DIR) FOUND in the ENVIRONMENT var list:")
  message(STATUS "LI_DIR = $ENV{LI_DIR}")
	set(MachineWorks_DIR "$ENV{LI_DIR}")

	if(DEFINED ENV{LI_DIAG_MESSAGE_FILE})
  	message(STATUS "LI_DIAG_MESSAGE_FILE = $ENV{LI_DIAG_MESSAGE_FILE}")  
  	set(MachineWorks_DIAG_MESSAGE_FILE "$ENV{LI_DIAG_MESSAGE_FILE}")
	else()
		set(MachineWorks_DIAG_MESSAGE_FILE "${MachineWorks_DIR}/messages/english/diagnos")
		message(STATUS "LI_DIAG_MESSAGE_FILE is not defined. We set it as: ${MachineWorks_DIAG_MESSAGE_FILE}")  
	endif()
else()
  message(WARNING "MachineWorks_DIR(LI_DIR) or LI_DIAG_MESSAGE_FILE NOT FOUND! Please make sure they exist")
	message(STATUS "LI_DIR = $ENV{LI_DIR}")
  message(STATUS "LI_DIAG_MESSAGE_FILE = $ENV{LI_DIAG_MESSAGE_FILE}")
endif()


# check the existance of the LI Directory and message file
IF (EXISTS "${MachineWorks_DIR}")
	set(MachineWorks_FOUND ON)
ELSE()
	message(FATAL_ERROR  "MachineWorks_DIR does NOT exists!" )
ENDIF()

IF (NOT EXISTS "${MachineWorks_DIAG_MESSAGE_FILE}")
	message(FATAL_ERROR  "MachineWorks_DIAG_MESSAGE_FILE is NOT found!" )
ENDIF()


# set MachineWorks_LIB_DIR
message(STATUS "MachineWorks build type: ${CMAKE_BUILD_TYPE}. Setting the MachineWorks_LIB_DIR...")
IF(WIN32)
	set(msoft_ver "msoft143")
	message(STATUS "msoft version: ${msoft_ver}. (MicroSoft Visual Studio build tools version).")
ENDIF()
IF(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES DEBUG)
	IF(WIN32)
		set(MachineWorks_LIB_DIR ${MachineWorks_DIR}/lib/amd/winxp64/${msoft_ver}/dds_)
	ELSE() 
		set(MachineWorks_LIB_DIR ${MachineWorks_DIR}/lib/x64/linux/gcc/dds_)
	ENDIF()
ELSE()
	IF(WIN32)
		set(MachineWorks_LIB_DIR ${MachineWorks_DIR}/lib/amd/winxp64/${msoft_ver}/dos_)
	ELSE() 
		set(MachineWorks_LIB_DIR ${MachineWorks_DIR}/lib/x64/linux/gcc/dos_)
	ENDIF()
ENDIF()


# check the existance of the Lib Dir
IF (EXISTS "${MachineWorks_LIB_DIR}")
	message(STATUS  "MachineWorks_LIB_DIR found: ${MachineWorks_LIB_DIR}")
ELSE()
	message(FATAL_ERROR  "MachineWorks_LIB_DIR does NOT exists!" )
ENDIF()


# set the MachineWorks_INCLUDE_DIR & MachineWorks_LIBRARIES
set(MachineWorks_INCLUDE_DIR "${MachineWorks_DIR}/include")
if(WIN32)
	list(APPEND MachineWorks_INCLUDE_DIR "${MachineWorks_DIR}/include/amd/winxp64/${msoft_ver}")
else() 
	list(APPEND MachineWorks_INCLUDE_DIR "${MachineWorks_DIR}/include/x64/linux/gcc")
endif()

# OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
	message(STATUS "OpenGL directory: ${OpenGL_DIR}")
	message(STATUS "OpenGL library  : ${OPENGL_LIBRARIES}")
endif()

# find the libs
message(STATUS  "finding MW libs from MachineWorks_LIB_DIR= ${MachineWorks_LIB_DIR}")
find_library(mw_lib NAMES mw REQUIRED HINTS "${MachineWorks_LIB_DIR}")			  # find mw.lib
message(STATUS  "found mw_lib: ${mw_lib}")
find_library(mwrenogl_lib NAMES mwrenogl REQUIRED HINTS "${MachineWorks_LIB_DIR}")# find mwrenogl.lib
message(STATUS  "found mwrenogl_lib: ${mwrenogl_lib}")
find_library(mwwindow_lib NAMES mwwindow REQUIRED HINTS "${MachineWorks_LIB_DIR}")# find mwwindow.lib
message(STATUS  "found mwwindow_lib: ${mwwindow_lib}")
set(MachineWorks_LIBRARIES "${mw_lib};${mwrenogl_lib};${mwwindow_lib};${OPENGL_LIBRARIES}")

if(WIN32)
	find_library(mwwgl_lib NAMES mwwgl REQUIRED HINTS "${MachineWorks_LIB_DIR}")		# find mwwgl.lib(Win)
	message(STATUS  "found mwwgl_lib: ${mwwgl_lib}")
	find_library(mwrendx_lib NAMES mwrendx REQUIRED HINTS "${MachineWorks_LIB_DIR}")# find mwrendx.lib(Win Only)
	message(STATUS  "found mwrendx_lib: ${mwrendx_lib}")
	list(APPEND MachineWorks_LIBRARIES ";${mwwgl_lib};${mwrendx_lib}")
else()
	message(STATUS  "finding dependencies: libxft and libfontconfig")
	find_library(xft_lib NAMES xft Xft REQUIRED HINTS "/usr/lib/x86_64-linux-gnu")  # find libXft.a
	find_library(fc_lib NAMES fontconfig REQUIRED HINTS "/usr/lib/x86_64-linux-gnu")	
	
	find_library(mwglx_lib NAMES mwglx REQUIRED HINTS "${MachineWorks_LIB_DIR}")		# find mwglx.lib(Lin)
	message(STATUS  "found mwglx_lib: ${mwglx_lib}")
	list(APPEND MachineWorks_LIBRARIES ";${mwglx_lib};${xft_lib};${fc_lib}")
endif()


message(STATUS "set MachineWorks_FOUND      = ${MachineWorks_FOUND}")
message(STATUS "set MachineWorks_INCLUDE_DIR= ${MachineWorks_INCLUDE_DIR}")
message(STATUS "set MachineWorks_LIBRARIES  = ${MachineWorks_LIBRARIES}")

message("************************************************************")
message("* FindMachineWorks ended                                   *")
message("************************************************************")
message("")


