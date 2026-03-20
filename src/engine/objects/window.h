//
// Created by unexpectcat on 3/12/26.
//

#ifndef SAUSAGEENGINE_V0_0_2_WINDOW_H
#define SAUSAGEENGINE_V0_0_2_WINDOW_H


class Window {



public:


    int resolution[2];
    Window(int w, int h) : resolution{w, h} {}

    ~Window() = default;

    int createWindow();
    void setCurrentContextNull();
    void bindImguiContext();
    bool isOpen();
    void BeginDrawFrame();
    void EndDrawFrame();
    void Shutdown();

private:
    struct Impl;
    Impl* impl;
};


#endif //SAUSAGEENGINE_V0_0_2_WINDOW_H