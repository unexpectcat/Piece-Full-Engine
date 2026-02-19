#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

int main(void) {
    // 1. Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // 2. Set OpenGL version (3.3 Core is the standard for learning)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 3. Create the window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Sausage Engine - Arch Linux", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // 4. Load GLAD (Must happen after making context current)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    // 5. The Render Loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, 1);

        // Fun: Change color based on time
        float time = (float)glfwGetTime();
        float red   = (sinf(time) * 0.5f) + 0.5f;
        float green = (sinf(time + 2.0f) * 0.5f) + 0.5f;
        float blue  = (sinf(time + 4.0f) * 0.5f) + 0.5f;

        // Render
        glClearColor(red, green, blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}