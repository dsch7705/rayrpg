#pragma once
#include "item.hpp"
#include "util.hpp"
#include <vector>
#include <string>

#define DEFAULT_MAX_INVENTORY_SIZE 16


class Inventory
{
private:
	std::vector<std::pair<std::string, unsigned int>> m_slots;
	int m_maxSlots;
	std::string m_label;

public:
	Inventory(int maxSlots, const std::string& label) : m_maxSlots(maxSlots), m_label(label) {}
	Inventory(void) : Inventory(DEFAULT_MAX_INVENTORY_SIZE, "Inventory") {}

	void AddItem(const std::string& id, int count);
	void Print(void);
	virtual void Draw(void);
};