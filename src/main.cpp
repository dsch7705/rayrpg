#include "util.hpp"
#include "entity_manager.hpp"
#include "player.hpp"
#include "item.hpp"
#include "texture.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <iostream>


const bool drawBBs = true;

int main()
{
	SetTraceLogLevel(LOG_WARNING);
	SetDebugLevel(DebugLevel::All);
	InitWindow(800, 600, "RPG");

	TextureManager::LoadTextures();

	Item::RegisterItem("stick", new Item("Stick", "stick.png"));

	Player p(10, GetScreenWidth() / 2.f, GetScreenHeight() / 2.f);
	while (!WindowShouldClose())
	{
		EntityManager::Update(GetFrameTime());

		BeginDrawing();
		ClearBackground(SKYBLUE);

		EntityManager::Draw();
		if (drawBBs)
		{
			for (Entity*& e : EntityManager::GetAllEntities())
			{
				DrawRectangleLinesEx(e->GetBoundingBox(), 2.f, LIME);
			}
		}

		EndDrawing();
	}

	TextureManager::UnloadTextures();
	CloseWindow();
	DebugPrint(DebugLevel::All, "Bye bye!");
}