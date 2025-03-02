#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#define SPRITE_PATH "res/sprites/"


struct Rectangle;
class Sprite
{
public:
	void* texture;
	int width;
	int height;

	Sprite(const std::string& filename);
	~Sprite();
	void Draw(Rectangle dst);

};

class SpriteManager
{
private:
	static std::unordered_map<std::string, Sprite> m_spriteDict;

public:
	static void LoadSprites(void);
	static void LoadSprites(const std::string& path);
	static void UnloadSprites(void);

	static Sprite* GetSprite(const std::string& filename);
	static void PrintSprites(void);
	static void DrawSpritesTest(void);
};