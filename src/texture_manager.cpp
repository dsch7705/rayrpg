#include "texture_manager.hpp"
#include "util.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <unordered_map>
#include <filesystem>
#include <iostream>
#include <stdexcept>


std::unordered_map<std::string, Texture> texDict;
Texture* TextureManager::errTexture = nullptr;
void TextureManager::LoadTextures()
{
	LoadTextures(TEX_PATH);
}
void TextureManager::LoadTextures(const std::string& path)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (entry.is_regular_file() == false)
			continue;
		std::string ext = entry.path().extension().string();
		if (ext != ".png" && ext != ".jpg")
			continue;
		
		std::string filepath = entry.path().string();
		std::string filename = entry.path().filename().string();
		Texture tex = LoadTexture(filepath.c_str());
		texDict.insert(std::make_pair(filename, tex));

		if (filename == "error.png")
			errTexture = &texDict.at(filename);
	}

	if (errTexture == nullptr)
		ThrowException("'%s' not found!", "error.png");
}
void TextureManager::UnloadTextures()
{
	for (const auto& pair : texDict)
	{
		UnloadTexture(pair.second);
	}

	texDict.clear();
}

Texture* TextureManager::GetTexture(const std::string& filename)
{
	if (texDict.count(filename) == 0)
		return &texDict.at("error.png");

	return &texDict.at(filename);
}
void TextureManager::PrintTextures(void)
{
	for (const auto& pair : texDict)
	{
		DebugPrint(DebugLevel::Info, "%s\n", pair.first.c_str());
	}
}
void TextureManager::DrawTexturesTest()
{
	static const int SPRITE_TEST_SCALE = 4;

	Rectangle texDst{ 0 };
	for (const auto& pair : texDict)
	{
		Texture tex = pair.second;
		texDst.width = tex.width * SPRITE_TEST_SCALE;
		texDst.height = tex.height * SPRITE_TEST_SCALE;
		DrawTexturePro(tex, Rectangle{ 0, 0, (float)tex.width, (float)tex.height }, texDst, Vector2Zeros, 0.f, WHITE);

		texDst.x += texDst.width;
	}
}