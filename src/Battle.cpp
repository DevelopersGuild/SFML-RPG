#include "Battle.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

/*
The constructor
*/
Gameplay::BattleCharacter::BattleCharacter()
{
    direction = DIRECTION::right;
    facing_right = true;
}
/*
BattleChar(base) loadSprite function
Assume the picture is 320 height
*/
void Gameplay::BattleCharacter::loadSprite(sf::Texture &texture)
{
    //1.find the number of frame. 1 frame is 320 x 320, 2 frame is 640 x 320...
    sf::Vector2u textureSize = texture.getSize();
    int num_frame = textureSize.x / 320;
    
    //2.add each frame into the spriteList
    for(int i = 0; i < num_frame; i++)
    {
        spriteList.add(sf::IntRect(i * 320, 0, 320, 320));
    }
    
    //3.set texture to sprite
    sprite.setTexture(texture);
    
    //4.set the origin of the sprite
    sprite.setOrigin(160, 160);
    
    //5.set the texture at the first frame
    sprite.setTextureRect(spriteList.getNext());
}

/*
BattleChar(base) moving function
add 0.5 speed only
*/
void Gameplay::BattleCharacter::move(Gameplay::BattleCharacter::DIRECTION newDirection)
{
    if(direction != newDirection)
    {
        sprite.scale(-1, 1);
        facing_right = !facing_right;
    }
    
    if(direction == DIRECTION::right && !facing_right)
    {
        sprite.scale(-1,1);
        facing_right = !facing_right;
    }
    else if(direction == DIRECTION::left && facing_right)
    {
        sprite.scale(-1, 1);
        facing_right = !facing_right;
    }
    
    //if speed is already at max speed, do nothing
    if(speed < max_speed && speed > -max_speed)
    {
        switch(newDirection)
        {
            case DIRECTION::right:
                speed += 0.5;
                direction = right;
                break;
            case DIRECTION::left:
                speed -= 0.5;
                direction = left;
                break;
        }
    }
}

/*
BattleChar(base) animation Update function
decrease the speed, update sprite....
*/
void Gameplay::BattleCharacter::animeUpdate()
{
    if(moveTimer.getElapsedTime() > sf::seconds(0.01))
    {
        //move the character
        sprite.move(speed, 0);
        
        //decrease the speed
        if(speed > 0)
            speed -= 0.1;
        else if(speed < 0)
            speed += 0.1;
        
        moveTimer.restart();
    }
    
    //if speed is too small, just set it to 0
    if(speed < 0.2 && speed > -0.2)
        speed = 0;
    
    //if 0.8s has passed since the last sprite, go to the next sprite
    if(spriteTimer.getElapsedTime() > sf::seconds(0.4))
    {
        sprite.setTextureRect(spriteList.getNext());
        spriteTimer.restart();
    }
}

/*
BattleChar(base) draw
draw the sprite of character
*/
void Gameplay::BattleCharacter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
}

/*
BattlePlayer constructor
constructor of BattlePlayer class, need a character pointer
*/
Gameplay::BattlePlayer::BattlePlayer(Character& newCharacter) : character(newCharacter)
{
    speed = character.getSpeed();
    max_speed = 4;  //TBD
    type = player;
    name = newCharacter.getName();
    max_speed = newCharacter.getSpeed();
}

/*
BattlePlayer animeUpdate
move the player right
*/
void Gameplay::BattlePlayer::animeUpdate()
{
    this->move(right);
    BattleCharacter::animeUpdate();
}

/*
BattleMonster constructor
default constructor of monster.
*/
Gameplay::BattleMonster::BattleMonster()
{
    max_speed = 2;
    max_hp = 20;
    current_hp = max_hp;
    atk = 5;
    def = 5;
    direction = left;
    facing_right = false;
    type = monster;
}

/*
BattleMonster constructor with attributes
initiate attributes of monster
*/
Gameplay::BattleMonster::BattleMonster(float newMaxSpeed, int newAtk, int newDef, int newMaxHP)
{
    max_speed = newMaxSpeed;
    atk = newAtk;
    def = newDef;
    max_hp = newMaxHP;
    current_hp = max_hp;
    direction = left;
    facing_right = false;
    type = monster;
}

/*
BattleMonster copy constructor
copy constructor
*/
Gameplay::BattleMonster::BattleMonster(const BattleMonster& newMonster)
{
    max_speed = newMonster.max_speed;
    atk = newMonster.atk;
    def = newMonster.def;
    max_hp = newMonster.max_hp;
    current_hp = newMonster.current_hp;
    direction = newMonster.direction;
    facing_right = newMonster.facing_right;
    type = monster;
    const sf::Texture* texture = newMonster.sprite.getTexture();
    sf::Vector2u textureSize = texture->getSize();
    int num_frame = textureSize.x / 320;
    for(int i = 0; i < num_frame; i++)
        spriteList.add(sf::IntRect(i * 320, 0, 320, 320));
    sprite.setTexture(*texture);
    sprite.setOrigin(160, 160);
    sprite.setTextureRect(spriteList.getNext());
}

/*
BattleMonster assign constructor
assign constructor
*/
Gameplay::BattleMonster& Gameplay::BattleMonster::operator=(const BattleMonster& newMonster)
{
    max_speed = newMonster.max_speed;
    atk = newMonster.atk;
    def = newMonster.def;
    max_hp = newMonster.max_hp;
    current_hp = newMonster.current_hp;
    direction = newMonster.direction;
    facing_right = newMonster.facing_right;
    type = monster;
    const sf::Texture* texture = newMonster.sprite.getTexture();
    sf::Vector2u textureSize = texture->getSize();
    int num_frame = textureSize.x / 320;
    for(int i = 0; i < num_frame; i++)
        spriteList.add(sf::IntRect(i * 320, 0, 320, 320));
    sprite.setTexture(*texture);
    sprite.setOrigin(160, 160);
    sprite.setTextureRect(spriteList.getNext());
    return *this;
}
/*
BattleMonster animeUpdate
the monster moves left.
*/
void Gameplay::BattleMonster::animeUpdate()
{
    this->move(left);
    BattleCharacter::animeUpdate();
}

/*
Battle constructor
constructor of battle
*/
Gameplay::Battle::Battle(Configuration& newConfig) : config(newConfig)
{
    //the background is as big as the window
    background.setSize(sf::Vector2f(config.window.getSize()));
    
}

/*
Battle setBackGround
set the background of the battle
*/
void Gameplay::Battle::setBackGround(sf::Texture* texture)
{
    background.setTexture(texture);
}

/*
Battle addCharacter
add the character to the character Tree, if the playerName is already in the
tree, rename the character with additional number.
*/
void Gameplay::Battle::addCharacter(std::unique_ptr<BattleCharacter> charPtr)
{
    std::string searchStr;
    
    for(int i = 0; ; i++)
    {
        searchStr = charPtr->getName();
        if(i) searchStr += i;
        
        //search for the name in the character Tree
        auto it = characterTree.find(searchStr);
        //if not found, then add the character to the tree
        if(it == characterTree.end())
        {
            charPtr->setName(searchStr);
            characterTree.emplace(searchStr, std::move(charPtr));
            return;
        }
    }
}

/*
Battle setCharPosition
set the position of the character.
Since the battle is on x-axis only, so only one value is needed.
if the name is not found, do nothing.
*/
void Gameplay::Battle::setCharPosition(const std::string& charName, int value)
{
    auto it = characterTree.find(charName);
    if(it != characterTree.end())
        it->second->setPosition(sf::Vector2f(value, 500));
    else
        std::cout << "Error: char not found." << std::endl;
    return;
}

/*
Battle moveCharacter
move the character in certain direction
if the name is not found, do nothing.
*/
void Gameplay::Battle::moveCharacter(const std::string &charName, BattleCharacter::DIRECTION direction)
{
    auto it = characterTree.find(charName);
    it->second->move(direction);
}

/*
Battle draw
draw the battle in window
*/
void Gameplay::Battle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background);
    for(auto& pair : characterTree)
    {
        target.draw(*pair.second);
    }
}

/*
Battle update
perform animation update and collision test(thus dealing damage)
for battle. Must called in every frame.
*/
void Gameplay::Battle::update()
{
    for(auto& pair : characterTree)
    {
        pair.second->animeUpdate();
    }
    _collisionTest();
}

/*
Battle collisionTest
test if any two character intersect in the battle and then call 
deal damage function.
*/
void Gameplay::Battle::_collisionTest()
{
    for(auto& pair : characterTree)
    {
        for(auto& otherPair : characterTree)
        {
            if(pair.first != otherPair.first && pair.second->getAABB().intersects(otherPair.second->getAABB()))
            {
                pair.second->setSpeed(4);
                otherPair.second->setSpeed(-4);
                return;
            }
        }
    }
}

/*
BattleFactory constructor
load all monster's name and their data into the tree.
*/
Gameplay::BattleFactory::BattleFactory(Configuration& newConfig) : config(newConfig)
{
    //load all monster name and texture filename here.
	std::ifstream input;
	input.open(resourcePath() + "maps/monsterData.txt");
	if (!input.is_open())
	{
		std::cout << "Error: maps/monsterData.txt not found!" << std::endl;
		exit(1);
	}
	//load the data to a new BattleMonster
	while (!input.eof())
	{
		std::string name, spriteName, line;
		int max_speed, atk, def, max_hp;
		std::getline(input, line);
		std::stringstream ss(line);
		ss >> name >> max_speed >> atk >> def >> max_hp >> spriteName;
        BattleMonster newMonster(max_speed, atk, def, max_hp);
        newMonster.loadSprite(config.texMan.get(spriteName));
        monsterTree.emplace(name, newMonster);
	}
	input.close();
}

/*
BattleFactory generateBattle
generate a battle based on the battleObject and player who started the battle
*/
std::shared_ptr<Gameplay::Battle> Gameplay::BattleFactory::generateBattle(tmx::MapObject* battleObject)
{
    //create empty battle
    std::shared_ptr<Gameplay::Battle> battle(new Battle(config));
    
    //load the background
    std::string background = battleObject->GetPropertyString("background");
    battle->setBackGround(&config.texMan.get(background));
    
    //get the possible monster set
    std::string monster_set = battleObject->GetPropertyString("monster_set");
    std::stringstream ss(monster_set);
    std::vector<std::string> monsterList;
    std::string hold;
    while(ss >> hold) monsterList.push_back(hold);
    
    int random = rand() % 100;
    int min = 0, max = 0, temp = 0;
    std::string result;
    for(auto it = monsterList.begin(); it != monsterList.end(); it++)
    {
        std::stringstream numss(battleObject->GetPropertyString(*it));
        numss >> temp;
        max += temp;
        
        if(random >= min && random < max)
        {
            result = *it;
            break;
        }
        min = max;
    }
    
    //create a monster from the tree
    std::unique_ptr<BattleMonster> monster(new BattleMonster(monsterTree.at(result)));
    std::string monsterName = monster->getName();
    battle->addCharacter(std::move(monster));
    battle->setCharPosition(monsterName, 800);
	return battle;
}