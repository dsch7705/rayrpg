#pragma once
#include "sprite.hpp"
#include <unordered_map>
#include <string>

#define DEFAULT_ANIMATOR_FPS 10


class Animator
{
private:
	std::unordered_map<std::string, Sprite*> m_states;
	Sprite* m_currentState;

	unsigned int m_frameRate;
	float m_timeOnCurrentFrame;

public:
	Animator();
	Animator(unsigned int frameRate);
	void Update(float deltaTime);

	void AddState(const std::string& stateName, Sprite* sprite);
	void RemoveState(const std::string& stateName);
	void SetCurrentState(const std::string& stateName);
	Sprite* GetCurrentState(void);

};