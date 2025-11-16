#pragma once
namespace Sausage {
    class Renderer; // forward declaration

    class Core {
    public:
        Core();
        ~Core();
        void testRun();


    private:
        struct Impl;
        Impl* impl;
    };
}

