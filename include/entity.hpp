#pragma once

struct Vector2;
struct Rectangle;
struct Texture2D;
class Entity
{
private:
	int m_health;
	int m_maxHealth;

	Vector2* m_position;
	Vector2* m_boundingBoxSize;
	Rectangle* m_boundingBox;
	Texture2D* m_sprite;

	void UpdateBB(bool updateSize=false);

public:
	Entity(int health, float posX, float posY);
	~Entity();
	/// <summary>
	/// Lose health
	/// </summary>
	/// <param name="amount"></param>
	void TakeDamage(int amount);
	/// <summary>
	/// Set health to zero
	/// </summary>
	/// <param name=""></param>
	void Kill(void);
	/// <summary>
	/// Recover health
	/// </summary>
	/// <param name="amount">: -1 heals to max health</param>
	void Heal(int amount);
	/// <summary>
	/// Implement behavior logic here
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void Update(float deltaTime) = 0;

	/// <summary>
	/// Adds value to position
	/// </summary>
	/// <param name="value"></param>
	void UpdatePosition(const Vector2& value);
	void SetPosition(const Vector2& value);
	void SetBoundingBoxSize(float width, float height);
	void SetSprite(Texture2D* sprite);

	Vector2 GetPosition(void);
	Rectangle GetBoundingBox(void);
	int GetHealth(void);
};