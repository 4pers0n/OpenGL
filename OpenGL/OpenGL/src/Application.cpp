#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLEW */
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error when initializing GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // the actual data we put into the vertex buffer
    float positions[6] = {
        -0.5f, -0.5f,  // each line is a vertex
         0.0f,  0.5f,  // we group two elements in each line together
         0.5f, -0.5f   // and it's called an attribute
    };

    // create a buffer, buffer_id is the output parameter
    unsigned int buffer_id;
    glGenBuffers(1, &buffer_id);
    if (buffer_id == GL_INVALID_VALUE) {
        std::cerr << "Error when generating a buffer" << std::endl;
        glfwTerminate();
        return -1;
    }
    // bind the buffer to an array buffer inside vram
    // enter the state of having this buffer (no need to specify the buffer later)
    // (imagine seleting a layer in Photoshop)
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    // specify the data(we can specify the size first)
    // check the docs.GL for this function
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    // 1. We call this function once because we only have one attribute(position)
    // para - index : the index of this attribute
    // para - size : how many types are inside this attribute
    // para - type : the type of element inside this attribute
    // para - normalized : boolean of if to normalize the data
    // para - stride : offset to go to the next vertex
    // para - pointer : specifies an offset of the first component
    //                  of the first generic vertex attribute in the array
    //                  (the offset to an attribute)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    // used to enable the attribute above. Again state machine,
    // only need to specify the index. Can be called before the line above.
    glEnableVertexAttribArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}