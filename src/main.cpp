#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#include <cmath>

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 rotation;
void main()
{
    gl_Position = rotation * vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

int main()
{
    // Triangle vertices
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL FPS Toggle", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    // Disable vsync (manual frame control)
    glfwSwapInterval(0);

    // Vertex buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Vertex Shader Error:\n" << infoLog << std::endl;
    }

    // Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Fragment Shader Error:\n" << infoLog << std::endl;
    }

    // Shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Shader Program Link Error:\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Rotation uniform location
    int rotLoc = glGetUniformLocation(shaderProgram, "rotation");

    // Clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // --- FPS Control ---
    double targetFPS = 1000.0;
    double targetFrameTime = 1.0 / targetFPS;

    std::cout << "Press F1 = 60 FPS | F2 = 1000 FPS | F3 = Unlimited\n";

    while (!glfwWindowShouldClose(window))
    {
        double frameStart = glfwGetTime();

        // Handle FPS toggle keys
        if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
            targetFPS = 1000.0;
            targetFrameTime = 1.0 / targetFPS;
            std::cout << "→ FPS capped at 60\n";
        }
        if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) {
            targetFPS = 10000.0;
            targetFrameTime = 1.0 / targetFPS;
            std::cout << "→ FPS capped at 1000\n";
        }
        if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS) {
            targetFPS = 100000.0; // unlimited
            std::cout << "→ FPS uncapped\n";
        }

        // Update rotation matrix
        float angle = static_cast<float>(glfwGetTime());
        float cosA = cos(angle);
        float sinA = sin(angle);
        float rotationMatrix[16] = {
             cosA,  sinA, 0.0f, 0.0f,
            -sinA,  cosA, 0.0f, 0.0f,
             0.0f,  0.0f, 1.0f, 0.0f,
             0.0f,  0.0f, 0.0f, 1.0f
        };
        glUniformMatrix4fv(rotLoc, 1, GL_FALSE, rotationMatrix);

        // Draw
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Manual FPS limit
        double frameEnd = glfwGetTime();
        double elapsed = frameEnd - frameStart;

        if (targetFPS > 0.0 && elapsed < targetFrameTime) {
            std::this_thread::sleep_for(
                std::chrono::duration<double>(targetFrameTime - elapsed));
        }
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
