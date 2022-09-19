#include <iostream>

#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "GLBasics/VertexArray.h"
#include "GLBasics/VertexBuffer.h"
#include "GLBasics/VertexBufferLayout.h"
#include "GLBasics/IndexBuffer.h"
#include "GLBasics/Shader.h"
#include "GLBasics/Texture.h"

constexpr int MAJOR_VERSION = 3;
constexpr int MINOR_VERSION = 3;
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main(void)
{
    // Initialize the GLFW library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize the GLEW library
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    // Initialize the ImGui library
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    const ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));  // NOLINT(clang-diagnostic-cast-qual)

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const float vertices[] = {
      // positions      texture coordinates
         0.5f, -0.5f,   1.0f, 0.0f,
        -0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f,  0.5f,   0.0f, 1.0f,
         0.5f,  0.5f,   1.0f, 1.0f
    };

    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    const auto vbo = new GLBasics::VertexBuffer(vertices, 4 * 4 * sizeof(float));
    const auto vbl = new GLBasics::VertexBufferLayout();
    vbl->Push<float>(2);
    vbl->Push<float>(2);
    const auto ibo = new GLBasics::IndexBuffer(indices, 6);
    const auto vao = new GLBasics::VertexArray();
    vao->BindBuffer(*vbo, *vbl, *ibo);

    const auto shader = new GLBasics::Shader("res/shaders/MainVertex.glsl", "res/shaders/MainFragment.glsl");

    const auto texture = new GLBasics::Texture("res/textures/container.jpg");
    texture->Bind(0);
    shader->SetUniform1i("sampler2D", 0);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Render here
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        GLCall(glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, 0));

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    delete(vao);
    delete(vbo);
    delete(vbl);
    delete(ibo);
    delete(shader);
    delete(texture);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}