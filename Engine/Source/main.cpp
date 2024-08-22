#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "Windows/testWindow.h"  // Include your rendering logic
#include <iostream>
int main()
{
    Scene* myNewScene = new Scene();

    // Initialize GLFW
    if (!glfwInit())
        return -1;

    // Create a GLFW window with an OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL ImGui Window", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set OpenGL viewport
    glViewport(0, 0, 1360, 768);

    // Initialize the framebuffer for offscreen rendering
    myNewScene->InitFramebuffer(512, 512);

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup ImGui bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool show_demo_window = true;
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render to the framebuffer
        myNewScene->RenderToFramebuffer();

        glClearColor(0.1f, 0.4f, 0.1f, 1.0f); // Set a background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Create an ImGui window and display the rendered content
        ImGui::Begin("OpenGL Window");

        // Display the framebuffer texture in ImGui
        ImGui::Image((void*)(intptr_t)myNewScene->GetRenderedTexture(), ImVec2(512, 512));

        ImGui::End();

        //ImGui::ShowDemoWindow(&show_demo_window);
        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
