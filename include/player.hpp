#pragma once
#include "character.hpp"


class Player : public Character
{
private:
	struct
	{
		bool attack;
		bool attackHeavy;
	} m_spriteVars;

	void Move(float deltaTime);
	void Attack(void);

public:
	Player(int health, float posX, float posY);
	~Player(void);

	void Update(float deltaTime) override;
	void Draw(void) override;
	void Animate(void) override;

};