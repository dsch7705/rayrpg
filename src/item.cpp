#include "item.hpp"
#include "texture.hpp"
#include "util.hpp"
#include "raylib/raylib.h"
#include <iostream>


std::unordered_map<std::string, std::unique_ptr<Item>> Item::m_itemDict;
Item::Item(const std::string& displayName, const std::string& spriteFilename) : displayName(displayName)
{
	sprite = Sprite(spriteFilename);
	maxStackSize = DEFAULT_MAX_ITEM_STACK_SIZE;
}
Item::~Item()
{
}

void Item::RegisterItem(const std::string& id, Item* item)
{
	m_itemDict[id] = std::unique_ptr<Item>(item);
}
void Item::RemoveItem(const std::string& id)
{
	m_itemDict.erase(id);
}
Item Item::GetItem(const std::string& id)
{
	return *m_itemDict.at(id).get();
}