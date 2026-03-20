//
// Created by unexpectcat on 3/12/26.
//

#include "window.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <math.h>


struct Window::Impl {

    public: virtual ~Impl();

    public:
    static GLFWwindow* window;
};

GLFWwindow* Window::Impl::window = nullptr;

int Window::createWindow() {
    // FIX: Assign directly to the static member so other methods can see it
    Window::Impl::window = glfwCreateWindow(Window::resolution[0], Window::resolution[1], "Sausage Engine", NULL, NULL);

    if (!Window::Impl::window) {
        printf("3.3 Core failed. Attempting fallback to 2.1...\n");
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
        Window::Impl::window = glfwCreateWindow(Window::resolution[0], Window::resolution[1], "Sausage Engine", NULL, NULL);
    }

    if (!Window::Impl::window) {
        fprintf(stderr, "Fatal: GPU does not support OpenGL 2.1 or 3.3\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(Window::Impl::window);

    // --- IMGUI INITIALIZATION SEQUENCE ---
    // 1. Create the base context first
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // 2. Setup Style
    ImGui::StyleColorsDark();

    // 3. Init Platform Backend (GLFW)
    if (!ImGui_ImplGlfw_InitForOpenGL(Window::Impl::window, true)) {
        fprintf(stderr, "Failed to initialize ImGui GLFW backend\n");
        return -1;
    }

    // 4. Init Renderer Backend (OpenGL)
    if (!ImGui_ImplOpenGL3_Init("#version 130")) {
        fprintf(stderr, "Failed to initialize ImGui OpenGL3 backend\n");
        return -1;
    }

    return 0;
}

void Window::setCurrentContextNull() {
    glfwMakeContextCurrent(NULL);
}

void Window::bindImguiContext() {
}

bool Window::isOpen() {
    return !glfwWindowShouldClose(Window::Impl::window);
}

void Window::BeginDrawFrame() {
    glfwPollEvents();
    if (glfwGetKey(Window::Impl::window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(Window::Impl::window, 1);

    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // Fun: Change color based on time
    float time = (float)glfwGetTime();
    float red   = (sinf(time) * 0.5f) + 0.5f;
    float green = (sinf(time + 2.0f) * 0.5f) + 0.5f;
    float blue  = (sinf(time + 4.0f) * 0.5f) + 0.5f;

    // Render
    glClearColor(red, green, blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::EndDrawFrame() {
    // Swap buffers and poll events
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers
    if (Window::Impl::window) {
        glfwSwapBuffers(Window::Impl::window);
    }
}

void Window::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(Window::Impl::window);
    glfwTerminate();
}

