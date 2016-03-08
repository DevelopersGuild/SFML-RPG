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
#include <SFML/Audio.hpp>
#include "ResourcePath.h"

template<class T>
class ResourceManager
{
private:
    std::map<std::string, std::unique_ptr<T>> _Map;
public:
    ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager operator=(const ResourceManager&) = delete;

	T& get(const std::string&);
};

template<class T>
ResourceManager<T>::ResourceManager()
{

}

template<class T>
T& ResourceManager<T>::get(const std::string& str)
{
	auto it = _Map.find(str);
	if (it != _Map.end())
	{
		return *it->second;
	}	
	else
	{
		std::unique_ptr<T> ptr(new T);

		if (!ptr->loadFromFile(resourcePath() + str))
		{
			throw "Not found!";	//handle exception...to be changed
		}

		_Map.emplace(str, std::move(ptr));

		return *_Map[str];
	}
}

template<>
class ResourceManager<sf::Music>
{
private:
	std::map<std::string, std::unique_ptr<sf::Music>> _Map;
public:
	ResourceManager()
	{
		;
	}
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager operator=(const ResourceManager&) = delete;

	sf::Music& ResourceManager<sf::Music>::get(const std::string& str)
	{
		auto it = _Map.find(str);
		if (it != _Map.end())
		{
			return *it->second;
		}
		else
		{
			std::unique_ptr<sf::Music> ptr(new sf::Music);

			if (!ptr->openFromFile(resourcePath() + str))
			{
				throw "Not found!";	//handle exception...to be changed
			}

			_Map.emplace(str, std::move(ptr));

			return *_Map[str];
		}
	}
};

#endif /* ResourceManager_h */
