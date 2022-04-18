// GLFWProgram.cpp : Defines the entry point for the application.
//

#include "GLFWProgram.h"

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.8f, 0.02f, 1.0f);\n"
"}\n\0";

// settings
const unsigned int SCR_WIDTH  = 800;
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

    GLfloat vertices[]=
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

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

    // Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.10f, 0.10f, 0.10f, 1.0f); // RGBA (RED GREED BLUE ALPHA) ALPHA = COLOUR TRANSPARENCY. 1.0 means max value
    glClear(GL_COLOR_BUFFER_BIT); // Execute the command we've told it to prepare for above
    glfwSwapBuffers(window); // Only the back buffer has the color we want while the front buffer has a default(white) or nothing. So we swap them

    while(!glfwWindowShouldClose(window)) // tells glfw to keep the window open
    {   
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        glfwPollEvents(); // Process all polled events so that the window is interactable. Such as resize, appearing, peripherals, etc.
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);  // glfw terminate the window object
    glfwTerminate();            // terminates the library and all contexts
    return 0;
}