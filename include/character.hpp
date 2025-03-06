#pragma once
#include "entity.hpp"
#include "inventory.hpp"
#include "sprite.hpp"
#include "animator.hpp"
#include <string>


class Character : public Entity
{
protected:
	struct
	{
		float accel;
		float maxWalkSpeed;
		float maxRunSpeed;
		float damping;
		Vector2* velocity;

		bool running;
	} m_movementVars;
	struct
	{
		Sprite sprCharacter;
		float scaleX;
		float scaleY;
		float offsetX;
		float offsetY;
		Animator animator;

		int facingXDir;
		float walkSpeed;
		bool walking;
	} m_spriteVars;
	Inventory m_inventory;

	virtual void Draw(void);
	virtual void Animate(void);
	void Move(Vector2 direction);

public:
	Character(int health, float posX, float posY);
	~Character(void);

	virtual void Update(float deltaTime);

};