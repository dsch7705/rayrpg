#pragma once
#include <unordered_map>
#include <string>
#include <memory>


struct Texture;
namespace TextureManager
{
	inline const char* TEX_PATH = "res/textures/";

	void LoadTextures(void);
	void LoadTextures(const std::string& path);
	void UnloadTextures(void);

	Texture* GetTexture(const std::string& filename);
	void PrintTextures(void);
	void DrawTexturesTest(void);
};