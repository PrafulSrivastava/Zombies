#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Configuration.hpp"

using namespace std;
using namespace sf;

class TextureHolder {
private:
	map<string, Texture> m_TextureMap;
	static TextureHolder* m_s_Instance;

public:
	TextureHolder();
	static Texture& GetTexture(string const& filename);
};