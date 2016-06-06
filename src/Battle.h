#ifndef Battle_h
#define Battle_h

#include <SFML/Graphics.hpp>
#include <memory>
#include "Character.h"
#include "Configuration.h"
#include <stdlib.h>
#include <time.h>
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
        enum TYPE{player, monster}; //type of the character
		enum STATUS { active, non_active, dead }; //status of character
    protected:
        sf::Sprite sprite;      //sprite for animation
        SpriteList spriteList; //sprite intRect for animation
        STATUS status; //status of character
        
        DIRECTION direction;    //current direction of character facing
        TYPE type;
        bool facing_right;  //bool for fixing the direction
        float speed;        //current speed of the character
        float max_speed;      //the max speed of the character
        std::string name;   //name of character
        sf::Clock spriteTimer; //timer for animation
        sf::Clock moveTimer; //timer for moving
    public:
        BattleCharacter();
        //set the name of the character
        void setName(const std::string& newName){name = newName;}
        
        //get the name of the character
        std::string getName(){return name;}
        
        //load character Sprite
        virtual void loadSprite(sf::Texture& texture);

		//get the character Texture
		virtual const sf::Texture* getTexture() { return sprite.getTexture(); }
        
        //move character
        virtual void move(DIRECTION direction);
        
        //animation update. Must be called per frame
        virtual void animeUpdate();
        
        //set the position of character
        virtual void setPosition(const sf::Vector2f& pos){sprite.setPosition(pos);}
        
        //get the position of character
        virtual const sf::Vector2f& getPosition(){return sprite.getPosition();}
        
        //draw the character on screen
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
        //get the rectangle of the character
        virtual sf::FloatRect getAABB(){return sprite.getGlobalBounds();}
        
        //get the current speed of the character
        virtual float getSpeed(){return speed;}
        
        //set the current speed of the character
        virtual void setSpeed(float newSpeed){speed = newSpeed;}
        
        //get the maximum speed of the character
        virtual float getMaxSpeed(){return max_speed;}
        
        //set the maximum speed of the character
        virtual void setMaxSpeed(float value){max_speed = value;}
        
        //get the type of character
        TYPE getType(){return type;}
        
        //get the STATUS of character
        STATUS getStatus(){return status;}
        
        //try to escape the battle(failed if more than 3 times)
        virtual bool escapeBattle(){return true;}

		//reset the number of escape
		virtual void resetEscapeBattle() { ; }
        
        //try to leave the battle(success anyway)
        virtual void leaveBattle(){;}
        
        //fly out of the screen(for defeated character only0
        virtual void flyOut();
        
        //take damage
        virtual void takeDamage(int value) = 0;

		//the attributes
		virtual int getAtk() = 0;
		virtual int getDef() = 0;
		virtual int getMaxHP() = 0;
		virtual int getCurrent_hp() = 0;
		virtual int getExp() = 0;

		virtual void setAtk(int value) = 0;
		virtual void setDef(int value) = 0;
		virtual void setMaxHP(int value) = 0;
		virtual void setCurrentHP(int value) = 0;
		virtual void setExp(int value) = 0;
    };
    /*
    BattlePlayer
    the player in battle
    */
    class BattlePlayer : public BattleCharacter
    {
    private:
        Character& character; //pointer to real character
    public:
        BattlePlayer(Character& character);
        void animeUpdate();
        bool escapeBattle();
        void leaveBattle();
        void takeDamage(int value);
        
		int getAtk() { return character.getAtk(); }
		int getDef() { return character.getDef(); }
		int getMaxHP() { return character.getMaxHp(); }
		int getCurrent_hp() { return character.getCurrentHp(); }
		int getExp(){ return character.getExp(); }

		void setAtk(int value) { character.setAtk(value); }
		void setDef(int value) { character.setDef(value); }
		void setMaxHP(int value) { character.setMaxHp(value); }
		void setCurrentHP(int value) { character.setCurrentHp(value); }
		void setExp(int value) {character.gainExp(value);} //gain exp instead

		void resetEscapeBattle() { character.resetBattleEscaped(); }
    };
    /*
    BattleMonster
    the monster in the battle
    */
    class BattleMonster : public BattleCharacter
    {
    private:
        int atk; //attack value of monster
        int def; //defence value of monster
        int max_hp; //maximum hp of monster
        int current_hp; //current hp of monster
		int exp; //exp gained if the monster is defeated
    public:
        BattleMonster();
        BattleMonster(float max_speed, int atk, int def, int max_hp);
        BattleMonster(const BattleMonster&);
        BattleMonster& operator=(const BattleMonster&);

		float getMaxSpeed() { return max_speed; }
		int getAtk() { return atk; }
		int getDef() { return def; }
		int getMaxHP() { return max_hp; }
		int getCurrent_hp() { return current_hp; }
		int getExp() { return exp; }

		void setMaxSpeed(float value) { max_speed = value; }
		void setAtk(int value) { atk = value; }
		void setDef(int value) { def = value; }
		void setMaxHP(int value) { max_hp = value; }
		void setCurrentHP(int value) { current_hp = value; }
		void setExp(int value) { exp = value; }

        void animeUpdate();
        void takeDamage(int value);
    };
    
    /*
    Battle damage number class
    the damage number that poped out when player and monster fight each other
    */
    class BattleDamage : public sf::Drawable
    {
    private:
        sf::Text text;
        bool done;
        sf::Clock clock;    //for determine if time > 0.3s
        sf::Clock updateClock;  //for determine a frame time
    public:
        BattleDamage(const sf::Font& font, const std::string& string);
        void update();
        bool isDone(){return done;}
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setPosition(const sf::Vector2f& pos){text.setPosition(pos);}
        void setTextColor(const sf::Color& color){text.setColor(color);}
    };
    /*
     Battle class
     Handles the battle mechanism in the game.
     */
    class Battle : public sf::Drawable
    {
	public:
		//the state of the battle
		enum STATE{started, overed};
    private:
        //reference to the configuration
        Configuration& config;
        
        //a tree of all BattleCharacter in the battle
        std::map<std::string, std::unique_ptr<BattleCharacter>> characterTree;
        
        //the background image of battle
        sf::RectangleShape background;

		//camera of battle
		sf::View camera;

		//the state of the battle
		STATE state;
        
        //a list of drawable things
        std::list<std::unique_ptr<BattleDamage>> damageRenderList;

        void _collisionTest();
		void _dealDamage(std::unique_ptr<BattleCharacter>& player, std::unique_ptr<BattleCharacter>& monster);
        void _hitWallTest(std::unique_ptr<BattleCharacter>& character);
		bool haswon();
    public:
        Battle(Configuration& config);
        void setBackGround(sf::Texture* texture);
        void addCharacter(std::unique_ptr<BattleCharacter> charPtr);
        void setCharPosition(const std::string& charName, int value);
        void moveCharacter(const std::string& charName, BattleCharacter::DIRECTION direction);
		const sf::View& getCamera() { return camera; }
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void update();
        STATE getState(){return state;}
    };
    
    /*
    BattleFactory
    generate Battles
    */
    class BattleFactory
    {
    private:
        Configuration& config;
        std::map<std::string, BattleMonster> monsterTree; //For receviving monster's data
    public:
        BattleFactory(Configuration& config);
		std::shared_ptr<Gameplay::Battle> generateBattle(tmx::MapObject* battleObject);
    };

}
#endif /* Battle_h */
