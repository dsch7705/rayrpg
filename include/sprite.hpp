#include <unordered_map>
#include <string>

#define SPRITE_PATH "res/sprites/"


struct Texture2D;
class SpriteManager
{
private:
	static std::unordered_map<std::string, Texture2D> m_sprites;

public:
	static Texture2D LoadSprite(const std::string& filename);
	static Texture2D GetSprite(const std::string& filename);

};