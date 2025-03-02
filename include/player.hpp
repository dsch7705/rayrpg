#pragma once
#include "entity.hpp"
#include "sprite.hpp"


class Player : public Entity
{
private:
	struct
	{
		float accel;
		float maxVel;
		float damping;
		Vector2* velocity;
	} m_movementVars;

	Sprite m_sprCharacterIdle;
	Sprite m_sprCharacterWalk;

public:
	Player(int health, float posX, float posY);
	void Update(float deltaTime) override;
	void Draw(void) override;

	void Move(float deltaTime);
};