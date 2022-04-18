GLFWProgram

DEPENDENCIES: Git, CMake and ninja-build.

Any call with a VERSION lower than 3.13 will leave CMP0079 unset

Be sure to add CMakePresets.txt to change the output directory to out/build. Generated by VS
Running the project in VS creates the relavant .vs folder in top level directory

cmake -DGLFW_BUILD_DOCS=OFF -S . -B out/build // To build sub modules

git init														 // Initialise as git. Creates a .git folder in top directory
git submodule add https://github.com/glfw/glfw.git external/glfw // Adds git sub directory into existing project. last part just means create a folder called external and another folder inside called glfw. This is done so you can add multiple sub directorys in one folder instead of many.
git add -f <FileName> 											 // Adds the specific file or directory/folder
git commit -am "Updated description"							 // Updates everything
git submodule update --init --recursive                          // Grabs the sub module on a new clone