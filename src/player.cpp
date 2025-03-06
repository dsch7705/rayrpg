#include "player.hpp"
#include "util.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <iostream>


Player::Player(int health, float posX, float posY) : Character(health, posX, posX)
{
	m_movementVars.maxWalkSpeed = 125.f;
	m_movementVars.maxRunSpeed = 250.f;

	auto& c_spriteVars = Character::m_spriteVars;
	// Load animation states
	c_spriteVars.sprCharacter = Sprite("Knight.png", 8, 11);
	Animator& anim = c_spriteVars.animator;
	anim.AddState(AnimationState("idle", &c_spriteVars.sprCharacter, 6, 0, true, false, 6));
	anim.AddState(AnimationState("walk", &c_spriteVars.sprCharacter, 8, 1));
	anim.AddState(AnimationState("attack1", &c_spriteVars.sprCharacter, 7, 2, false, false, 15));
	anim.AddState(AnimationState("attack2", &c_spriteVars.sprCharacter, 10, 3, false, false, 15));
	anim.AddState(AnimationState("attack3", &c_spriteVars.sprCharacter, 11, 4, false, false, 15));
	anim.SetCurrentState("idle");
	
	// Transitions
	anim.AddTransition("idle", "attack1", &m_spriteVars.attack);
	anim.AddTransition("attack1", "idle", &anim.GetState("attack1")->done);

	anim.AddTransition("idle", "attack3", &m_spriteVars.attackHeavy);
	anim.AddTransition("attack3", "idle", &anim.GetState("attack3")->done);

	anim.AddTransition("walk", "attack2", &m_spriteVars.attack);
	anim.AddTransition("attack2", "walk", &anim.GetState("attack2")->done);

	anim.AddTransition("walk", "attack3", &m_spriteVars.attackHeavy);
	anim.AddTransition("attack3", "walk", &anim.GetState("attack3")->done);

}
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	Move(deltaTime);
	Attack();

	Character::Update(deltaTime);
}

bool inventoryIsOpen = false;
void Player::Draw()
{	
	Character::Draw();

	// Open inventory
	if (IsKeyPressed(KEY_TAB))
		inventoryIsOpen = !inventoryIsOpen;
	if (inventoryIsOpen)
		m_inventory.Draw();
}
void Player::Animate()
{
	Character::Animate();
}

void Player::Move(float deltaTime)
{
	m_movementVars.running = IsKeyDown(KEY_LEFT_SHIFT);

	Vector2 inputVec = Vector2{ float(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)), float(IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) };
	Character::Move(inputVec);
}
void Player::Attack()
{
	m_spriteVars.attack = IsKeyPressed(KEY_C);

	auto& c_spriteVars = Character::m_spriteVars;
	Animator& anim = c_spriteVars.animator;
	AnimationState& currentState = *anim.GetCurrentState();

	if (currentState.name == "attack1")
	{
		const unsigned int damageHitFrame = 3;
		if (currentState.IsFrameOnce(damageHitFrame))
			DebugPrint(DebugLevel::Info, "Hit!");
	}
	else if (currentState.name == "attack2")
	{
		const unsigned int damangeHitFrame1 = 3;
		const unsigned int damangeHitFrame2 = 7;

		if (currentState.IsFrameOnce(damangeHitFrame1) || currentState.IsFrameOnce(damangeHitFrame2))
			DebugPrint(DebugLevel::Info, "Hit!");
	}
}