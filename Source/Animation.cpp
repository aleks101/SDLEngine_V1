#include "pch.h"
#include "Animation.h"
#include "TimeD.h"

Animation::Animation() : m_frameDuration(nullptr), m_srcRect(nullptr), m_startX(0), m_width(0){
	m_loop = false;
	m_finished = false;
	m_currFrame = 0;
	m_time = 0;
	m_row = 0;
	m_stop = false;
	m_frames = 0;
}
Animation::Animation(const Animation& ani) {
	m_loop = ani.m_loop;
	m_stop = ani.m_stop;
	m_finished = ani.m_finished;
	m_frames = ani.m_frames;
	m_currFrame = ani.m_currFrame;

	m_frameDuration = new float[m_frames];
	for (int i = 0; i < m_frames; i++)
		m_frameDuration[i] = ani.m_frameDuration[i];
	m_time = ani.m_time;
	m_row = ani.m_row;
	m_startX = ani.m_startX;
	m_width = ani.m_width;
	m_srcRect = ani.m_srcRect;
}
Animation::~Animation() {
	Clean();
}
void Animation::Init(SDL_Rect* sourceRect, int startX, int startY, int width, int height, int frames) {
	m_srcRect = sourceRect;
	m_srcRect->x = startX;
	m_startX = startX;
	m_width = width;
	m_startY = startY;
	m_height = height;
	m_frames = frames;

	m_frameDuration = new float[frames];
	for (int i = 0; i < frames; i++)
		m_frameDuration[i] = 0;
	m_loop = false;
	m_finished = false;
	m_currFrame = 0;
	m_time = 0;
	m_row = 0;
	m_stop = false;
	m_srcRect->w = m_width;
}
void Animation::Clean() {
	if (m_frameDuration != NULL)
		delete m_frameDuration;
	m_frameDuration = NULL;
}
void Animation::SetFrameDuration(int frame, float duration) {
	if (frame < m_frames)
		m_frameDuration[frame] = duration;
}
void Animation::Animate() {
	if (!m_stop) {
		if (m_loop)
			m_finished = false;
		if (!m_finished) {
			m_srcRect->x = m_startX + m_width * m_currFrame;

			if (m_frameDuration != nullptr && m_frameDuration[m_currFrame] <= m_time) {
				m_time = 0;
				m_currFrame++;
			}
			if (m_currFrame >= m_frames) {
				m_currFrame = 0;
				m_finished = true;
			}
			m_time += TimeD::DeltaTime();
		}
	}
}
void Animation::SetLooping(bool loop) {
	m_loop = loop;
}
bool Animation::IsFinished() {
	return m_finished;
}
void Animation::SkipToFrame(int frame) {
	m_currFrame = frame;
}
void Animation::Start() {
	m_finished = false;
}
void Animation::Stop() {
	m_stop = true;
}
void Animation::Resume() {
	m_stop = false;
}
void Animation::Reset() {
	m_currFrame = 0;
	m_time = 0;
}