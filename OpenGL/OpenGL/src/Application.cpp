#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, Renderer::FramebufferSizeCallback);
    Renderer::DisableWireframeMode();

    glfwSwapInterval(1);

    /* Initialize GLEW */
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error when initializing GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // the actual data we put into the vertex buffer
    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // position | texture coordinate | custom color
         0.5f, -0.5f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 2.0f, 2.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f
    };

    // index buffer (used to remove redundant vertices)
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Enable blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glBlendEquation(GL_FUNC_ADD));

    VertexArray* va = new VertexArray;

    VertexBuffer* vb = new VertexBuffer(positions, 7 * 4 * sizeof(float));
    
    VertexBufferLayout* layout = new VertexBufferLayout;
    layout->Push<float>(2);
    layout->Push<float>(2);
    layout->Push<float>(3);
    va->AddBuffer(*vb, *layout);

    IndexBuffer* ib = new IndexBuffer(indices, 2 * 3);

    Shader* shader = new Shader("res/shaders/Basic.glsl");
    shader->Bind();

    Texture* texture1 = new Texture("res/textures/BasicTexture.png");
    Texture* texture2 = new Texture("res/textures/awesomeface.png");
    //texture1->Bind(0);
    //shader->SetUniform1i("u_Texture1", 0);  // 0 because the texture slot is 0
    texture2->Bind(1);
    shader->SetUniform1i("u_Texture2", 1);


    // used for animation
    float r = 0.8f;
    float increment = 0.01f; 

    // because va has all the information stored in it
    va->UnBind();
    ib->UnBind();
    vb->UnBind();

    Renderer* renderer = new Renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    glm::vec3 translation(-0.5f, 0.0f, 0.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        renderer->Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (r > 1.0f) {
            increment = -0.01f;
        }
        else if (r < 0.0f) {
            increment = 0.01f;
        }
        r += increment;

        {
            ImGui::SliderFloat3("Translation", &translation.x, -1.0f, 1.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // set the projection matrix to fix the problem related to aspect ratio
        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        proj = glm::translate(proj, translation);

        shader->SetUniformMat4f("u_MVP", proj);


        shader->SetUniform4f("u_Color", r, 0.3f, 0.2f, 1.0f);

        renderer->Draw(*va, *ib, *shader);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    
    delete(vb);
    delete(ib);
    delete(va);
    delete(layout);
    delete(shader);
    delete(texture1);
    delete(texture2);
    delete(renderer);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
