//
// Created by ahd on 3/12/26.
//


#include "core.h"
#include "../renderer/internalRenderer.h"
#include  "../objects/window.h"

void initSausageEngine() {

    internalRenderer::initGLFW();

    Window *current_window = new Window(720, 480);
    int create_window_error = current_window->createWindow();

    if (create_window_error == -1) {
        return;
    }
    internalRenderer::initGlad();

    while (current_window->isOpen()) {
        current_window->BeginDrawFrame();


        current_window->EndDrawFrame();
    }
    current_window->Shutdown();
    delete current_window;
}
