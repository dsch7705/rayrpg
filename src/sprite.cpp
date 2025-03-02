#include "sprite.hpp"
#include "util.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <filesystem>
#include <iostream>


Sprite::Sprite(const std::string& filepath)
{;
	texture = new Texture2D();
	Texture2D& tex = *(Texture2D*)texture;
	Texture2D tex2 = LoadTexture(filepath.c_str());
	if (IsTextureValid(tex2) == false)
		DebugPrint(DebugLevel::Warning, "Failed to load sprite '%s'\n", filepath.c_str());
	tex = tex2;

	DebugPrint(DebugLevel::All, "GL texture id: %d\n%s\n", tex2.id, filepath.c_str());

	width = tex.width;
	height = tex.height;
}
Sprite::~Sprite()
{
	UnloadTexture(*((Texture2D*)texture));
}
void Sprite::Draw(Rectangle dst)
{
	Texture2D tex = *(Texture2D*)texture;
	DrawTexturePro(tex, Rectangle{ (float)tex.width, (float)tex.height }, dst, Vector2Zeros, 0.f, WHITE);
}

std::unordered_map<std::string, Sprite> SpriteManager::m_spriteDict;
void SpriteManager::LoadSprites()
{
	LoadSprites(SPRITE_PATH);
}
void SpriteManager::LoadSprites(const std::string& path)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (entry.is_regular_file() == false)
			continue;
		std::string ext = entry.path().extension().string();
		if (ext != ".png" && ext != ".jpg")
			continue;
		
		m_spriteDict.insert(std::make_pair(entry.path().filename().string(), Sprite(entry.path().string())));
	}
}
void SpriteManager::UnloadSprites()
{
	m_spriteDict.clear();
}

Sprite* SpriteManager::GetSprite(const std::string& filename)
{
	if (m_spriteDict.count(filename) == 0)
		return nullptr;

	return &m_spriteDict.at(filename);
}
void SpriteManager::PrintSprites(void)
{
	for (const auto& pair : m_spriteDict)
	{
		DebugPrint(DebugLevel::All, "%s\n", pair.first.c_str());
	}
}
void SpriteManager::DrawSpritesTest()
{
	static const int SPRITE_TEST_SCALE = 4;

	Rectangle sprDst{ 0 };
	for (const auto& pair : m_spriteDict)
	{
		Sprite spr = pair.second;
		sprDst.width = spr.width * SPRITE_TEST_SCALE;
		sprDst.height = spr.height * SPRITE_TEST_SCALE;
		spr.Draw(sprDst);

		sprDst.x += sprDst.width;
	}
}