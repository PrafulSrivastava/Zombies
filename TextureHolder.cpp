#include "TextureHolder.hpp"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder(){
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename) {
	auto& textureMap = m_s_Instance->m_TextureMap;
	auto keyValuePair = textureMap.find(filename);
	if (keyValuePair != textureMap.end()) {
		return keyValuePair->second;
	}
	auto& texture = textureMap[filename];
	texture.loadFromFile(filename);
	return texture;
}