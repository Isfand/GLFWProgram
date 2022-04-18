// GLFWProgram.cpp : Defines the entry point for the application.
//

#include "GLFWProgram.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* WIN_NAME{"GLFWProgram"};

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit(); // Version 3.3(Major.Minor)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // First major number of the version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Last minor number of the version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core only contains modern while compatability contains both modern and old

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WIN_NAME, NULL, NULL);

    if (window == NULL) // If window creation fails display message
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);  // glfw create context/object. We want to use the window

    gladLoadGL(); // Glad loads needed configurations for openGL
    glViewport(0,0, 800,600); // Area of the window OpenGL renders in (bottom left to top right)(xy, xy)
    glClearColor(0.10f, 0.50f, 0.10f, 1.0f); // RGBA (RED GREED BLUE ALPHA) ALPHA = COLOUR TRANSPARENCY. 1.0 means max value
    glClear(GL_COLOR_BUFFER_BIT); // Execute the command we've told it to prepare for above
    glfwSwapBuffers(window); // Only the back buffer has the color we want while the front buffer has a default(white) or nothing. So we swap them

    while(!glfwWindowShouldClose(window)) // tells glfw to keep the window open
    {
        glfwPollEvents(); // Process all polled events so that the window is interactable. Such as resize, appearing, peripherals, etc.
    }

    glfwDestroyWindow(window);  // glfw terminate the window object
    glfwTerminate();            // terminates the library and all contexts
    return 0;
}