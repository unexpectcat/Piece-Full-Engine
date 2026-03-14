//
// Created by ahd on 3/12/26.
//

#include "internalRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


int internalRenderer::initGLFW() {

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // 2. Set OpenGL version (3.3 Core is the standard for learning)
    // Try 3.3 first
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 0;
}


// Load GLAD (Must happen after making context current)
int internalRenderer::initGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }
    return 0;
}

