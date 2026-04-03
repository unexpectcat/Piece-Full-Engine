//
// Created by unexpectcat on 3/12/26.
//

#include "InternalRenderer.h"
#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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
};

GLFWwindow* InternalRenderer::Impl::windows[1] = { nullptr };


InternalRenderer::InternalRenderer() : impl(new Impl()) {}
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

    // A simple top-aligned bar

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

void InternalRenderer::showViewPort(ViewPort* viewport, uint32_t sceneTexture) {
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

void InternalRenderer::BeginDrawFrame() {
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
    glClear(GL_COLOR_BUFFER_BIT);
}

void InternalRenderer::EndDrawFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (InternalRenderer::Impl::windows[0]) {
        glfwSwapBuffers(InternalRenderer::Impl::windows[0]);
    }
}