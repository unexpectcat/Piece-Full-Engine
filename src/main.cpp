#include "engine/SausageEngine.h"

int main(int argc, char** argv)
{
    auto engine = std::make_unique<SausageEngine>();

    if (!engine->Startup()) {
        return -1;
    }

    engine->Run();
    return 0;
}