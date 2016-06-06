#include "GameInterface.h"
using namespace Gameplay;

GameInterface::GameInterface(GameSystem* newSystem) :
	system(newSystem),
	charInfo(newSystem->config)
{
	camera.setSize(500, 375);

	//initialize the transitionRect
	gui.setWindow(system->config.window);
	transitionRect = std::make_shared<tgui::Panel>();
	gui.add(transitionRect);
	transitionRect->setBackgroundColor(tgui::Color(sf::Color::Black));
	transitionRect->hide();

	charInfo.addToGui(gui);
	transitionRect->moveToFront();
}

void Gameplay::GameInterface::draw()
{
	sf::RenderWindow& window = system->config.window;
	updateCamera();	//update the camera

	//draw the map
	window.draw(*system->currentMap);

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
	panel->add(expBar);

	text_level = std::make_shared<tgui::Label>();
	text_level->setText("Lv 1");
	text_level->setTextSize(24);
	text_level->setTextColor(tgui::Color(sf::Color::Black));
	text_level->setPosition(5, 5);
	panel->add(text_level);
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
}
