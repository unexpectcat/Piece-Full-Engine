# Sausage  
MIT Licensed

Sausage is a lightweight, modular C++ game engine using **OpenGL** for rendering and **ImGui** for in-engine tooling.  
It is designed to be simple to integrate, easy to extend, and free of unnecessary abstraction layers.  
The goal is to provide a clean foundation for small-to-medium games, editor tools, and graphics experiments.

---

## Features
- OpenGL-based renderer with minimal overhead  
- ImGui editor layer with docking and custom panels  
- Clear module boundaries to prevent header replication  
- Asset loading for textures, shaders, and models  
- Scene system with entities and components  
- Cross-platform windowing and input  
- Fully open under the MIT License

---

## Architecture Overview

### Core Layer  
Provides fundamental engine utilities required by all other modules.  
Includes:
- Application and main loop management  
- Input handling  
- Timing utilities  
- Logging  
- Event dispatching  

**Dependencies:** none  

---

### Platform Layer  
Wraps OS-level functionality.  
Includes:
- Window creation  
- GL context initialization  
- High-resolution timing  
- Filesystem access  

**Dependencies:** core  

---

### Rendering Layer (OpenGL)  
Maintains all GPU-related code while avoiding global OpenGL state leaks.  
Includes:
- Renderer front-end API  
- Shader system  
- Mesh and buffer management  
- Texture and framebuffer abstractions  
- Viewport and camera utilities  

**Dependencies:** core, platform  

---

### Scene Layer  
Represents engine world objects and systems.  
Includes:
- Entities and components (ECS or hybrid model)  
- Transform system  
- Scene serialization and loading  
- Resource registry for assets  

**Dependencies:** renderer  

---

### UI Layer (ImGui)  
ImGui-based interface for debugging, profiling, and custom editor tools.  
Includes:
- ImGui context setup  
- Panels (scene hierarchy, inspector, logs, statistics)  
- Editor overlays such as gizmos or debug geometry  

**Dependencies:** scene  

---

### Editor (Optional)  
A standalone executable that uses all engine modules to provide development tooling.  
Includes:
- Layout persistence  
- Project configuration  
- Asset browser  
- Scene editing  

**Dependencies:** ui  

---

## Include and Module Organization

Sausage follows a strict, single-direction dependency flow:

