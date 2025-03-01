#include "entity_manager.hpp"
#include "entity.hpp"
#include "util.hpp"
#include <algorithm>
#include <iostream>


void EntityManager::Update(float deltaTime)
{
	for (Entity*& e : m_entities)
	{
		e->Update(deltaTime);
	}
}

std::vector<Entity*> EntityManager::m_entities;
void EntityManager::RegisterEntity(Entity* entity)
{
	auto it = std::find(m_entities.begin(), m_entities.end(), entity);
	if (it != m_entities.end())
	{
		DebugPrint(DebugLevel::Warning, "[EntityManager::RegisterEntity]: Entity already registered\n");
		return;
	}

	m_entities.push_back(entity);
}
void EntityManager::RemoveEntity(int indexOf)
{
	if (indexOf < 0 || indexOf > m_entities.size() - 1)
	{
		DebugPrint(DebugLevel::Error, "[EntityManager::RemoveEntity]: Index %d out of range\n", indexOf);
		return;
	}

	m_entities.erase(m_entities.begin() + indexOf);
}
void EntityManager::RemoveEntity(Entity* entity)
{
	int idx = FindEntity(entity);
	if (idx == -1)
	{
		DebugPrint(DebugLevel::Error, "[EntityManager::RemoveEntity]: Entity was never registered\n");
		return;
	}

	RemoveEntity(idx);
}
int EntityManager::FindEntity(Entity* entity)
{
	auto it = std::find(m_entities.begin(), m_entities.end(), entity);
	if (it == m_entities.end())
		return -1;

	return it - m_entities.begin();
}
std::vector<Entity*> EntityManager::GetAllEntities(void)
{
	return m_entities;
}