function(import_git_project PROJECT_NAME GIT_REPOSITORY GIT_TAG)
    include(FetchContent)
    # Test if project has not been already imported
    if(NOT ${PROJECT_NAME}_PROJECT)
        set(${PROJECT_NAME}_PROJECT TRUE PARENT_SCOPE)
        FetchContent_Declare(
            ${PROJECT_NAME}
            GIT_REPOSITORY ${GIT_REPOSITORY}
			GIT_TAG ${GIT_TAG}
        )
        FetchContent_GetProperties(${PROJECT_NAME})

        # Importing the project with EXCLUDE_FROM_ALL in order to avoid installing dependencies
        if(NOT ${PROJECT_NAME}_POPULATED)
            FetchContent_Populate(${PROJECT_NAME})
			if(${PROJECT_NAME}_SOURCE_DIR AND EXISTS ${${PROJECT_NAME}_SOURCE_DIR}/CMakeLists.txt)
				# Importing the project with EXCLUDE_FROM_ALL in order to avoid installing dependencies
				add_subdirectory(
					${${PROJECT_NAME}_SOURCE_DIR}
					${${PROJECT_NAME}_BINARY_DIR}
					EXCLUDE_FROM_ALL
				)
			endif()
        endif()
    endif()
endfunction()
