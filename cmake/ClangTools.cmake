# clang-format
function(AddClangFormat target directory)
	find_program(CLANG_FORMAT_EXE NAMES clang-format-18 clang-format REQUIRED)

	if(CLANG_FORMAT_EXE-NOTFOUND)
		message(STATUS "clang-format is NOT found!")
	else()
		message(STATUS "clang-format is found: ${CLANG_FORMAT_EXE}")
		execute_process(COMMAND ${CLANG_FORMAT_EXE} --version OUTPUT_VARIABLE clang_out )
		string(REGEX MATCH .*\(version[^\n]*\)\n version ${clang_out})
		set(CLANG_FORMAT_VERSION ${CMAKE_MATCH_1})
		message(STATUS "clang-format version: ${CLANG_FORMAT_VERSION}")
	endif()

	set(EXPRESSION h hpp hxx c cc cxx cpp)
	list(TRANSFORM EXPRESSION PREPEND "${directory}/*.")
	file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
		LIST_DIRECTORIES false ${EXPRESSION}
	)

	# print for debug
	#message(STATUS "the target: ${target}")
	message(STATUS "formating the code directory: ${directory}")
	#message(STATUS "the SOURCE_FILES to be formatted:\n ${SOURCE_FILES}")
	message(STATUS ".clang-format file directory: ${CMAKE_SOURCE_DIR}")  

	add_custom_command(TARGET ${target} PRE_BUILD COMMAND
		${CLANG_FORMAT_EXE} -i --style=file:"${CMAKE_SOURCE_DIR}/.clang-format" ${SOURCE_FILES}
	)
endfunction()


# clang-tidy
function(AddClangTidy target)
	find_program(CLANG_TIDY_PATH clang-tidy REQUIRED)
	if(CLANG_TIDY_PATH-NOTFOUND)
	message(STATUS "clang-tidy is NOT found!")
	else()
	message(STATUS "clang-tidy is found: ${CLANG_TIDY_PATH}")
	endif()

	set(CLANG_TIDY_ARGS "-checks=-*,-header-filter=.*,clang-analyzer-*,cppcoreguidelines-*")
	if(MSVC)
		message(STATUS "Running clang-tidy with MSVC compiler!")
		set_target_properties(${target}  PROPERTIES 
		  VS_GLOBAL_RunCodeAnalysis true
		  # Use visual studio core guidelines
		  VS_GLOBAL_EnableMicrosoftCodeAnalysis true
		  #VS_GLOBAL_CodeAnalysisRuleSet ${CMAKE_CURRENT_SOURCE_DIR}/foo.ruleset

		  # Use clang-tidy
		  VS_GLOBAL_EnableClangTidyCodeAnalysis true
		  VS_GLOBAL_ClangTidyChecks "${CLANG_TIDY_ARGS}"
		)
	else()
		message(STATUS "Running clang-tidy with non-MSVC compiler!")
		set(CLANG_TIDY_COMMAND "${CLANG_TIDY_PATH}" "${CLANG_TIDY_ARGS}")
		set_target_properties(${target}  PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
	endif()
endfunction()