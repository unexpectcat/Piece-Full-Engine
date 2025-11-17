#pragma once

class Window;  
class Camera;

#include <string>

namespace Sausage {

    class Renderer {
    public:
        Renderer();
        ~Renderer();
        int Init(int width, int height, const std::string& title);
        void SetTarget(Window* window);
        void Clear();
        void DrawFrame();
        bool isEngineWindowOpen();
    private:
        struct Impl;
        Impl* impl;
    };
}