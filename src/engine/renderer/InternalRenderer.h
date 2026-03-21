//
// Created by ahd on 3/12/26.
//

#ifndef SAUSAGEENGINE_V0_0_2_INTERNALRENDERER_H
#define SAUSAGEENGINE_V0_0_2_INTERNALRENDERER_H

#include "../objects/window.h"

class InternalRenderer {


public:
    InternalRenderer();
    ~InternalRenderer();

    static int initGLFW();
    static int initGlad();
    static int initImGui();
    static void destroyGLFW();
    static int initEngineWindow(const Window *window);
    static bool isEngineWindowOpen();
    static void destroyWindow(Window *window);
    static void BeginDrawFrame();
    static void EndDrawFrame();

private:
    struct Impl;
    Impl* impl;
};



#endif //SAUSAGEENGINE_V0_0_2_INTERNALRENDERER_H