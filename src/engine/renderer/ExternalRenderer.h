//
// Created by unexpectcat on 3/21/26.
//

#ifndef SAUSAGEENGINE_EXTERNALRENDERER_H
#define SAUSAGEENGINE_EXTERNALRENDERER_H


class Window;
class Renderer {
public:
    Renderer();
    ~Renderer();
    void init(Window* window);
    void renderFrame();
    void destroyWindow(int index);
    void isEngineWindowShouldClose(int index);
private:
    struct InternalImpl;
    InternalImpl* m_internal;
};

#endif //SAUSAGEENGINE_EXTERNALRENDERER_H