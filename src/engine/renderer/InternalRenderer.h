//
// Created by unexpectcat on 3/12/26.
//

#ifndef SAUSAGEENGINE_V0_0_2_INTERNALRENDERER_H
#define SAUSAGEENGINE_V0_0_2_INTERNALRENDERER_H

#include <memory>
class Window;
class InternalRenderer {


public:
    InternalRenderer();
    ~InternalRenderer();

    static int initGLFW();
    static int initGlad();
    static int initImGui();
    static void destroyGLFW();
    static int initEngineWindow(Window* window);
    static bool isEngineWindowShouldClose(int index);
    static void destroyWindow(int index);
    static void BeginDrawFrame();
    static void EndDrawFrame();

private:
    struct Impl;
    Impl* impl;
};



#endif //SAUSAGEENGINE_V0_0_2_INTERNALRENDERER_H