//
// Created by unexpectcat on 3/12/26.
//

#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>


struct Window::Impl {

    public: virtual ~Impl();

    public:
    static GLFWwindow* window;
};

GLFWwindow* Window::Impl::window = nullptr;

int Window::createWindow() {
    GLFWwindow* window = glfwCreateWindow(Window::resolution[0], Window::resolution[1], "Sausage Engine", NULL, NULL);

    if (!window) {
        printf("3.3 Core failed. Attempting fallback to 2.1...\n");
        // Fallback for VMs
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    }

    if (!window) {
        fprintf(stderr, "Fatal: GPU does not support OpenGL 2.1 or 3.3\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    Window::Impl::window = window;
    return 0;
}

void Window::setCurrentContextNull() {
    glfwMakeContextCurrent(NULL);
}

bool Window::isOpen() {
    return !glfwWindowShouldClose(Window::Impl::window);
}

void Window::BeginDrawFrame() {
    glfwPollEvents();
    if (glfwGetKey(Window::Impl::window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(Window::Impl::window, 1);
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
    glfwSwapBuffers(Window::Impl::window);
}

void Window::Shutdown() {
    glfwDestroyWindow(Window::Impl::window);
    glfwTerminate();
}

