//
// Created by unexpectcat on 9/5/26.
//
#include "enet.h"

#include <cstdio>

#include <enet/enet.h>


int enet::initialize()
{
    if (enet_initialize() != 0) {
        std::fprintf(stderr, "Failed to initialize ENet\n");
        return 1;
    }

    ENetAddress address{};
    address.host = ENET_HOST_ANY;
    address.port = 0;
    ENetHost* enetHost = enet_host_create(&address, 1, 1, 0, 0);
    if (!enetHost) {
        std::fprintf(stderr, "Failed to create ENet host\n");
        enet_deinitialize();
        return 1;
    }
    enet_host_destroy(enetHost);
    enet_deinitialize();
    return 0;
}
