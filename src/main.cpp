#include "util.hpp"
#include "entity_manager.hpp"
#include "player.hpp"
#include "item.hpp"
#include "texture.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <iostream>


bool drawBBs = false;

int main()
{
	SetTraceLogLevel(LOG_WARNING);
	SetDebugLevel(DebugLevel::All);
	InitWindow(800, 600, "RPG");

	TextureManager::LoadTextures();

	Player p(10, GetScreenWidth() / 2.f, GetScreenHeight() / 2.f);
	Item::RegisterItem("stick", new Item("Stick", "stick.png"));

	while (!WindowShouldClose())
	{
		EntityManager::Update(GetFrameTime());

		BeginDrawing();
		ClearBackground(SKYBLUE);
		//DrawTexturePro(stick, Rectangle{ 0, 0, 16, 16 }, p.GetBoundingBox(), Vector2Zeros, 0.f, WHITE);
		//TextureManager::DrawTexturesTest();
		EntityManager::Draw();

		if (drawBBs)
		{
			for (Entity*& e : EntityManager::GetAllEntities())
			{
				Color c = CheckCollisionPointRec(GetMousePosition(), e->GetBoundingBox()) ? GREEN : WHITE;
				DrawRectangleRec(e->GetBoundingBox(), c);
			}
		}

		EndDrawing();
	}

	TextureManager::UnloadTextures();
	CloseWindow();
	DebugPrint(DebugLevel::All, "Bye bye!");
}