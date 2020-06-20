#include "engine/utils/assets_manager.h"
#include <SFML/Graphics.hpp>

std::map<std::string, sf::Texture> AssetsManager::sm_textures;
std::map<std::string, sf::Font> AssetsManager::sm_fonts;

sf::Texture* AssetsManager::get_texture(const char* filename){
    std::map<std::string, sf::Texture>::iterator itr = sm_textures.find(filename);
    if(itr!=sm_textures.end()){
        return &(itr->second);
    }else{
        sf::Texture& texture = sm_textures[filename];
        texture.loadFromFile(filename);
        return &texture;
    }
}


sf::Font* AssetsManager::get_font(const char* filename){
    std::map<std::string, sf::Font>::iterator itr = sm_fonts.find(filename);
    if(itr!=sm_fonts.end()){
        return &(itr->second);
    }else{
        sf::Font& font = sm_fonts[filename];
        font.loadFromFile(filename);
        return &font;
    }
}