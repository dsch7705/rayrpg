#pragma once
#include "entity.hpp"
#include "texture.hpp"


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

	Texture* m_texCharacter;

public:
	Player(int health, float posX, float posY);
	void Update(float deltaTime) override;
	void Draw(void) override;

	void Move(float deltaTime);
};