#include "Renderer.h"
#include "core/Core.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Sausage {
    struct Renderer::Impl {
        unsigned int VBO;
        unsigned int VAO;
        unsigned int vertexShader;
        unsigned int fragmentShader;
        unsigned int shaderProgram;
        GLFWwindow* sausage_window;
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
        
    };

    Renderer::Renderer() : impl(new Impl{}) {}

    Renderer::~Renderer() {
        delete impl;
    }
    
    bool Renderer::isEngineWindowOpen()
    {
        return !glfwWindowShouldClose(impl->sausage_window);
    }
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

	int Renderer::Init(int width, int height, const std::string& title)
	{

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

		impl->sausage_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (impl->sausage_window == nullptr)
		{
			std::cout << "Failed to create GLFW window\n";
			glfwTerminate();
			return - 1;
		}
        glfwMakeContextCurrent(impl->sausage_window);

        // Load OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD\n";
            return -1;
        }
        glViewport(0, 0, 800, 600);

        glfwSetFramebufferSizeCallback(impl->sausage_window, framebuffer_size_callback);

        // Disable vsync (manual frame control)
        glfwSwapInterval(0);

        // Vertex buffer
        glGenBuffers(1, &impl->VBO);
        glGenVertexArrays(1, &impl->VAO);

        glBindVertexArray(impl->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, impl->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &impl->vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        glClearColor(0.169f, 0.220f, 0.298f, 1.0f); 

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cout << "Vertex Shader Error:\n" << infoLog << std::endl;
        }

        // Fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &impl->fragmentShaderSource, nullptr);
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

        return 0;
	}

	void Renderer::SetTarget(Window* window)
	{
	}

	void Renderer::Clear()
	{
        glDeleteProgram(impl->shaderProgram);
        glfwTerminate();
	}

	void Renderer::DrawFrame()
	{
        double frameStart = glfwGetTime();


        //// Update rotation matrix
        //float angle = static_cast<float>(glfwGetTime());
        //float cosA = cos(angle);
        //float sinA = sin(angle);
        //float rotationMatrix[16] = {
        //     cosA,  sinA, 0.0f, 0.0f,
        //    -sinA,  cosA, 0.0f, 0.0f,
        //     0.0f,  0.0f, 1.0f, 0.0f,
        //     0.0f,  0.0f, 0.0f, 1.0f
        //};
        //glUniformMatrix4fv(rotLoc, 1, GL_FALSE, rotationMatrix);

        // Draw
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(impl->shaderProgram);
        glBindVertexArray(impl->VAO);

        glfwPollEvents();
        glfwSwapBuffers(impl->sausage_window);

	}
}
