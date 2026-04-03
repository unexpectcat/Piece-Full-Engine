//
// Created by unexpectcat on 3/12/26.
//

#ifndef SAUSAGEENGINE_V0_0_2_INTERNALRENDERER_H
#define SAUSAGEENGINE_V0_0_2_INTERNALRENDERER_H

#include <memory>
class Window;
class Inspector;
class ToolBar;
class ViewPort;
class AssetManager;
class InternalRenderer {


public:
    InternalRenderer();
    ~InternalRenderer();
    static int initGLFW();
    static int initGlad();
    static int initImGui();
    static void destroyGLFW();
    static int initEngineWindow(Window* window);
    static void showInspector(Inspector* inspector);
    static void showToolBar(ToolBar* toolbar);
    void showViewPort(ViewPort* viewport);
    static void showAssetManager(AssetManager* assetManager);
    static bool isEngineWindowShouldClose(int index);

public:
    static void destroyWindow(int index);
    static void BeginEngineRenderFrame();
    static void EndEngineRenderFrame();
    void BeginViewPortRenderFrame();
    void EndViewPortRenderFrame();
    bool CreateViewPortFrameBuffer(int width, int height);

private:
    struct Impl;
    Impl* impl;
};



#endif //SAUSAGEENGINE_V0_0_2_INTERNALRENDERER_H