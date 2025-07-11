#include "pch.h"
#include "Particle.h"

Particle::Particle(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect screen, SDL_Rect* player, Vec2 velocity, float lifeTime) :
	Object(dest) {
	CenterObj(player);
	m_ren = ren;
	m_tex = tex;
	m_screen = screen;
	m_lifetime = lifeTime;
	m_velocity = velocity;
	m_isDead = false;
	m_opacity = 255;

	/*m_light = Light(ren, Vec2(m_screen.x, m_screen.y), 20, 50, { 255, 255, 255, 255 }, SDL_BLENDMODE_ADD);*/

	m_timer.Start();
}
Particle::Particle(const Particle& obj) : Object(obj.m_dest), m_isDead(obj.m_isDead), m_opacity(obj.m_opacity), m_lifetime(obj.m_lifetime), m_timer(obj.m_timer) {
	CenterObj(obj.m_playerRect);
	m_ren = obj.m_ren;
	m_tex = obj.m_tex;
	m_screen = obj.m_screen;
	m_velocity = obj.m_velocity;
}
Particle::~Particle() {
	m_timer.Stop();
}
Particle& Particle::operator=(const Particle& obj) {
	m_isDead = obj.m_isDead;
	m_opacity = obj.m_opacity;
	m_lifetime = obj.m_lifetime;
	m_timer = obj.m_timer;

	CenterObj(obj.m_playerRect);
	m_ren = obj.m_ren;
	m_tex = obj.m_tex;
	m_screen = obj.m_screen;
	m_dest = obj.m_dest;
	m_velocity = obj.m_velocity;

	return *this;
}
void Particle::Render() {
	if (m_lifetime > (static_cast<float>(m_timer.GetMili())) / 1000) {
		/*m_light.DrawLight();*/
		SDL_SetTextureAlphaMod(m_tex, m_opacity);
		if (m_ren != nullptr && m_tex != nullptr)
			SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
		SDL_SetTextureAlphaMod(m_tex, 0);
	}
}
void Particle::Update() {
	if (m_lifetime > (static_cast<float>(m_timer.GetMili()))/1000) {
		m_opacity -= rand()%8;
		Move();
		Render();
	}
	else {
		m_isDead = true;
	}
}
void Particle::Move() {
	ChangeDestPosFor(m_velocity);
	ChangeScreenPosFor(m_velocity);
}