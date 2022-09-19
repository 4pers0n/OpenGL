#include <iostream>

#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/string_cast.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "GLBasics/VertexArray.h"
#include "GLBasics/VertexBuffer.h"
#include "GLBasics/VertexBufferLayout.h"
#include "GLBasics/IndexBuffer.h"
#include "GLBasics/Shader.h"
#include "GLBasics/Texture.h"
#include "Utils/MainUtils.h"
#include "Renderer.h"

constexpr int MAJOR_VERSION = 3;
constexpr int MINOR_VERSION = 3;

int main(void)
{
    // Initialize the GLFW library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(Utils::DEFAULT_WINDOW_WIDTH, Utils::DEFAULT_WINDOW_HEIGHT, "OpenGL", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Utils::FramebufferSizeCallback);

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

    const auto texture0 = new GLBasics::Texture("res/textures/container.jpg");
    const auto texture1 = new GLBasics::Texture("res/textures/awesomeface.png");
    texture0->Bind(0);
    shader->SetUniform1i("sampler0", 0);
    texture1->Bind(1);
    shader->SetUniform1i("sampler1", 1);

    const auto renderer = new Renderer();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        renderer->Clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        // Render here
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Window Width: %d", Utils::windowWidth);
            ImGui::Text("Window Height: %d", Utils::windowHeight);
        }

        // This keeps the rendered output always having a correct aspect ratio
        {
            float projectedWidth = 0.0f, projectedHeight = 0.0f;
            if (Utils::windowWidth < Utils::windowHeight)
            {
                projectedWidth = 2.0f;
                projectedHeight = 1.0f * Utils::windowHeight / Utils::windowWidth * 2.0f;
            }
            else
            {
                projectedHeight = 2.0f;
                projectedWidth = 1.0f * Utils::windowWidth / Utils::windowHeight * 2.0f;
            }

            ImGui::Text("Normalized Window Width: %f", projectedWidth);
            ImGui::Text("Normalized Window Height: %f", projectedHeight);

            glm::mat4 proj = glm::ortho(-projectedWidth / 2, projectedWidth / 2,
                -projectedHeight / 2, projectedHeight / 2, -1.0f, 1.0f);

            shader->SetUniformMat4f("aProj", proj);
        }
        renderer->DrawElements(GL_TRIANGLES, *vao, *shader, ibo->GetCount());

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
    delete(texture0);
    delete(texture1);
    delete(renderer);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}