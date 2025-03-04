#pragma once
#include "sprite.hpp"
#include <unordered_map>
#include <string>
#include <memory>

#define DEFAULT_MAX_ITEM_STACK_SIZE 99


struct Item
{
public:
	std::string displayName;
	int maxStackSize;
	Sprite sprite;

	Item(const std::string& displayName, const std::string& spriteFilename);
	~Item();


	static std::unordered_map<std::string, std::unique_ptr<Item>> m_itemDict;

	static void RegisterItem(const std::string& id, Item* item);
	static void RemoveItem(const std::string& id);
	static Item GetItem(const std::string& id);
};