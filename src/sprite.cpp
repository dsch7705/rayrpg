#include "sprite.hpp"
#include "raylib/raylib.h"


std::unordered_map<std::string, Texture2D> SpriteManager::m_sprites;
Texture2D SpriteManager::LoadSprite(const std::string& filename)
{
	if (m_sprites.count(filename))
		return GetSprite(filename);

	std::string filepath = SPRITE_PATH;
	filepath.append(filename);
	Texture2D tex = LoadTexture(filepath.c_str());
	m_sprites[filename] = tex;
	return tex;
}
Texture2D SpriteManager::GetSprite(const std::string& filename)
{
	return m_sprites[filename];
}