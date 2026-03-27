//
// Created by unexpectcat on 3/21/26.
//
#include "ExternalRenderer.h"
#include "InternalRenderer.h"
#include "../objects/window.h"
struct Renderer::InternalImpl {
    InternalRenderer service;
    Window *window;
};

Renderer::Renderer() : m_internal(new InternalImpl()) {}

Renderer::~Renderer() {
    delete m_internal;
}

void Renderer::init(Window *window) {
    m_internal->service.initGLFW();
    m_internal->service.initEngineWindow(window);
    m_internal->service.initGlad();
    m_internal->service.initImGui();
}


void Renderer::renderFrame() {

    m_internal->service.BeginDrawFrame();

    // Logic to update the Window class state from GLFW
    // m_internal->service.syncWindowState(window);

    m_internal->service.EndDrawFrame();
}

void Renderer::destroyWindow(int index) {
    m_internal->service.destroyWindow(index);
}

void Renderer::isEngineWindowShouldClose(int index) {
}
