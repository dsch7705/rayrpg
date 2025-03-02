#pragma once
#include "sprite.hpp"
#include <unordered_map>
#include <string>
#include <memory>


class Item
{
private:
	std::string m_displayName;
	Sprite* m_sprite;

	static std::unordered_map<std::string, std::unique_ptr<Item>> m_itemDict;

public:
	Item(const std::string& displayName, const std::string& spriteFilename);
	~Item();

	static void RegisterItem(const std::string& id, Item* item);
	static void RemoveItem(const std::string& id);

	static void DumpDict(void);
};