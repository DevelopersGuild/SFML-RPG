#include "GameInterface.h"
#include <iomanip>
using namespace Gameplay;

GameInterface::GameInterface(GameSystem* newSystem) :
	system(newSystem),
	charInfo(newSystem->config),
    inGameMenu(newSystem->config),
    dialogue(newSystem->config),
	miniMap(newSystem->config)
{
	camera.setSize(500, 375);

	//initialize the transitionRect
	gui.setWindow(system->config.window);
	transitionRect = std::make_shared<tgui::Panel>();
	gui.add(transitionRect);
	transitionRect->setBackgroundColor(tgui::Color(sf::Color::Black));
	transitionRect->hide();

	charInfo.addToGui(gui);
    inGameMenu.addToGui(gui);
    dialogue.addToGue(gui);
	miniMap.addToGui(gui);
	transitionRect->moveToFront();
}

void Gameplay::GameInterface::draw()
{
	sf::RenderWindow& window = system->config.window;
	updateCamera();	//update the camera

	//draw the map
	window.draw(*system->currentMap);

    //draw every NPCs in the same map
    for (auto& npc : system->npcRenderList)
    {
        window.draw(*npc);
    }
    
	//draw every player in the map
	for (auto& pair : system->playerTree)
	{
		window.draw(pair.second);
	}

    //if it is in battle, draw the battle
    if(system->currentBattle)
    {
        system->currentBattle->update();
		window.setView(system->currentBattle->getCamera());
        sf::RectangleShape test;
        test.setFillColor(sf::Color::Red);
        window.draw(*system->currentBattle);
        window.draw(test);
    }

	charInfo.update(system->thisPlayerPtr);
    gui.draw();
	//debug
	
	//system->currentMap->Draw(system->config.window, tmx::MapLayer::DrawType::Debug, true);
}

void Gameplay::GameInterface::updateGUI(sf::Event & event)
{
	gui.handleEvent(event);
	//update the miniMap
	miniMap.update(system->getPlayerPosition(), system->currentMap);
}

//Peter's function
void Gameplay::GameInterface::updateCamera()
{
	//get the map size, player's position, and camera size
	const sf::Vector2u& currentMapSize = system->currentMap->GetMapSize();
	const sf::Vector2f& playerPosition = system->thisPlayerPtr->getPosition();
	const sf::Vector2f& cameraSize = camera.getSize();

    sf::Vector2f tempCameraPosition = sf::Vector2f(playerPosition.x, playerPosition.y);
    //******************************************************************************
    //Peter's part
    //example: the camera stops at some point when player approach the top of the map
    // x, y is temporary camera position.
    
    float x, y; x = playerPosition.x; y = playerPosition.y;
    if (playerPosition.y < cameraSize.y / 2)
    {
        //camera.setCenter(playerPosition.x, cameraSize.y / 2);
        y = cameraSize.y / 2;
        if (playerPosition.x < cameraSize.x / 2)
            x = cameraSize.x / 2;
        else if (playerPosition.x > currentMapSize.x - cameraSize.x / 2)
            x = currentMapSize.x - cameraSize.x / 2;
    }
    else if (playerPosition.y > currentMapSize.y - cameraSize.y / 2)
    {
        //camera.setCenter(playerPosition.x, currentMapSize.y - cameraSize.y / 2);
        y = currentMapSize.y - cameraSize.y / 2;
        if (playerPosition.x < cameraSize.x / 2)
            x = cameraSize.x / 2;
        else if (playerPosition.x > currentMapSize.x - cameraSize.x / 2)
            x = currentMapSize.x - cameraSize.x / 2;
    }
    else if (playerPosition.x < cameraSize.x / 2)
        x = cameraSize.x / 2;
    else if (playerPosition.x > currentMapSize.x - cameraSize.x / 2)
        x = currentMapSize.x - cameraSize.x / 2;
    //camera.setCenter(playerPosition);
    tempCameraPosition.x = x;
    tempCameraPosition.y = y;
    camera.setCenter(tempCameraPosition);

	//....
	//....
	//....

	//end of Peter's part
	//******************************************************************************
	//ask window to draw the camera in the next render function
	system->config.window.setView(camera);
}

void Gameplay::GameInterface::setTransition()
{
	//set the transitionRect to the right of the current camera
	transitionRect->setSize(gui.getSize());
	//const sf::Vector2f& viewSize = view.getSize();
	transitionRect->showWithEffect(tgui::ShowAnimationType::SlideFromRight, sf::seconds(0.2f));

	//render loop to make sure Transition animation is not called again in 0.2s
	sf::Clock clock;
	sf::RenderWindow& window = system->config.window;
	while (clock.getElapsedTime() < sf::seconds(0.2f))
	{
		window.clear();
		this->draw();
		window.display();
	}
}

void Gameplay::GameInterface::exitTransition()
{
	transitionRect->hideWithEffect(tgui::ShowAnimationType::SlideToLeft, sf::seconds(0.2f));

	//render loop to make sure Transition animation is not called again in 0.2s
	sf::Clock clock;
	sf::RenderWindow& window = system->config.window;
	while (clock.getElapsedTime() < sf::seconds(0.2f))
	{
		window.clear();
		this->draw();
		window.display();
	}
}

void Gameplay::GameInterface::switchInGaemMenu()
{
    if(isDisplayingInGameMenu())
    {
        inGameMenu.hide();
    }
    else
    {
        inGameMenu.updateData(system->thisPlayerPtr);
        inGameMenu.show();
    }
}

void Gameplay::GameInterface::switchDialogue(const std::string& str)
{
    if(dialogue.isDisplaying())
        dialogue.hide();
    else
        dialogue.show(str);
}

//*************************************************************
Gameplay::CharInfoInterface::CharInfoInterface(Configuration& config)
{
	panel = std::make_shared<tgui::Panel>();
	panel->setSize(400, 300);
	panel->setBackgroundColor(tgui::Color(0, 0, 0, 0));
	panel->setFont(tgui::Font(config.fontMan.get("Carlito-Italic.ttf")));
	
	text_hp = std::make_shared<tgui::Label>();
	text_hp->setText("HP");
	text_hp->setTextSize(24);
	text_hp->setTextColor(tgui::Color(sf::Color::Black));
	text_hp->setPosition(5, 34);
	panel->add(text_hp);

	hpBar = std::make_shared<tgui::ProgressBar>();
	hpBar->setPosition(5, 60);
	hpBar->setSize(350, 20);
	hpBar->setMaximum(100);
	hpBar->setMinimum(0);
	hpBar->setText(sf::String("100 / 100"));
	hpBar->setValue(100);
	std::shared_ptr<tgui::ProgressBarRenderer> pRender = hpBar->getRenderer();
	pRender->setBackgroundColor(tgui::Color(0,0,0,40));
	pRender->setForegroundColor(tgui::Color(sf::Color::Red));
	pRender->setTextColor(tgui::Color(sf::Color::Black));
	panel->add(hpBar);

	text_exp = std::make_shared<tgui::Label>();
	text_exp->setText("EXP");
	text_exp->setTextSize(24);
	text_exp->setTextColor(tgui::Color(sf::Color::Black));
	text_exp->setPosition(5, 79);
	panel->add(text_exp);

	expBar = std::make_shared<tgui::ProgressBar>();
	expBar->setPosition(5, 105);
	expBar->setSize(350, 20);
	expBar->setMaximum(100);
	expBar->setMinimum(0);
	expBar->setText(sf::String("0%"));
	expBar->setValue(0);
	std::shared_ptr<tgui::ProgressBarRenderer> eRender = expBar->getRenderer();
	eRender->setBackgroundColor(tgui::Color(0,0,0,40));
	eRender->setForegroundColor(tgui::Color(sf::Color::Yellow));
	eRender->setTextColor(tgui::Color(sf::Color::Black));
	panel->add(expBar);

	text_level = std::make_shared<tgui::Label>();
	text_level->setText("Lv 1");
	text_level->setTextSize(24);
	text_level->setTextColor(tgui::Color(sf::Color::Black));
	text_level->setPosition(5, 5);
	panel->add(text_level);
    
    coin = std::make_shared<tgui::Picture>();
    coin->setSize(30,30);
    coin->setPosition(5, 135);
    coin->setTexture(config.texMan.get("coin.png"));
    panel->add(coin);
    
    text_money = std::make_shared<tgui::Label>();
    text_money->setTextSize(30);
    text_money->setPosition(40, 127);
    text_money->setText("10");
    panel->add(text_money);
}

void Gameplay::CharInfoInterface::addToGui(tgui::Gui & gui)
{
	gui.add(panel);
}

void Gameplay::CharInfoInterface::update(Player * player)
{
	int currentHp = player->getCurrentHp();
	int maxHp = player->getMaxHp();
	int currentExp = player->getCurrentExp();
	int expCap = player->getExpCap();
	int level = player->getLevel();
    int money = player->getMoney();

	hpBar->setText(sf::String(std::to_string(currentHp) + " / " + std::to_string(maxHp)));
	hpBar->setMaximum(maxHp);
	if (currentHp >= 0)
		hpBar->setValue(currentHp);
	else
		hpBar->setValue(0);

	int percent = static_cast<int>(static_cast<float>(currentExp) / expCap * 100);
	expBar->setText(sf::String(std::to_string(percent) + "%"));
	expBar->setMaximum(expCap);
	expBar->setValue(currentExp);

	text_level->setText("Lv " + std::to_string(level));
    text_money->setText(std::to_string(money));
}
//**************************************************************
Gameplay::InGameMenu::InGameMenu(Configuration& config)
{
    panel = std::make_shared<tgui::Panel>();
    panel->setSize(400, 600);
    panel->setPosition(314, 84);
    panel->setBackgroundColor(tgui::Color(0,0,0,140));
    panel->setFont(tgui::Font(config.fontMan.get("Carlito-Italic.ttf")));
    panel->hide();
    
    player_characterName = std::make_shared<tgui::Label>();
    player_characterName->setText("Player");
    player_characterName->setTextColor(tgui::Color(sf::Color::White));
    player_characterName->setPosition(5,15);
    player_characterName->setTextSize(30);
    panel->add(player_characterName);
    
    player_level = std::make_shared<tgui::Label>();
    player_level->setText("Level: ");
    player_level->setTextColor(tgui::Color(sf::Color::White));
    player_level->setPosition(200,15);
    player_level->setTextSize(30);
    panel->add(player_level);
    

    player_hp = std::make_shared<tgui::Label>();
    player_hp->setText("HP: ");
    player_hp->setTextColor(tgui::Color(sf::Color::White));
    player_hp->setPosition(20, 90);
    player_hp->setTextSize(30);
    panel->add(player_hp);
    
    player_exp = std::make_shared<tgui::Label>();
    player_exp->setText("EXP: ");
    player_exp->setTextColor(tgui::Color(sf::Color::White));
    player_exp->setPosition(20,140);
    player_exp->setTextSize(30);
    panel->add(player_exp);
    
    player_attack = std::make_shared<tgui::Label>();
    player_attack->setText("ATTACK: ");
    player_attack->setTextColor(tgui::Color(sf::Color::White));
    player_attack->setPosition(20,190);
    player_attack->setTextSize(30);
    panel->add(player_attack);
    
    player_defense = std::make_shared<tgui::Label>();
    player_defense->setText("DEFENSE: ");
    player_defense->setTextColor(tgui::Color(sf::Color::White));
    player_defense->setPosition(20,240);
    player_defense->setTextSize(30);
    panel->add(player_defense);
    
    player_speed = std::make_shared<tgui::Label>();
    player_speed->setText("SPEED: ");
    player_speed->setTextColor(tgui::Color(sf::Color::White));
    player_speed->setPosition(20,290);
    player_speed->setTextSize(30);
    panel->add(player_speed);
    
    player_battle_speed = std::make_shared<tgui::Label>();
    player_battle_speed->setText("BATTLE SPEED: ");
    player_battle_speed->setTextColor(tgui::Color(sf::Color::White));
    player_battle_speed->setPosition(20,340);
    player_battle_speed->setTextSize(30);
    panel->add(player_battle_speed);
    
    player_money = std::make_shared<tgui::Label>();
    player_money->setText("MONEY: ");
    player_money->setTextColor(tgui::Color(sf::Color::White));
    player_money->setPosition(20,390);
    player_money->setTextSize(30);
    panel->add(player_money);
    
    
    button_settings = std::make_shared<tgui::Label>();
    button_settings->setText("Settings");
    button_settings->setTextColor(tgui::Color(sf::Color::White));
    button_settings->setPosition(50,500);
    button_settings->setTextSize(20);
    panel->add(button_settings);
    
    button_leave = std::make_shared<tgui::Label>();
    button_leave->setText("Leave");
    button_leave->setTextColor(tgui::Color(sf::Color::White));
    button_leave->setPosition(250,500);
    button_leave->setTextSize(20);
    panel->add(button_leave);
    

}

void Gameplay::InGameMenu::addToGui(tgui::Gui& gui)
{
    gui.add(panel);
}

void Gameplay::InGameMenu::updateData(Gameplay::Player *player)
{
    player_characterName->setText(player->getName());
    player_level->setText("Lv. " + std::to_string(player->getLevel()));
    player_hp->setText("HP: " + std::to_string(player->getCurrentHp()) + "/" + std::to_string(player->getMaxHp()));
    player_exp->setText("EXP: " + std::to_string(player->getCurrentExp()) + "/" + std::to_string(player->getExpCap()));
    player_attack->setText("Attack: " + std::to_string(player->getAtk()));
    player_defense->setText("Defense: " + std::to_string(player->getDef()));
    player_money->setText("Money: " + std::to_string(player->getMoney()));
    

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << player->getSpeed();
    std::string s = stream.str();
    player_speed->setText("Speed: " + s);
    stream.clear();
    
    stream << std::fixed << std::setprecision(2) << player->getBattleSpeed();
    
    player_battle_speed->setText("Battle speed: " + s);
    
}

void Gameplay::InGameMenu::show()
{
	if (time_LastSwitch.getElapsedTime() > sf::seconds(0.2f))
	{
		panel->showWithEffect(tgui::ShowAnimationType::Scale, sf::seconds(0.2f));
		time_LastSwitch.restart();
	}		
}

void Gameplay::InGameMenu::hide()
{
	if (time_LastSwitch.getElapsedTime() > sf::seconds(0.2f))
	{
		panel->hideWithEffect(tgui::ShowAnimationType::Scale, sf::seconds(0.2f));
		time_LastSwitch.restart();
	}
}
//****************************************************************
Gameplay::Dialogue::Dialogue(Configuration& config)
{
    panel = std::make_shared<tgui::Panel>();
    panel->setSize(config.window.getSize().x * 0.8, config.window.getSize().y * 0.30);
    panel->setPosition(config.window.getSize().x * 0.1, config.window.getSize().y * 0.60);
    panel->setBackgroundColor(tgui::Color(0,0,0,80));
	panel->setFont(tgui::Font(config.fontMan.get("Carlito-Regular.ttf")));
    text = std::make_shared<tgui::Label>();
    text->setTextColor(tgui::Color(sf::Color::White));
    text->setTextSize(26);
    text->setPosition(panel->getSize().x * 0.10, panel->getSize().y * 0.15);
    text->setAutoSize(true);
    text->setMaximumTextWidth(panel->getSize().x * 0.8);
    panel->add(text);
    panel->hide();
}

void Gameplay::Dialogue::show(const std::string& str)
{
    text->setText(str);
    panel->show();
}

void Gameplay::Dialogue::hide()
{
    panel->hide();
}

void Gameplay::Dialogue::addToGue(tgui::Gui& gui)
{
    gui.add(panel);
}