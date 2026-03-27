//
// Created by unexpectcat on 3/18/26.
//

#ifndef SAUSAGEENGINE_SAUSAGEENGINEINSTANCE_H
#define SAUSAGEENGINE_SAUSAGEENGINEINSTANCE_H

#include  "renderer/InternalRenderer.h"
#include "renderer/ExternalRenderer.h"

namespace SE {
    void initSausageEngine(int argc, char** argv);
    void shutdownSausageEngine();
}



class SausageEngine {
public:
    SausageEngine();
    ~SausageEngine();

    bool Startup();
    void Run();

private:
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Window> m_window;
    bool m_isRunning;
};




#endif //SAUSAGEENGINE_SAUSAGEENGINEINSTANCE_H