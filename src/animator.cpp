#include "animator.hpp"


Animator::Animator(unsigned int frameRate)
{
	m_currentState = nullptr;
	m_frameRate = frameRate;
	m_timeOnCurrentFrame = 0.f;
}
Animator::Animator() : Animator::Animator(DEFAULT_ANIMATOR_FPS)
{
}
void Animator::Update(float deltaTime)
{
	m_timeOnCurrentFrame += deltaTime;
	if (m_timeOnCurrentFrame > 1.f / m_frameRate)
	{
		m_currentState->FrameStepForward();
		m_timeOnCurrentFrame = 0.f;
	}
}

void Animator::AddState(const std::string& stateName, Sprite* sprite)
{
	m_states.insert(std::make_pair(stateName, sprite));
}
void Animator::RemoveState(const std::string& stateName)
{
	m_states.erase(stateName);
}
void Animator::SetCurrentState(const std::string& stateName)
{
	Sprite* state = m_states.at(stateName);
	if (state == m_currentState)
		return;

	m_currentState = m_states.at(stateName);
	m_currentState->FrameSetIndex(0);
}
Sprite* Animator::GetCurrentState()
{
	return m_currentState;
}