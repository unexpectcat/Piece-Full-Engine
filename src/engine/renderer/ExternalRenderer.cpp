//
// Created by unexpectcat on 3/21/26.
//
#include "ExternalRenderer.h"
#include "InternalRenderer.h"
#include "../objects/EngineWindow.h"
#include "../objects/Inspector.h"
#include "../objects/AssetManager.h"
#include "../objects/ToolBar.h"
#include "../objects/ViewPort.h"

struct Renderer::InternalImpl {
    InternalRenderer service;
    Window *window = nullptr;

    Inspector* inspector[4];
    ViewPort* viewPort[4];
    AssetManager* assetManager[4];

    ToolBar* toolBar = nullptr;

    ~InternalImpl() {
        for (int i = 0; i < 4; ++i) {
            delete inspector[i];
            delete viewPort[i];
            delete assetManager[i];
        }
        delete toolBar;
    }
};

Renderer::Renderer() : m_internal(new InternalImpl()) {
    for (Inspector* &inspector : m_internal->inspector) {
        inspector = new Inspector();
    }

    for (ViewPort* &view_port : m_internal->viewPort) {
        view_port = new ViewPort();
    }

    for (AssetManager* &asset_manager : m_internal->assetManager) {
        asset_manager = new AssetManager();
    }

    m_internal->toolBar = new ToolBar();


}

Renderer::~Renderer() {
    delete m_internal;
}

void Renderer::init(Window *window) {

    m_internal->service.initGLFW();
    m_internal->service.initEngineWindow(window);
    m_internal->service.initGlad();
    m_internal->service.initImGui();
    m_internal->toolBar->visible = true;
    m_internal->inspector[0]->visible = true;
    m_internal->viewPort[0]->visible = true;
    m_internal->assetManager[0]->visible = true;
}


void Renderer::renderFrame() {

    m_internal->service.CreateViewPortFrameBuffer(200, 200);
    m_internal->service.BeginEngineRenderFrame();
    m_internal->service.BeginViewPortRenderFrame();
    m_internal->service.EndViewPortRenderFrame();

    for (Inspector* &inspector : m_internal->inspector) {
        InternalRenderer::showInspector(inspector);
    }

    for (ViewPort* &view_port : m_internal->viewPort) {
        m_internal->service.showViewPort(view_port);
    }

    for (AssetManager* &asset_manager : m_internal->assetManager) {
        m_internal->service.showAssetManager(asset_manager);
    }

    m_internal->service.showToolBar(m_internal->toolBar);
    m_internal->service.EndEngineRenderFrame();



}

void Renderer::destroyWindow(int index) {
    m_internal->service.destroyWindow(index);
}

void Renderer::isEngineWindowShouldClose(int index) {
}
