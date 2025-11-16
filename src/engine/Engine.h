#pragma once

#include "core/Core.h"
#include "renderer/Renderer.h"
#include "scene/Scene.h"

#pragma once
#include <memory>
#include <string>

namespace Sausage {

    class Engine {
    public:
        Engine();
        ~Engine();

        void Init(const std::string& title, int width, int height);
        void Run();

        std::shared_ptr<Scene> GetCurrentScene();

    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl; // PImpl to hide internal details
    };

}