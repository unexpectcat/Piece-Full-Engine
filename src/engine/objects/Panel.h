//
// Created by unexpectcat on 4/3/26.
//

#ifndef SAUSAGEENGINE_PANEL_H
#define SAUSAGEENGINE_PANEL_H


class Panel {

public:
    Panel() : visible(false) {};
    ~Panel() = default;


    int width, height;
    bool visible;
};


#endif //SAUSAGEENGINE_PANEL_H