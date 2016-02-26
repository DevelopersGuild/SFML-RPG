//
//  ResourceManager.cpp
//  RPGProject
//
//  Created by macbook on 2/24/16.
//  Copyright © 2016 De Anza College Developers' Guild. All rights reserved.
//

#include "ResourceManager.h"
#include "ResourcePath.h"

ResourceManager::ResourceManager()
{
    
}

void ResourceManager::add(const std::string& str)
{
    std::unique_ptr<sf::Texture> ptr(new sf::Texture);

	ptr->loadFromFile(resourcePath() + str);

    _textureMap.emplace(str, std::move(ptr));
}

sf::Texture& ResourceManager::get(const std::string& str)
{
    return *_textureMap[str];
}
