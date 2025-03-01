#include <vector>


class Entity;
class EntityManager
{
private:
	static std::vector<Entity*> m_entities;

public:
	static void Update(float deltaTime);
	static void RegisterEntity(Entity* entity);
	static void RemoveEntity(int indexOf);
	static void RemoveEntity(Entity* entity);
	static int  FindEntity(Entity* entity);
	static std::vector<Entity*> GetAllEntities(void);

};