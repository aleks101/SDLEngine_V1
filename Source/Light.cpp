#include "pch.h"
#include "Light.h"

Light::Light(SDL_Renderer* ren, Vec2 pos, float radius, float intensity, SDL_Color color, SDL_BlendMode mode) :
	m_ren(ren), m_pos(pos), m_radius(radius), m_intensity(intensity), m_color(color), m_blendType(mode) {

}
Light::Light() {

}
Light::Light(const Light& light) {
    m_ren = light.m_ren;
    m_radius = light.m_radius;
    m_pos = light.m_pos;
    m_intensity = light.m_intensity;
    m_color = light.m_color;
    m_blendType = light.m_blendType;
}
void Light::DrawLight() {
    // Calculate the squared radius for performance optimization
    int lightRadiusSquared = m_radius * m_radius;

    // Set blend mode to enable additive blending for lighting effect
    SDL_SetRenderDrawBlendMode(m_ren, m_blendType);

    // Iterate through each pixel within the light's radius
    for (int dy = -m_radius; dy <= m_radius; ++dy) {
        for (int dx = -m_radius; dx <= m_radius; ++dx) {
            // Calculate the squared distance from the light source
            int distanceSquared = dx * dx + dy * dy;

            // Apply the lighting effect only if the pixel is within the light's radius
            if (distanceSquared <= lightRadiusSquared) {
                // Calculate the alpha value based on the distance from the light source
                int alpha = m_intensity - (m_intensity * distanceSquared) / lightRadiusSquared;

                // Set the render draw color with the alpha value
                SDL_SetRenderDrawColor(m_ren, 255, 255, 255, alpha);

                // Draw a single pixel at (x + dx, y + dy) with the calculated alpha value
                SDL_RenderDrawPoint(m_ren, m_pos.x + dx, m_pos.y + dy);
            }
        }
    }
}
void Light::ChangeColor(SDL_Color color) {
    m_color = color;
}
void Light::ChangeIntensity(float intensity) {
    m_intensity = intensity;
}
void Light::ChangePos(Vec2 pos) {
    m_pos = pos;
}
void Light::ChangeRadius(float radius) {
    m_radius = radius;
}