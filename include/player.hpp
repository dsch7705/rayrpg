#pragma once
#include "entity.hpp"
#include "inventory.hpp"
#include "sprite.hpp"
#include "animator.hpp"


class Player : public Entity
{
private:
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
		Sprite sprSoldier;
		Animator animator;

		int facingXDir;
		float walkSpeed;

		bool walking;
		bool attack;
	} m_animVars;

	Inventory m_inventory;

public:
	Player(int health, float posX, float posY);
	~Player(void);

	void Update(float deltaTime) override;
	void Draw(void) override;
	void Animate(Vector2 inputVec);

	void Move(float deltaTime);
};