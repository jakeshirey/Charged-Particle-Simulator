#include "TextureManager.h"

//redeclared static var so .cpp file knows it exist (just the way it works)
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName)
{
	string path = "images/";
	path += fileName + ".png"; //dependant on project's folders and file types
	textures[fileName].loadFromFile(path);
}
sf::Texture& TextureManager::GetTexture(string textureName) //gets the texture, or adds it to map and gets it
{
	if (textures.find(textureName) == textures.end()) // not found
	{
		LoadTexture(textureName);
	}
	return textures[textureName];
}
void TextureManager::Clear()
{
	textures.clear();
}