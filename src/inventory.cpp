#include "inventory.hpp"
#include "util.hpp"
#include "raylib/raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raylib/raygui.h"
#include <algorithm>


void Inventory::AddItem(const std::string& id, int count)
{
	Item itm = Item::GetItem(id);
	for (auto& pair : m_slots)
	{
		if (pair.first == id)
		{
			if (pair.second >= itm.maxStackSize)
				continue;

			if (pair.second + count > itm.maxStackSize)
			{
				unsigned int remainder = count - (itm.maxStackSize - pair.second);
				pair.second = itm.maxStackSize;
				AddItem(id, remainder);
				return;
			}

			pair.second += count;
			return;
		}
	}

	if (m_slots.size() >= m_maxSlots)
	{
		DebugPrint(DebugLevel::All, "Inventory full (max %d slots)\n", m_maxSlots);
		return;
	}
	m_slots.push_back(std::make_pair(id, 0));
	AddItem(id, count);
}
void Inventory::Print()
{
	for (const auto& pair : m_slots)
	{
		Item itm = Item::GetItem(pair.first);
		DebugPrint(DebugLevel::All, "[Item]: '%s' (%d)\n", itm.displayName.c_str(), pair.second);
	}
}
void Inventory::Draw()
{
	const unsigned int WIDTH = 350;
	const unsigned int HEIGHT = 200;

	GuiSetStyle(DEFAULT, BACKGROUND_COLOR, 0xE1E1E1EE);
	GuiPanel(Rectangle{ GetScreenWidth() / 2.f - WIDTH / 2.f, GetScreenHeight() / 2.f - HEIGHT / 2.f, WIDTH, HEIGHT }, m_label.c_str());
}