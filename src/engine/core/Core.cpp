#include "Core.h"

#include "renderer/Renderer.h"
#include <iostream>

namespace Sausage {

    struct Core::Impl {
        Renderer renderer = Renderer();
    };

    Core::Core() : impl(new Impl{}) {}
    Core::~Core() {
        delete impl;
    }
    

    

    void Core::testRun() {
        int width = 800;
        int height = 600;
        std::string title = "My Window";

        int result = impl->renderer.Init(width, height, title);
        if (result != 0) {
            std::cout << "Failed to initialize renderer!\n";
            return;
        }

        while (impl->renderer.isEngineWindowOpen())
        {
            impl->renderer.DrawFrame();
        }

        impl->renderer.Clear();
    }

}
