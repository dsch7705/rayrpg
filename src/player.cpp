#include "player.hpp"
#include "util.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <iostream>


int movementXDirection = 1;

Player::Player(int health, float posX, float posY) : Entity(health, posX, posY)
{
	m_movementVars.accel = 6000.f;
	m_movementVars.damping = 0.997f;
	m_movementVars.maxVel = 400.f;
	m_movementVars.velocity = new Vector2{ 0 };

	m_texCharacter = TextureManager::GetTexture("guy.png");
	SetBoundingBoxSize(100.f, 150.f);
}
void Player::Update(float deltaTime)
{
	Move(deltaTime);
}
void Player::Draw()
{
	Texture2D tex = *m_texCharacter;
	Rectangle texCharacterSrc{0, 0, tex.width, tex.height};
	if (movementXDirection > 0.f)
	{
		texCharacterSrc.x -= texCharacterSrc.width;
		texCharacterSrc.width *= -1.f;
	}

	DrawTexturePro(*m_texCharacter, texCharacterSrc, GetBoundingBox(), Vector2Zeros, 0.f, WHITE);
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