#include "player.hpp"
#include "util.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <iostream>


int movementXDirection = 0;
int movementYDirection = 0;

Player::Player(int health, float posX, float posY) : Entity(health, posX, posY)
{
	m_movementVars.accel = 6000.f;
	m_movementVars.damping = 0.997f;
	m_movementVars.maxVel = 400.f;
	m_movementVars.velocity = new Vector2{ 0 };

	m_sprCharacterIdle = Sprite("guy_idle.png");
	m_sprCharacterWalkSide = Sprite("guy_walk_side.png", 32, 48, 4, true);
	m_sprCharacterWalkFacing = Sprite("guy_walk_facing.png", 32, 48, 2, true);
	m_sprCharacterWalkAway = Sprite("guy_walk_away.png", 32, 48, 2, true);
	m_animator = Animator();
	m_animator.AddState("idle", &m_sprCharacterIdle);
	m_animator.AddState("walk_side", &m_sprCharacterWalkSide);
	m_animator.AddState("walk_facing", &m_sprCharacterWalkFacing);
	m_animator.AddState("walk_away", &m_sprCharacterWalkAway);
	m_animator.SetCurrentState("idle");

	SetBoundingBoxSize(100.f, 150.f);
}
void Player::Update(float deltaTime)
{
	Move(deltaTime);
	m_animator.Update(deltaTime);
}
void Player::Draw()
{
	switch (movementYDirection)
	{
	case 1:
		m_animator.SetCurrentState("walk_facing");
		break;

	case -1:
		m_animator.SetCurrentState("walk_away");
		break;

	default:
		switch (movementXDirection)
		{
		case 1:
		case -1:
			m_animator.SetCurrentState("walk_side");
			break;
		default:
			m_animator.SetCurrentState("idle");
		}

		break;
	}

	m_animator.GetCurrentState()->Draw(GetBoundingBox(), (movementXDirection == -1), false);
}

void Player::Move(float deltaTime)
{
	// Accelerate
	Vector2 inputVec = Vector2Normalize(Vector2{ float(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)), float(IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) });
	//	Update movement direction
	if (inputVec.x > 0.f)
		movementXDirection = 1;
	else if (inputVec.x < 0.f)
		movementXDirection = -1;
	else
		movementXDirection = 0;
	if (inputVec.y > 0.f)
		movementYDirection = 1;
	else if (inputVec.y < 0.f)
		movementYDirection = -1;
	else
		movementYDirection = 0;

	Vector2& vel = *m_movementVars.velocity;
	vel = Vector2Add(vel, Vector2Scale(inputVec, m_movementVars.accel * deltaTime));

	// Clamp n damp
	if (Vector2Length(vel) > m_movementVars.maxVel)
	{
		vel = Vector2ClampValue(vel, 0.f, m_movementVars.maxVel);
	}
	if (inputVec.x == 0.f)
		vel.x *= m_movementVars.damping;
	if (inputVec.y == 0.f)
		vel.y *= m_movementVars.damping;

	// Apply velocity
	UpdatePosition(Vector2Scale(vel, deltaTime));
}