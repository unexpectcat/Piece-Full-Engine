//
// Created by unexpectcat on 3/18/26.
//

#include "SausageEngine.h"
#include "objects/EngineWindow.h"
#include <memory>

#include "objects/Inspector.h"

SausageEngine::SausageEngine()
    : m_isRunning(false),
      m_renderer(std::make_unique<Renderer>()),
      m_window(std::make_unique<Window>(720, 480))
{
    // Constructor body can stay empty now
}

SausageEngine::~SausageEngine() = default;

bool SausageEngine::Startup() {
    m_renderer->init(m_window.get());
    m_isRunning = true;
    return true;
}

void SausageEngine::Run() {
    while (m_isRunning) {
        m_renderer->renderFrame();

        if (m_window->closed) {
            m_isRunning = false;
            m_renderer->destroyWindow(0);
        }
    }
}