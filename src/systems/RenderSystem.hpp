#pragma once
#include "ISystem.hpp"

class Renderer;
class Camera;

// Jedyny system dotykający warstwy graficznej.
// Sortuje sprite'y po layer, przelicza świat->ekran przez Camera,
// rysuje tylko to, co jest w widoku (culling).
// NIE dziedziczy po ISystem::update (potrzebuje Renderer), ma własny render().
class RenderSystem {
public:
    RenderSystem(Renderer& renderer, Camera& camera);
    void render(Registry& reg);

private:
    Renderer& m_renderer;
    Camera&   m_camera;
};
