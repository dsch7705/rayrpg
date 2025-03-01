#include "entity.hpp"
#include "entity_manager.hpp"
#include "sprite.hpp"
#include "raylib/raylib.h"

#define DEFAULT_BB_SIZE_VEC2 Vector2{ 30.f, 45.f }


Entity::Entity(int health, float posX, float posY)
{
	m_maxHealth = m_health = health;
	m_position = new Vector2{ posX, posY };
	m_boundingBoxSize = new DEFAULT_BB_SIZE_VEC2;
	m_boundingBox = new Rectangle{ m_position->x - m_boundingBoxSize->x / 2.f, m_position->y - m_boundingBoxSize->y / 2.f,
									m_boundingBoxSize->x, m_boundingBoxSize->y};

	m_sprite = NULL;

	EntityManager::RegisterEntity(this);
}
Entity::~Entity()
{
	delete m_position;
	delete m_boundingBoxSize;
	delete m_boundingBox;

	EntityManager::RemoveEntity(this);
}
void Entity::TakeDamage(int amount)
{
	m_health -= amount;
}
void Entity::Kill(void)
{
	m_health = 0;
}
void Entity::Heal(int amount)
{
	if (amount == -1 || m_health + amount >= m_maxHealth)
	{
		m_health = m_maxHealth;
		return;
	}

	m_health += amount;
}

void Entity::UpdatePosition(const Vector2& value)
{
	m_position->x += value.x;
	m_position->y += value.y;

	UpdateBB();
}
void Entity::SetPosition(const Vector2& value)
{
	m_position->x = value.x;
	m_position->y = value.y;

	UpdateBB();
}
void Entity::SetBoundingBoxSize(float width, float height)
{
	m_boundingBoxSize->x = width;
	m_boundingBoxSize->y = height;

	UpdateBB();
}
void Entity::UpdateBB(bool updateSize)
{
	if (updateSize)
	{
		m_boundingBox->width = m_boundingBoxSize->x;
		m_boundingBox->height = m_boundingBoxSize->y;
	}

	m_boundingBox->x = m_position->x - m_boundingBoxSize->x / 2.f;
	m_boundingBox->y = m_position->y - m_boundingBoxSize->y / 2.f;
}
void Entity::SetSprite(Texture2D* sprite)
{
	m_sprite = sprite;
}

Vector2 Entity::GetPosition(void)
{
	return *m_position;
}
Rectangle Entity::GetBoundingBox(void)
{
	return *m_boundingBox;
}
int Entity::GetHealth(void)
{
	return m_health;
}