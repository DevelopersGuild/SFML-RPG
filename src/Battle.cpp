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
	status = active;
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
BattleChar flyOut
move to the right-top corner or left-top corner of the screen 
and keep rotating!
*/

void Gameplay::BattleCharacter::flyOut()
{
    if(direction == right)
    {
        sprite.move(-10, -16);
        sprite.rotate(20);
    }
    else if(direction == left)
    {
        sprite.move(10, -16);
        sprite.rotate(-20);
    }
}
/*
BattlePlayer constructor
constructor of BattlePlayer class, need a character pointer
*/
Gameplay::BattlePlayer::BattlePlayer(Character& newCharacter) : character(newCharacter)
{
    speed = 0;
    max_speed = 4;  //TBD
    type = player;
    name = newCharacter.getName();
    max_speed = newCharacter.getBattleSpeed();
}

/*
BattlePlayer animeUpdate
move the player right
*/
void Gameplay::BattlePlayer::animeUpdate()
{
    if(status == STATUS::non_active)
    {
        this->flyOut();
    }
    BattleCharacter::animeUpdate();
}

/*
BattlePlayer escapeBattle
try to escape (or "be escaped") the battle. Failed if the number of continuous battle escaped
is greater than 3.
*/
bool Gameplay::BattlePlayer::escapeBattle()
{
    if(character.getBattleEscaped() >= 3)
    {
        return false;
    }
    else
    {
        character.incBattleEscaped();
        return true;
    }
}

/*
BattlePlayer leaveBattle
leave the battle normally.
*/
void Gameplay::BattlePlayer::leaveBattle()
{
    //nothing happen...
}

/*
BattlePlayer takeDamage
take the damage...if hp is below 0. The player is defeated and 
flys out the battle.
*/
void Gameplay::BattlePlayer::takeDamage(int value)
{
    character.setCurrentHp(character.getCurrentHp() - value);
    if(character.getCurrentHp() <= 0)
    {
        status = STATUS::non_active;
    }
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
	status = active;
	exp = 1;
    money = 0;
}

/*
BattleMonster constructor with attributes
initiate attributes of monster
*/
Gameplay::BattleMonster::BattleMonster(float newMaxSpeed, int newAtk, int newDef, int newMaxHP)
{
    max_speed = newMaxSpeed;
	speed = 0;
    atk = newAtk;
    def = newDef;
    max_hp = newMaxHP;
    current_hp = max_hp;
    direction = left;
    facing_right = false;
    type = monster;
	status = active;
	exp = 1;
    money = 0;
}

/*
BattleMonster copy constructor
copy constructor
*/
Gameplay::BattleMonster::BattleMonster(const BattleMonster& newMonster)
{
    max_speed = newMonster.max_speed;
	speed = 0;
    atk = newMonster.atk;
    def = newMonster.def;
    max_hp = newMonster.max_hp;
    current_hp = newMonster.current_hp;
    direction = newMonster.direction;
    facing_right = newMonster.facing_right;
    type = monster;
	status = newMonster.status;
	exp = newMonster.exp;
    money = newMonster.money;
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
	speed = 0;
    atk = newMonster.atk;
    def = newMonster.def;
    max_hp = newMonster.max_hp;
    current_hp = newMonster.current_hp;
    direction = newMonster.direction;
    facing_right = newMonster.facing_right;
    type = monster;
	status = newMonster.status;
	exp = newMonster.exp;
    money = newMonster.money;
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
    if(status == BattleCharacter::STATUS::active)
    {
        this->move(left);
    }
    else if(status == BattleCharacter::STATUS::non_active)
    {
        this->flyOut();
    }
    BattleCharacter::animeUpdate();
}

/*
BattleMonster takeDamage
take Damage. Flys out when hp is below 0.
*/
void Gameplay::BattleMonster::takeDamage(int value)
{
    current_hp = current_hp - value;
    if(current_hp <= 0)
    {
        status = STATUS::non_active;
    }
}

/*
Battle constructor
constructor of battle
*/
Gameplay::Battle::Battle(Configuration& newConfig) : config(newConfig), camera(config.window.getDefaultView())
{
    //the background is as big as the window
    background.setSize(sf::Vector2f(config.window.getSize()));
	state = started;
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
	if(it->second->getStatus() == BattleCharacter::STATUS::active)
		it->second->move(direction);
}

/*
Battle damage number constructor
set the text with font and number.
*/
Gameplay::BattleDamage::BattleDamage(const sf::Font& font, const std::string& str)
{
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(32);
    done = false;
}

/*
Battle damage number update
update the position of the number(flys up)
after 0.3s, set the boolean done to true.
*/
void Gameplay::BattleDamage::update()
{
    if(clock.getElapsedTime() < sf::seconds(0.8f))
    {
        if(updateClock.getElapsedTime() > sf::seconds(0.015f))
        {
            text.move(0,-2);
            updateClock.restart();
        }
    }
    else
    {
        done = true;
    }
}

/*
Battle damage number draw
draw the number on screen
*/
void Gameplay::BattleDamage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text);
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
    for(const std::unique_ptr<BattleDamage>& obj : damageRenderList)
    {
        target.draw(*obj);
    }
}

/*
Battle update
perform animation update and collision test(thus dealing damage)
for battle. Must called in every frame.
*/
void Gameplay::Battle::update()
{
	//do nothing if battle is already over
	if (state == overed)
		return;

    for(auto& pair : characterTree)
    {
        pair.second->animeUpdate();
        _hitWallTest(pair.second);
    }
    _collisionTest();
    
    //update the drawList
    for(auto it = damageRenderList.begin(); it != damageRenderList.end(); it++)
    {
        if((*it)->isDone())
        {
            damageRenderList.erase(it);
			if (damageRenderList.empty())
				break;
			else
				it = damageRenderList.begin();
        }
    }
    
    for(auto it = damageRenderList.begin(); it != damageRenderList.end(); it++)
    {
        (*it)->update();
    }
}

/*
Battle hitWallTest
check if the character hits the edge of the battle.
*/
void Gameplay::Battle::_hitWallTest(std::unique_ptr<BattleCharacter>& character)
{
    //if the target is hitting the invisible wall....
    //right wall
    if(character->getPosition().x >= background.getSize().x)
    {
        //if it is active monster, stop the monster
        if(character->getType() == BattleCharacter::TYPE::monster && character->getStatus() == BattleCharacter::STATUS::active)
            character->setPosition(sf::Vector2f(background.getSize().x, 500));
        //if it is player, the player leaves the battle
        if(character->getType() == BattleCharacter::TYPE::player)
        {
			character->resetEscapeBattle();
            character->leaveBattle();
            this->state = STATE::overed;
        }
    }
    else if(character->getPosition().x <= 0)//left wall
    {
        //if it is player and the player has not won the battle yet, escape the battle if it is the first 3 times
        if(character->getType() == BattleCharacter::TYPE::player)
        {
			if (haswon())
			{
				character->resetEscapeBattle();
				this->state = STATE::overed;
			}
            else if(character->getStatus() == BattleCharacter::STATUS::non_active)
            {
                //if the player has lost the battle...
                this->state = STATE::overed;//TBD
            }
            else if( character->escapeBattle())
            {
                this->state = STATE::overed;
            }
            else
            {
                character->setPosition(sf::Vector2f(1, 500)); //stop the player
            }
        }
        //the monster reaches the left wall?...
    }
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
        if(pair.second->getStatus() == BattleCharacter::STATUS::active && pair.second->getType() == BattleCharacter::TYPE::player)
        {
            for(auto& otherPair : characterTree)
            {
                if(otherPair.second->getStatus() == BattleCharacter::STATUS::active && otherPair.second->getType() == BattleCharacter::TYPE::monster && pair.first != otherPair.first && pair.second->getAABB().intersects(otherPair.second->getAABB()))
                {
                    _dealDamage(pair.second, otherPair.second);
                    return;
                }
            }
        }
    }
}

/*
Battle dealDamage 
determine the damage taken. Put the damage number to the rendering list, and set the speed of player and monster
*/
void Gameplay::Battle::_dealDamage(std::unique_ptr<BattleCharacter>& player, std::unique_ptr<BattleCharacter>& monster)
{
    //calculate damage
    int damage_playerToMonster = player->getAtk() - monster->getDef();
    int damage_monsterToPlayer = monster->getAtk() - player->getDef();
    
    //set the damage to 1 if the damage is 0 or negative
    if(damage_playerToMonster <= 0)
        damage_playerToMonster = 1;
    if(damage_monsterToPlayer <= 0)
        damage_monsterToPlayer = 1;
    
    //calculate ratio
    float damage_ratio = (static_cast<float>(damage_monsterToPlayer) / damage_playerToMonster);
    
    //if damage_ratio is greater than 1.2, set it as 1.2
    if(damage_ratio >= 1.2f)
        damage_ratio = 1.2f;
    //if damage_ratio is less than 0.8 set it as 0.8
    if(damage_ratio <= 0.8f)
        damage_ratio = 0.8f;
    
    //characters take damage
    player->takeDamage(damage_monsterToPlayer);
    monster->takeDamage(damage_playerToMonster);
    
    //player may gain exp and money if the monster is defeated
    if(monster->getStatus() == BattleCharacter::STATUS::non_active)
    {
        player->setExp(monster->getExp());
        std::unique_ptr<BattleDamage> expgain(new BattleDamage(config.fontMan.get("PressStart2P.ttf"), "exp +" + std::to_string(monster->getExp())));
        expgain->setTextColor(sf::Color::Yellow);
        expgain->setPosition(player->getPosition() - sf::Vector2f(0, 170));
        damageRenderList.push_back(std::move(expgain));
        
        int newMoney = player->getMoney() + monster->getMoney();
        player->setMoney(newMoney);
    }
    
    //put the damage number to render list
    std::unique_ptr<BattleDamage> playerDamageToken(new BattleDamage(config.fontMan.get("PressStart2P.ttf"), std::to_string(damage_monsterToPlayer)));
    
    playerDamageToken->setPosition(player->getPosition() - sf::Vector2f(0, 170));
    playerDamageToken->setTextColor(sf::Color::Red);
    
    std::unique_ptr<BattleDamage> monsterDamageToken(new BattleDamage(config.fontMan.get("PressStart2P.ttf"), std::to_string(damage_playerToMonster)));
    
    monsterDamageToken->setPosition(monster->getPosition() - sf::Vector2f(0, 170));
    monsterDamageToken->setTextColor(sf::Color::Black);
    
    damageRenderList.push_back(std::move(playerDamageToken));
    damageRenderList.push_back(std::move(monsterDamageToken));
    
    //generate two random numbers between 0 to 2
    int r1 = rand() % 4;
    int r2 = rand() % 4;
    //set the speed
	player->setSpeed((-4 * damage_ratio) - r1);
	monster->setSpeed((4 *  (1.f / damage_ratio)) + r2);
}

/*
Battle haswon
has the player won the battle?(i.e. no monster are active)
*/
bool Gameplay::Battle::haswon()
{
	for (auto& pair : characterTree)
	{
		if (pair.second->getType() == BattleCharacter::TYPE::monster && pair.second->getStatus() == BattleCharacter::STATUS::active)
			return false;
	}
	return true;
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
        int max_speed, atk, def, max_hp, exp, money;
		std::getline(input, line);
		std::stringstream ss(line);
		ss >> name >> max_speed >> atk >> def >> max_hp >> exp >> money >>spriteName;
        BattleMonster newMonster(max_speed, atk, def, max_hp);
		newMonster.setExp(exp);
        newMonster.setMoney(money);
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