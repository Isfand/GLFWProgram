# CMakeList.txt : CMake project for GLFWProgram, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
file(GLOB ${PROJECT_NAME} CONFIGURE_DEPENDS "*.h" "*.cpp")
add_executable (${PROJECT_NAME} ${GLFWProgram})


# TODO: Add tests and install targets if needed.


