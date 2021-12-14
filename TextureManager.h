#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager
{
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string textureName); //no folder names or .png
public:
	static sf::Texture& GetTexture(string textureName);
	static void Clear(); //called at end of main!!!!
};

//example use -> sf::Sprite newButton(TextureManager::GetTexture("btnNew"));

