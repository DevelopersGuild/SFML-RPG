#ifndef Battle_h
#define Battle_h

#include <SFML/Graphics.hpp>
#include "Character.h"
/*
 Battle object
 -to start a battle, the game needs a battle Object.
 -a map has two types: safe, non-safe(monster encounter)
 -a map may have several battle zones, which defined specified what monster may encountered. If the move function found the battle zone, it will return the battle zone as battle Object.
 -a map must contain a global monster battle Object. The move function will return this object if no battle zone found.
 -the battle Object contains the rate of encounter, and a list of monster encounter chance.
 -When player moves, the function will perform rate of encounter check. If passed, nothing happen. If failed, battle begins.
 -If battle begins, the game system will call createBattle() function, which ask Battle factory to generate a battle.
 
 -players have shared_ptr to a battle obj.
 -players have states: battle, non-battle.
 
 -The Battle factory(BF) generates battles.
 -BF has a tree of monster.
 -BF needs to be initalized: read the monster file and save the monster's data into the tree.
 -BF goes through monster encounter change in the battle object and decide which monsters are in the battle.
 -BF goes through the battle object and decide the back ground of battle.
 -BF automatically sets the shared_ptr for player who initiated the battle. (So the player initiated the battle is the only owner, before any player joins the battle.) Also set the player’s state to battle.
 -if player is already in a battle, then it is impossible to trigger another battle. Therefore assert() the program if player’s shared_ptr is not nullptr.
 
 -When battle is created, put battling dust in the map.
 -when called player.joinBattle(), player set his/her shared_ptr to battle obj. Also set the player’s state to battle.
 
 -Battle has a charName map : std::map<std::string, Battle::Character>.
 -Battle::Character has states: active, non-active(cannot collide), died, left. The characters are non-active only when they are defeated and “flying out” of the map.
 -Battle has a renderList, which helps to draw characters, monsters and temporary objects such as damage number, spell… etc.
 -Each player's Battle::Character has a ptr(ref of unique_ptr) to GamePlay::Character(so they can access hp, at,def, speed…etc.)
 -Each monster's Battle::Character has a ptr(unique_ptr) to dynamic allocated GamePlay::Character.
 -Battle has moving function : moveCharacter(Direction, NameOfCharacter). Non-active characters cannot be moved.
 -Unlike the map, characters in the battle move with speed but not displacement. (So there is bouncing animation.)
 -Battle has a function : update(). This function updates the sprite’s location.
 -If Character collides with monster, perform Battle::Character::Attack(monsterObj),
 this function will evaluate the damage duel to the monster and the damage taken from monster. Place the damage number to renderList. Modify the speed of both Character and monster so they “bounce back”.
 -After the Attack function, if monster’s hp is below 0, set it as non-active, and “fly out” of the map. Character gains exp from monster. The one that contribute the last hit gains exp.
 -After the Attack function, if character’s hp is below 0, set it as non-active, and “fly out” of the map. When done, set the characters as died.
 
 -The GameSystem keeps checking the character’s status. If the character dies, reset the shared_ptr and teleport the player to previous town. If the character left, reset the shared_ptr.
 -For every reset of shared_ptr, check if it is the last one(i.e. unique) to Battle. If it is, remove the battling dust in the map.
 
 -the monster will move to the nearest player.
 
 -Character can use potion in the battle by calling usePotion() function.
 
 -When Character gains exp, perform level up check and update attributes.
 
 -Boss fight is a special case: the one that does greatest damage wins the game.
 -Once the boss is defeated, show message to all players and rank panel. Then ends the game.
 */
namespace Gameplay
{
    /*
    BattleCharacters
    base class of characters in battle
    */
    class BattleCharacter : public sf::Drawable
    {
    public:
        enum DIRECTION{left, right}; //direction of the character
    protected:
        sf::Sprite sprite;      //sprite for animation
        SpriteList spriteList; //sprite intRect for animation
        enum STATUS{active, non_active, dead} status; //status of character
        DIRECTION direction;    //current direction of character facing
        float speed;        //current speed of the character
        int max_speed;      //the max speed of the character
        std::string name;   //name of character
        sf::Clock spriteTimer; //timer for animation
        sf::Clock moveTimer; //timer for moving
    public:
        //set the name of the character
        void setName(const std::string& newName){name = newName;}
        
        //load character Sprite
        virtual void loadSprite(sf::Texture& texture);
        
        //move character
        virtual void move(DIRECTION direction);
        
        //animation update. Must be called per frame
        virtual void animeUpdate();
        
        //set the position of character
        virtual void setPosition(const sf::Vector2f& pos){sprite.setPosition(pos);}
        
        //draw the character on screen
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
    /*
    BattlePlayer
    the player in battle
    */
    class BattlePlayer : public BattleCharacter
    {
    private:
        Character* charPtr; //pointer to real character
    public:
        
    };
    /*
    BattleMonster
    the monster in the battle
    */
    class BattleMonster : public BattleCharacter
    {
    private:
        float max_speed; //max speed of monster
        int atk; //attack value of monster
        int def; //defence value of monster
        int max_hp; //maximum hp of monster
        int current_hp; //current hp of monster
    public:
        
    };
    /*
     Battle class
     Handles the battle mechanism in the game.
     */
    class Battle
    {
    private:
        //a tree of all BattleCharacter in the battle
        std::map<std::string, BattleCharacter> characterTree;
        
        //the background image of battle
        sf::Sprite background;
        
    public:
        
    };
    
    /*
    BattleFactory
    generate Battles
    */
    class BattleFactory
    {
    private:
        
    public:
        
    };

}
#endif /* Battle_h */
