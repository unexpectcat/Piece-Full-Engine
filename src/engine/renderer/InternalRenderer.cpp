//
// Created by unexpectcat on 3/12/26.
//

#include "InternalRenderer.h"
#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <cstdio>
#include <cstdlib>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <cmath>

#include "../../../include/imgui/imgui.h"
#include "../objects/EngineWindow.h"
#include "../objects/Inspector.h"
#include "../objects/AssetManager.h"
#include "../objects/ToolBar.h"
#include "../objects/ViewPort.h"

struct InternalRenderer::Impl {
    virtual ~Impl() = default;
    static GLFWwindow* windows[1];
    struct FrameBuffer
    {
        virtual ~FrameBuffer() = default;
        GLuint fbo = 0;
        GLuint color = 0;
        GLuint depth = 0;
        int width = 0;
        int height = 0;
    };
    FrameBuffer viewportFB;
};

GLFWwindow* InternalRenderer::Impl::windows[1] = { nullptr };
InternalRenderer::InternalRenderer() : impl(new Impl())  {}
InternalRenderer::~InternalRenderer() { delete impl; }

int InternalRenderer::initGLFW() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    return 0;
}

int InternalRenderer::initGlad() {
    // FIX: Use reinterpret_cast for C++ style cast instead of C-style
    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }
    return 0;
}

int InternalRenderer::initImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    if (InternalRenderer::Impl::windows[0] == nullptr) {
        fprintf(stderr, "ImGui Error: No window found.\n");
        return -1;
    }

    ImGui_ImplGlfw_InitForOpenGL(InternalRenderer::Impl::windows[0], true);
    ImGui_ImplOpenGL3_Init("#version 120");

    return 0;
}

void InternalRenderer::destroyGLFW() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (InternalRenderer::Impl::windows[0]) {
        glfwDestroyWindow(InternalRenderer::Impl::windows[0]);
        InternalRenderer::Impl::windows[0] = nullptr;
    }
    glfwTerminate();
}

int InternalRenderer::initEngineWindow(Window *window) {
    if (!window) return -1;

        InternalRenderer::Impl::windows[0] = glfwCreateWindow(
        window->resolution[0],
        window->resolution[1],
        "Sausage Engine",
        nullptr,
        nullptr
    );

    if (!InternalRenderer::Impl::windows[0]) {
        printf("3.3 Core failed. Attempting fallback to 2.1...\n");
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

        InternalRenderer::Impl::windows[0] = glfwCreateWindow(
            window->resolution[0],
            window->resolution[1],
            "Sausage Engine",
            nullptr,
            nullptr
        );
    }

    if (!InternalRenderer::Impl::windows[0]) {
        fprintf(stderr, "Fatal: GPU support error\n");
        glfwTerminate();
        return -1;
    }

    glfwSetWindowUserPointer(InternalRenderer::Impl::windows[0], window);

    glfwSetWindowCloseCallback(InternalRenderer::Impl::windows[0], [](GLFWwindow* w) {
        auto* myWindow = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (myWindow) {
            myWindow->closed = true;
        }
    });

    glfwMakeContextCurrent(InternalRenderer::Impl::windows[0]);
    return 0;
}

void InternalRenderer::showInspector(Inspector *inspector) {
    if (!inspector) return;
    if (!inspector->visible) return;
    ImGui::ShowDemoWindow(&inspector->visible);
    ImGui::Begin("inspector");
    ImGui::End();
}

void InternalRenderer::showToolBar(ToolBar* toolbar) {
    if (!toolbar) return;
    if (!toolbar->visible) return;

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Scene")) {}
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) { /* Handle exit */ }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void InternalRenderer::showViewPort(ViewPort* viewport) {
    GLuint textureID = impl->viewportFB.color;
    uint32_t sceneTexture = static_cast<uint32_t>(textureID);
    if (!viewport || !viewport->visible) return;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Viewport", &viewport->visible);

    // Fill the window with the texture from your Framebuffer
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();

    // Cast the texture ID to ImTextureID for ImGui
    // Note: If sceneTexture is 0, this will just show a black square
    ImGui::Image((ImTextureID)(uintptr_t)sceneTexture, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
    ImGui::PopStyleVar();
}

void InternalRenderer::showAssetManager(AssetManager* assetManager) {
    if (!assetManager || !assetManager->visible) return;

    ImGui::Begin("Asset Manager", &assetManager->visible);

    if (ImGui::TreeNode("Scripts")) {
        ImGui::BulletText("PlayerController.cpp");
        ImGui::BulletText("EnemyAI.cpp");
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Textures")) {
        ImGui::BulletText("Sausage_Albedo.png");
        ImGui::BulletText("Ground_Normal.tga");
        ImGui::TreePop();
    }

    ImGui::End();
}

bool InternalRenderer::isEngineWindowShouldClose(int index) {
    return glfwWindowShouldClose(InternalRenderer::Impl::windows[index]);
}

void InternalRenderer::destroyWindow(int index) {

    if (index < 0 || index >= 1) return;

    if (InternalRenderer::Impl::windows[index]) {
        glfwDestroyWindow(InternalRenderer::Impl::windows[index]);
        InternalRenderer::Impl::windows[index] = nullptr;
    }
}

void InternalRenderer::BeginEngineRenderFrame() {

    glfwPollEvents();
    if (glfwGetKey(InternalRenderer::Impl::windows[0], GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(InternalRenderer::Impl::windows[0], 1);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    auto time = static_cast<float>(glfwGetTime());
    float red   = (sinf(time) * 0.5f) + 0.5f;
    float green = (sinf(time + 2.0f) * 0.5f) + 0.5f;
    float blue  = (sinf(time + 4.0f) * 0.5f) + 0.5f;

    glClearColor(red, green, blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void InternalRenderer::EndEngineRenderFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (InternalRenderer::Impl::windows[0]) {
        glfwSwapBuffers(InternalRenderer::Impl::windows[0]);
    }
}

void InternalRenderer::BeginViewPortRenderFrame() {

    auto& fb = impl->viewportFB;

    glBindFramebuffer(GL_FRAMEBUFFER, fb.fbo);
    glViewport(0, 0, fb.width, fb.height);

    auto time = static_cast<float>(glfwGetTime());
    float red   = (sinf(time) * 0.5f) + 0.5f;
    float green = (sinf(time + 2.0f) * 0.5f) + 0.5f;
    float blue  = (sinf(time + 4.0f) * 0.5f) + 0.5f;

    glClearColor(red, green, blue, 1.0f);

}

void InternalRenderer::EndViewPortRenderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



bool LoadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

bool InternalRenderer::CreateViewPortFrameBuffer(int width, int height) {
    auto& fb = impl->viewportFB;
    if (fb.fbo)
    {
        glDeleteFramebuffers(1, &fb.fbo);
        glDeleteTextures(1, &fb.color);
        glDeleteRenderbuffers(1, &fb.depth);
    }

    fb.width = width;
    fb.height = height;

    glGenFramebuffers(1, &fb.fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fb.fbo);

    // color texture
    glGenTextures(1, &fb.color);
    glBindTexture(GL_TEXTURE_2D, fb.color);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        fb.color,
        0);

    // depth
    glGenRenderbuffers(1, &fb.depth);
    glBindRenderbuffer(GL_RENDERBUFFER, fb.depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER,
        fb.depth);

    bool ok = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return ok;
}