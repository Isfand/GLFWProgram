// GLFWProgram.cpp : Defines the entry point for the application.
// Src
/**GLFWProgram for openGL practice**/
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
"   FragColor = vec4(0.8f, 0.8f, 0.00f, 1.0f);\n"
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

    // Vertex cordinates. (Anti-clockwise)(X,Y,Z)
    GLfloat vertices[]=
    {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    // Used in Index buffer | Order in which shape assembly occurs
    GLuint indicies[]=
    {
        0,1,2,
        2,0,3
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
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Get vertex shader reference 
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // VertexShader, No. of Strings used for vertexShaderSource, reference to vertexShaderSource, if length is null each string is assumed to be null terminated
    glCompileShader(vertexShader); // GPU cannot understand the source code so it needs to be compiled to machine code right away

    // Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Get fragment shader reference 
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // In order to use the shaders we need to wrap them together in a shaderprogram which is what we will actually be using
    GLuint shaderProgram = glCreateProgram(); //Get shaderProgram reference | Nothing needs to be specified inside because there is only one type of shader program.
    glAttachShader(shaderProgram, vertexShader); // Attach vertex shader to the shader program
    glAttachShader(shaderProgram, fragmentShader); // Attach fragment shader to the shader program
    glLinkProgram(shaderProgram); // links the program object(ShaderProgram) specified by program

    // We can delete the shaders we created before because they are already in the program and to free space in memory.
    glDeleteShader(vertexShader); 
    glDeleteShader(fragmentShader);

    // Vertex array, vertex buffer and element buffer object
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0); //Position of the first vertex, Number of vertexes, data type of vertex, Only matters if cordinates are of type int so false, amount of data between each vertex, offset(Point where our vertices being in the array)
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glClearColor(0.10f, 0.10f, 0.10f, 1.0f); // RGBA (RED GREED BLUE ALPHA) ALPHA = COLOUR TRANSPARENCY. 1.0 means max value
    glClear(GL_COLOR_BUFFER_BIT); // Execute the command we've told it to prepare for above
    glfwSwapBuffers(window); // Only the back buffer has the color we want while the front buffer has a default(white) or nothing. So we swap them

    while(!glfwWindowShouldClose(window)) // tells glfw to keep the window open
    {   
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframemode | Apply to front and back, and draw as lines
        glDrawElements(GL_TRIANGLES, sizeof(indicies)/sizeof(GLuint), GL_UNSIGNED_INT, 0); // , Number of indicies,,
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // End wireframe mode
        glfwSwapBuffers(window);

        glfwPollEvents(); // Process all polled events so that the window is interactable. Such as resize, appearing, peripherals, etc.
    }

    // Delete all objects we've created
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);  // glfw terminate the window object
    glfwTerminate();            // terminates the library and all contexts
    return 0;
}