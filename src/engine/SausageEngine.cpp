//
// Created by unexpectcat on 3/18/26.
//

#include "SausageEngine.h"
#include "renderer/internalRenderer.h"
#include "objects/EngineWindow.h"



void SE::initSausageEngine() {
    internalRenderer::initGLFW();

    EngineWindow *engine_main_window = new EngineWindow(720, 480);
    int create_window_error = engine_main_window->createWindow();

    if (create_window_error == -1) {
        return;
    }
    internalRenderer::initGlad();

    while (engine_main_window->isOpen()) {
        engine_main_window->BeginDrawFrame();


        engine_main_window->EndDrawFrame();
    }

    engine_main_window->Shutdown();
    delete engine_main_window;
}

void SE::shutdownSausageEngine() {

}
