#include <iostream>

#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/string_cast.hpp>

#include "GLBasics/VertexArray.h"
#include "GLBasics/VertexBuffer.h"
#include "GLBasics/VertexBufferLayout.h"
#include "GLBasics/IndexBuffer.h"
#include "GLBasics/Shader.h"
#include "GLBasics/Texture.h"
#include "Utils/MainUtils.h"
#include "Maths/Projection.h"
#include "Renderer.h"


int main(void)
{
    // Initialize the GLFW library
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Utils::DEFAULT_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Utils::DEFAULT_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(Utils::DEFAULT_WINDOW_WIDTH, Utils::DEFAULT_WINDOW_HEIGHT, "OpenGL", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "GLFW failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Utils::FramebufferSizeCallback);

    // Initialize the GLEW library
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW initialization failed" << std::endl;
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

    // ImGui environment
    int scaleMode = 0;
    bool useBlending = false;
    bool useWireFrameMode = false;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        //                             green and grey ish color
        renderer->Clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        // Render here
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Stats:");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Window Width: %d", Utils::windowWidth);
            ImGui::Text("Window Height: %d", Utils::windowHeight);
            ImGui::End();
        }
        
        {
            ImGui::Begin("Debug");
            ImGui::SliderInt("Scaling Mode", &scaleMode, 0, 2);
            ImGui::Text("0: Aspect Ratio, 1: Full Screen, 2: No Scaling");
            ImGui::Text("");
            ImGui::Checkbox("Use OpenGL blending", &useBlending);
            ImGui::Checkbox("Enable wireframe mode", &useWireFrameMode);
            ImGui::End();
        }

        // This keeps the rendered output always having a correct aspect ratio
        glm::mat4 proj = Maths::GetScaleMatrix(static_cast<Maths::ScaleMode>(scaleMode), Utils::windowWidth, Utils::windowHeight);
        shader->SetUniformMat4f("aProj", proj);

        if (useBlending) { renderer->EnableBlending(); }
        else { renderer->DisableBlending(); }
        if (useWireFrameMode) { renderer->EnableWireFrameMode(); }
        else { renderer->DisableWireFrameMode(); }

        renderer->DrawElements(GL_TRIANGLES, *vao, *shader, ibo->GetCount());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        Utils::ProcessInput(window);

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