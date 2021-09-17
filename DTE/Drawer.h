#pragma once
#include <map>
#include <vector>

class Game;
class Bitmap;
class Texture;
class ColisionBox;

namespace Grafic {
	struct Size {
		double w = 0, h = 0;
	};
	struct Point {
		double x = 0, y = 0;
	};
}

using namespace Grafic;

class Drawer
{
public:
	Drawer(Game* target) {
		this->target = target;
		LoadTextures();
	}

	void Rectangle(Size size, Point point, size_t color);
	void Background(size_t color);
	void WithTexture(std::vector<ColisionBox*>& boxes);
	
	void LoadTextures();
	Texture& GetTexture(const char* key);

	void Resize();
private:
	Game* target;
	std::map<const char*, Texture*> textures;
};

