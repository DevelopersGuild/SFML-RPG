#include "Battle.h"

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
    //if the direction is different, flip the sprite
    //if(direction != newDirection)
    
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
    if(spriteTimer.getElapsedTime() > sf::seconds(0.8))
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