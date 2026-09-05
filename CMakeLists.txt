cmake_minimum_required(VERSION 3.21)
project(PieceFullEngine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Keep every dependency a shared library and mark our own target the same way,
# so the exe/DLL doesn't statically absorb any of them.
set(BUILD_SHARED_LIBS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config_upper)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_upper} ${CMAKE_SOURCE_DIR}/bin)
endforeach()

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(unofficial-enet CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(PieceFullEngine
    src/main.cpp
        src/renderer/renderer.cpp
        src/renderer/renderer.h
        src/renderer/window.cpp
        src/renderer/window.h
        src/network/enet.cpp
        src/network/enet.h
)

target_include_directories(PieceFullEngine PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(PieceFullEngine PRIVATE
    glfw
    glm::glm
    assimp::assimp
    imgui::imgui
    nlohmann_json::nlohmann_json
    unofficial::enet::enet
    OpenGL::GL
)

# Ship the vcpkg-built shared libs (glfw3.dll, assimp-*.dll, etc.) next to the exe on Windows.
if(WIN32)
    add_custom_command(TARGET PieceFullEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:PieceFullEngine>
            $<TARGET_FILE_DIR:PieceFullEngine>
        COMMAND_EXPAND_LISTS
    )
endif()
