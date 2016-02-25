//
//  ResourceManager.h
//  RPGProject
//
//  Created by macbook on 2/24/16.
//  Copyright © 2016 De Anza College Developers' Guild. All rights reserved.
//

#ifndef ResourceManager_h
#define ResourceManager_h

#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

class ResourceManager
{
private:
    std::map<std::string, std::unique_ptr<sf::Texture>> _textureMap;
public:
    ResourceManager();
    void add(const std::string&);
    sf::Texture& get(const std::string&);
};
#endif /* ResourceManager_h */
