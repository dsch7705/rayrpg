#include "character.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"


float dT;

Character::Character(int health, float posX, float posY) : Entity(health, posX, posY)
{
	// Movement vars
	m_movementVars.accel = 6000.f;
	m_movementVars.maxWalkSpeed = 100.f;
	m_movementVars.maxRunSpeed = 175;
	m_movementVars.damping = 0.997f;
	m_movementVars.velocity = new Vector2{ 0 };

	m_movementVars.running = false;

	// Sprite vars
	m_spriteVars.sprCharacter = Sprite("error.png");
	m_spriteVars.scaleX = 4.f;
	m_spriteVars.scaleY = 4.f;
	m_spriteVars.offsetX = 0.f;
	m_spriteVars.offsetY = 5.f;

	m_spriteVars.facingXDir = 1;
	m_spriteVars.walkSpeed = 30.f;
	m_spriteVars.walking = false;

	// Entity vars
	SetBoundingBoxSize(60.f, 70.f);

	// Animation transitions
	Animator& anim = m_spriteVars.animator;
	anim.AddTransition2Way("idle", "walk", &m_spriteVars.walking);

}
Character::~Character()
{
	delete m_movementVars.velocity;
}

void Character::Draw()
{
	// Character sprite
	Sprite& spr = *m_spriteVars.animator.GetCurrentState()->sprite;
	Rectangle spriteDst;

	spriteDst.width = spr.width * m_spriteVars.scaleX;
	spriteDst.height = spr.height * m_spriteVars.scaleY;
	spriteDst.x = (GetPosition().x - spriteDst.width / 2.f) + m_spriteVars.offsetX;
	spriteDst.y = (GetPosition().y - spriteDst.height / 2.f) + m_spriteVars.offsetY;


	m_spriteVars.animator.GetCurrentState()->sprite->Draw(spriteDst, m_spriteVars.facingXDir == -1 ? true : false);
}
void Character::Animate()
{
	// Update facing direction
	if (m_movementVars.velocity->x > 0.f)
		m_spriteVars.facingXDir = 1;
	else if (m_movementVars.velocity->x < 0.f)
		m_spriteVars.facingXDir = -1;

	Vector2& vel = *m_movementVars.velocity;
	Animator& anim = m_spriteVars.animator;

	// Walk/Run
	float velocityMag = Vector2Length(*m_movementVars.velocity);
	if (velocityMag > m_spriteVars.walkSpeed)
		m_spriteVars.walking = true;
	else
		m_spriteVars.walking = false;
	if (m_movementVars.running)
		anim.GetState("walk")->frameRate = 15;
	else
		anim.GetState("walk")->frameRate = DEFAULT_ANIMATOR_FPS;

	m_spriteVars.animator.Update(dT);
}
void Character::Move(Vector2 direction)
{
	// Accelerate
	Vector2& vel = *m_movementVars.velocity;
	vel = Vector2Add(vel, Vector2Scale(Vector2Normalize(direction), m_movementVars.accel * dT));

	// Clamp n damp
	float maxSpeed = m_movementVars.running ? m_movementVars.maxRunSpeed : m_movementVars.maxWalkSpeed;
	if (Vector2Length(vel) > maxSpeed)
	{
		vel = Vector2ClampValue(vel, 0.f, maxSpeed);
	}
	if (direction.x == 0.f)
		vel.x *= m_movementVars.damping;
	if (direction.y == 0.f)
		vel.y *= m_movementVars.damping;

	// Apply velocity
	UpdatePosition(Vector2Scale(vel, dT));
}

void Character::Update(float deltaTime)
{
	dT = deltaTime;
	Animate();
	Draw();
}