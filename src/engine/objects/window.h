//
// Created by unexpectcat on 3/12/26.
//

#ifndef SAUSAGEENGINE_V0_0_2_WINDOW_H
#define SAUSAGEENGINE_V0_0_2_WINDOW_H


class Window {



public:


    int resolution[2];
    bool isOpen = true;

    Window(int w, int h) : resolution{w, h} {}

    ~Window() = default;



};


#endif //SAUSAGEENGINE_V0_0_2_WINDOW_H