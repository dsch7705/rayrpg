#include "item.hpp"
#include "texture.hpp"
#include "util.hpp"
#include "raylib/raylib.h"
#include <iostream>


std::unordered_map<std::string, std::unique_ptr<Item>> Item::m_itemDict;
Item::Item(const std::string& displayName, const std::string& spriteFilename)
{
	m_displayName = displayName;

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

void Item::DumpDict(void)
{
	for (const auto& pair : m_itemDict)
	{
		DebugPrint(DebugLevel::All, "'%s': '%s'\n", pair.first.c_str(), pair.second->m_displayName.c_str());
	}
}