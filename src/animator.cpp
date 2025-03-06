#include "animator.hpp"
#include "util.hpp"


AnimationState::AnimationState(const std::string& name, Sprite* sprite, unsigned int frameCount, unsigned int rowOffset, bool loop, bool reverse, unsigned int frameRate)
	: name(name), sprite(sprite), loop(loop), reverse(reverse), done(false), frameRate(frameRate), currentFrame(0), frameCount(frameCount)
{
	m_frameStartIdx = rowOffset * (sprite->sheetWidth / sprite->width);
	m_lastFrameIdx = m_frameStartIdx;
	m_timeOnCurrentFrame = 0.f;
}
void AnimationState::Update(float deltaTime)
{
	m_timeOnCurrentFrame += deltaTime;
	m_lastFrameIdx = currentFrame;
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

bool AnimationState::IsFrameOnce(unsigned int frameIdx)
{
	if (m_lastFrameIdx == currentFrame)
		return false;

	if (currentFrame == frameIdx)
		return true;

	return false;
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
	AnimationState* statePtr = &m_states.at(state.name);

	if (m_defaultState == nullptr)
		m_defaultState = statePtr;

	return statePtr;
}
void Animator::RemoveState(const std::string& stateName)
{
	m_states.erase(stateName);
}
void Animator::SetDefaultState(const std::string& stateName)
{
	if (m_states.count(stateName) < 1)
	{
		DebugPrint(DebugLevel::Warning, "Animator::SetDefaultState(): '%s' is not a valid state.", stateName.c_str());
		return;
	}

	AnimationState* statePtr = &m_states.at(stateName);
	m_defaultState = statePtr;
}
void Animator::SetCurrentState(const std::string& stateName)
{
	if (m_states.count(stateName) < 1)
	{
		DebugPrint(DebugLevel::Warning, "Animator::SetCurrentState(): '%s' is not a valid state.", stateName.c_str());
		return;
	}

	AnimationState* statePtr = &m_states.at(stateName);
	if (statePtr == m_currentState)
		return;

	m_currentState = statePtr;
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