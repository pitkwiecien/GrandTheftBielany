#pragma once
#include "ISystem.hpp"

class Renderer;
class Camera;

// obsluguje warstwe graficzna.
class RenderSystem {
    public:
        RenderSystem(Renderer& renderer, Camera& camera);
        void render(Registry& reg);

    private:
        Renderer& m_renderer;
        Camera&   m_camera;
};
