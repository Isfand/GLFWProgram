# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.13)

project ("GLFWProgram")

# Download all submodules
find_package(Git QUIET)
    if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # update submodules as needed
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if(GIT_SUBMODULE)
            message(STATUS "submodule update")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                            RESULT_VARIABLE GIT_SUBMOD_RESULT)
            if(NOT_GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init failed with $(GIT_SUBMOD_RESULT), please checkout submodules")
            endif()
        endif()
    endif()

    # check all submodules
    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
        message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULES was turned off or failed. Please checkout submodules")
    endif()

    # Include sub-projects.
find_package(OpenGL REQUIRED)
add_subdirectory ("GLFWProgram")
add_subdirectory (external/glfw)
add_subdirectory(external/glad)
target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include)
target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} glfw)
