#pragma once
#include "sprite.hpp"
#include <unordered_map>
#include <list>
#include <string>

#define DEFAULT_ANIMATOR_FPS 7


struct AnimationState
{
private:
	unsigned int m_frameStartIdx;
	float m_timeOnCurrentFrame;

	void Update(float deltaTime);
	void StepForward(void);
	void StepBackward(void);

public:
	std::string name;
	Sprite* sprite;

	unsigned int frameCount;
	unsigned int frameRate;
	unsigned int currentFrame;

	bool loop;
	bool reverse;
	bool done;

	AnimationState(const std::string& name, Sprite* sprite, unsigned int frameCount, unsigned int rowOffset=0, 
		bool loop=true, bool reverse=false, unsigned int frameRate=DEFAULT_ANIMATOR_FPS);
	friend class Animator;

	void Reset(void);
};
struct Transition
{
private:
	bool* m_conditionPtr;

public:
	std::string to;
	bool invert;

	Transition(const std::string& to, bool* conditionPtr, bool invert = false);
	friend class Animator;

};
class Animator
{
private:
	std::unordered_map<std::string, AnimationState> m_states;
	typedef std::list<Transition> transitionList_t;
	std::unordered_map<std::string, transitionList_t> m_transitions;
	AnimationState* m_currentState;

public:
	Animator(void) : m_currentState(nullptr) {}
	void Update(float deltaTime);

	AnimationState* AddState(AnimationState state);
	void RemoveState(const std::string& stateName);
	void SetCurrentState(const std::string& stateName);
	AnimationState* GetCurrentState(void);
	AnimationState* GetState(const std::string& stateName);

	void AddTransition(const std::string& from, const std::string& to, bool* conditionPtr, bool invert = false);
	void AddTransition2Way(const std::string& from, const std::string& to, bool* conditionPtr, bool invert = false);

};