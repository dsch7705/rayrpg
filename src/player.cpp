#include "player.hpp"
#
#include "util.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <iostream>


Player::Player(int health, float posX, float posY) : Entity(health, posX, posY)
{
	m_movementVars.accel = 6000.f;
	m_movementVars.damping = 0.997f;
	m_movementVars.maxWalkSpeed = 125.f;
	m_movementVars.maxRunSpeed = 250.f;
	m_movementVars.velocity = new Vector2{ 0 };

	m_animVars.sprSoldier = Sprite("Soldier.png", 7, 9);
	m_animVars.walkSpeed = 30.f;
	m_animVars.facingXDir = 1;
	SetBoundingBoxSize(60.f, 70.f);

	// Load animation states
	m_animVars.animator = Animator();
	Animator& anim = m_animVars.animator;
	anim.AddState(AnimationState("idle", &m_animVars.sprSoldier, 6));
	anim.AddState(AnimationState("walk", &m_animVars.sprSoldier, 8, 1));
	anim.AddState(AnimationState("attack1", &m_animVars.sprSoldier, 6, 2, false));
	anim.AddState(AnimationState("attack2", &m_animVars.sprSoldier, 6, 3, false));
	anim.SetCurrentState("idle");
	
	// Transitions
	bool* walkPtr = &m_animVars.walking;
	anim.AddTransition2Way("idle", "walk", &m_animVars.walking);

	anim.AddTransition("idle", "attack2", &m_animVars.attack);
	anim.AddTransition("attack2", "idle", &anim.GetState("attack2")->done);

	anim.AddTransition("walk", "attack1", &m_animVars.attack);
	anim.AddTransition("attack1", "walk", &anim.GetState("attack1")->done);

}
Player::~Player()
{
	delete m_movementVars.velocity;
}

void Player::Update(float deltaTime)
{
	Move(deltaTime);
	m_animVars.animator.Update(deltaTime);
}

bool inventoryIsOpen = false;
void Player::Draw()
{	
	// Character sprite
	const float SPRITE_SCALE = 4.f;
	Sprite& spr = *m_animVars.animator.GetCurrentState()->sprite;
	Rectangle spriteDst;

	spriteDst.width = spr.width * SPRITE_SCALE;
	spriteDst.height = spr.height * SPRITE_SCALE;
	spriteDst.x = GetPosition().x - spriteDst.width / 2.f;
	spriteDst.y = (GetPosition().y - spriteDst.height / 2.f) + 5.f;


	m_animVars.animator.GetCurrentState()->sprite->Draw(spriteDst, m_animVars.facingXDir == -1 ? true : false);

	// Open inventory
	if (IsKeyPressed(KEY_TAB))
		inventoryIsOpen = !inventoryIsOpen;
	if (inventoryIsOpen)
		m_inventory.Draw();

}
void Player::Animate(Vector2 inputVec)
{
	// Update facing direction
	if (inputVec.x > 0.f)
		m_animVars.facingXDir = 1;
	else if (inputVec.x < 0.f)
		m_animVars.facingXDir = -1;

	Vector2& vel = *m_movementVars.velocity;
	Animator& anim = m_animVars.animator;

	// Walk/Run
	float velocityMag = Vector2Length(*m_movementVars.velocity);
	if (velocityMag > m_animVars.walkSpeed)
		m_animVars.walking = true;
	else
		m_animVars.walking = false;
	if (m_movementVars.running)
		anim.GetState("walk")->frameRate = 10;
	else
		anim.GetState("walk")->frameRate = DEFAULT_ANIMATOR_FPS;

	// Attack
	m_animVars.attack = IsKeyPressed(KEY_F);
}

void Player::Move(float deltaTime)
{
	Vector2 inputVec = Vector2Normalize(Vector2{ float(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)), float(IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) });

	if (IsKeyDown(KEY_LEFT_SHIFT))
		m_movementVars.running = true;
	else
		m_movementVars.running = false;

	Animate(inputVec);

	// Accelerate
	Vector2& vel = *m_movementVars.velocity;
	vel = Vector2Add(vel, Vector2Scale(inputVec, m_movementVars.accel * deltaTime));

	// Clamp n damp
	float maxSpeed = m_movementVars.running ? m_movementVars.maxRunSpeed : m_movementVars.maxWalkSpeed;
	if (Vector2Length(vel) > maxSpeed)
	{
		vel = Vector2ClampValue(vel, 0.f, maxSpeed);
	}
	if (inputVec.x == 0.f)
		vel.x *= m_movementVars.damping;
	if (inputVec.y == 0.f)
		vel.y *= m_movementVars.damping;

	// Apply velocity
	UpdatePosition(Vector2Scale(vel, deltaTime));
}