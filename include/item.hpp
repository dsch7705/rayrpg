#include <unordered_map>
#include <string>
#include <memory>


struct Texture2D;
class Item
{
private:
	Texture2D* m_sprite;
	std::string m_displayName;

	static std::unordered_map<std::string, std::unique_ptr<Item>> m_itemDict;

public:
	Item(const std::string& displayName, const std::string& spriteFilename);
	~Item();

	static void RegisterItem(const std::string& id, Item* item);
	static void RemoveItem(const std::string& id);

	static void DumpDict(void);
};