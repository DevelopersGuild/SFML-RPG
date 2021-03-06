#ifndef GameInterface_h
#define GameInterface_h

#include "GameSystem.h"
#include "Configuration.h"
#include "MiniMap.h"

namespace Gameplay
{
	/*
	CharInfoInterface
	the interface at the left-top corner
	includes hp bar, exp bar and level...
	*/
	class CharInfoInterface
	{
	private:
		tgui::Panel::Ptr panel;
		tgui::Label::Ptr text_hp;
		tgui::ProgressBar::Ptr hpBar;
		tgui::Label::Ptr text_exp;
		tgui::ProgressBar::Ptr expBar;
		tgui::Label::Ptr text_level;
        tgui::Picture::Ptr coin;
        tgui::Label::Ptr text_money;
	public:
		CharInfoInterface(Configuration& config);
		void addToGui(tgui::Gui& gui);
		void update(Player* player);
	};

    /*
    InGameMenu class
    the inGmae menu during the game.
    provide a detail view of character. Show setting and exit button.
    */
    class InGameMenu
    {
    private:
		sf::Clock time_LastSwitch;
        tgui::Panel::Ptr panel;
        tgui::Label::Ptr player_characterName;
        tgui::Label::Ptr player_level;
        tgui::Label::Ptr player_hp;
        tgui::Label::Ptr player_exp;
        tgui::Label::Ptr player_attack;
        tgui::Label::Ptr player_defense;
        tgui::Label::Ptr player_speed;
        tgui::Label::Ptr player_battle_speed;
        tgui::Label::Ptr player_money;
        tgui::Label::Ptr button_settings;
        tgui::Label::Ptr button_leave;
    public:
        InGameMenu(Configuration& config);
        void addToGui(tgui::Gui& gui);
        void show();
        void hide();
        void updateData(Player* player);
		bool isDisplaying() { return panel->isVisible(); }
    };
    
    /*
    Dialogue class
    handling the dialogue graphics in the game.
    */
    class Dialogue
    {
    private:
        tgui::Panel::Ptr panel;
        tgui::Label::Ptr text;
    public:
        Dialogue(Configuration& config);
        void addToGue(tgui::Gui& gui);
        void show(const std::string& str);
        void hide();
        bool isDisplaying(){return panel->isVisible();}
    };
	/*
	GameInterface class
	Handles inputs from this computer
	*/
	class GameInterface
	{
	private:
		Gameplay::GameSystem* system;	//the interface calls system's function.
		sf::View camera;
		//sf::RectangleShape transitionRect;	//the rect that blocks the screen in transition state
		tgui::Gui gui;
		tgui::Panel::Ptr transitionRect;
		CharInfoInterface charInfo;
        InGameMenu inGameMenu;
        Dialogue dialogue;
		MiniMap miniMap;

		void updateCamera();
	public:
		GameInterface(GameSystem* system);

		//draw the game screen on the window.
		void draw();

		//update the gui of the interface, must be called in every frame
		void updateGUI(sf::Event& event);

		//update the mini map
		void updateMiniMap();

		//set the transition layer to block the screen
		void setTransition();

		//move the transition away from the screen
		void exitTransition();
		
        //set on/off the in game menu
        void switchInGaemMenu();
        
        //set on/off the dialogue box
        //note: string argument is only necessary when switching on.
        void switchDialogue(const std::string& str);

		//set on/off the miniMap
		void showMiniMap() { miniMap.show(); }
		void hideMiniMap() { miniMap.hide(); }

		//is the in game menu displayed?
		bool isDisplayingInGameMenu() { return inGameMenu.isDisplaying(); }
        
        //is dialogueBox displaing?
        bool isDisplayingDialogue(){return dialogue.isDisplaying();}
        
		//get the camera
		const sf::View& getCamera() { return camera; }
	};
}


#endif /* GameInterface_h */
