#pragma once





class Scene {
private:
    GLuint framebuffer, textureColorbuffer, rbo;

    //clear screen color
    

public:

    const GLfloat ss_R = 0.9f, ss_G = 0.8f, ss_B = 0.0f, ss_A = 1.0f;

    void InitVertexBuffer();

    void InitFramebuffer(int width, int height);

    void RenderToFramebuffer();

    void Render();

    GLuint GetRenderedTexture();

    virtual ~Scene() = default; // Virtual destructor for proper cleanup of derived classes
};

