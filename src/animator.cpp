#include "animator.hpp"
#include "util.hpp"
#include <cassert>


AnimationState::AnimationState(const std::string& name, Sprite* sprite, unsigned int frameCount, unsigned int rowOffset, bool loop, bool reverse, unsigned int frameRate)
	: name(name), sprite(sprite), loop(loop), reverse(reverse), done(false), frameRate(frameRate), currentFrame(0), frameCount(frameCount)
{
	m_frameStartIdx = rowOffset * (sprite->sheetWidth / sprite->width);
	m_timeOnCurrentFrame = 0.f;
}
void AnimationState::Update(float deltaTime)
{
	m_timeOnCurrentFrame += deltaTime;
	if (m_timeOnCurrentFrame > 1.f / frameRate)
	{
		reverse ? StepBackward() : StepForward();
		m_timeOnCurrentFrame = 0.f;
	}
}
void AnimationState::StepForward()
{
	if (currentFrame + 1 > frameCount - 1)
	{
		if (loop)
			currentFrame = 0;
		else
			done = true;
		return;
	}
	currentFrame++;
}
void AnimationState::StepBackward()
{
	if (currentFrame - 1 < 0)
	{
		if (loop)
			currentFrame = frameCount - 1;
		else
			done = true;
		return;
	}
	currentFrame--;
}
void AnimationState::Reset()
{
	currentFrame = 0;
	done = false;
	m_timeOnCurrentFrame = 0.f;
}


Transition::Transition(const std::string& to, bool* conditionPtr, bool invert)
	: to(to), m_conditionPtr(conditionPtr), invert(invert)
{
}


void Animator::Update(float deltaTime)
{
	if (m_currentState == nullptr)
		return;

	// Update state
	transitionList_t& transitionList = m_transitions.at(m_currentState->name);
	for (const Transition& tr : transitionList)
	{
		if (*tr.m_conditionPtr == !tr.invert)
		{
			DebugPrint(All, "%s\n", tr.to.c_str());
			// Transition to new state
			SetCurrentState(tr.to);
			break;
		}
	}

	m_currentState->Update(deltaTime);
	m_currentState->sprite->SetFrameIndex(m_currentState->m_frameStartIdx + m_currentState->currentFrame);
}

AnimationState* Animator::AddState(AnimationState state)
{
	m_states.emplace(std::make_pair(state.name, state));
	return &m_states.at(state.name);
}
void Animator::RemoveState(const std::string& stateName)
{
	m_states.erase(stateName);
}
void Animator::SetCurrentState(const std::string& stateName)
{
	AnimationState* state = &m_states.at(stateName);
	if (state == nullptr)
	{
		DebugPrint(DebugLevel::Error, "'%s' is not a valid state.\n", stateName);
		assert(state != nullptr);
	}

	if (state == m_currentState)
		return;
	//DebugPrint(DebugLevel::All, "%x | %x : %s\n", state, m_currentState, state->name.c_str());

	m_currentState = state;
	m_currentState->Reset();
}
AnimationState* Animator::GetCurrentState()
{
	return m_currentState;
}
AnimationState* Animator::GetState(const std::string& stateName)
{
	if (m_states.count(stateName) < 1)
		return nullptr;

	return &m_states.at(stateName);
}

void Animator::AddTransition(const std::string& from, const std::string& to, bool* conditionPtr, bool invert)
{
	if (m_transitions.count(from) < 1)
		m_transitions.insert(std::make_pair(from, transitionList_t()));

	transitionList_t& transitionList = m_transitions.at(from);
	transitionList.emplace_back(Transition(to, conditionPtr, invert));
}
void Animator::AddTransition2Way(const std::string& from, const std::string& to, bool* conditionPtr, bool invert)
{
	AddTransition(from, to, conditionPtr, invert);
	AddTransition(to, from, conditionPtr, !invert);
}