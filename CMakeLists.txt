# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("GLFWProgram")

# Include sub-projects.
add_subdirectory ("GLFWProgram")
add_subdirectory (external/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include)
target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} glfw3)
