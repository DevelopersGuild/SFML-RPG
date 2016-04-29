#include "InGame.h"
#include <sstream>

InGame::InGame(Configuration& newConfig, std::unique_ptr<StartInfo> startInfo) :
	config(newConfig),
    state(STATE::loading)
{

}

void InGame::run()
{
	sf::RenderWindow& window = config.window;

	/*Testing only*/
	tgui::Gui gui;
	gui.setWindow(window);

	gui.setFont(tgui::Font(config.fontMan.get("Carlito-Bold.ttf")));

	tgui::Picture::Ptr background = std::make_shared<tgui::Picture>();
	background->setTexture(config.texMan.get("Book.png"));
	background->setSize(gui.getSize());
	gui.add(background);

	tgui::ProgressBar::Ptr progressBar = std::make_shared<tgui::ProgressBar>();
	gui.add(progressBar);
	progressBar->setPosition(50, 700);
	progressBar->setSize(930, 20);
	progressBar->setMinimum(0);
	progressBar->setMaximum(100);
	progressBar->setText("loading...0%");
	unsigned int percent = 0;
	sf::Clock clock;

	tgui::Panel::Ptr panel = std::make_shared<tgui::Panel>();
	gui.add(panel);
	panel->setSize(820, 200);
	panel->setPosition(100, 450);
	panel->setBackgroundColor(tgui::Color(192, 192, 192, 150));

	tgui::Label::Ptr tips = std::make_shared<tgui::Label>();
	panel->add(tips);
	tips->setPosition(20, 20);
	tips->setTextSize(24);
	tips->setText("This is testing. Click cross button to leave.");
	
	/*End of Testing only*/

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			gui.handleEvent(event);
		}
		
		config.cursor.update();

		if (percent < 100 && clock.getElapsedTime() > sf::seconds(0.1))
		{
			percent++;
			std::stringstream ss;
			ss << percent;
			progressBar->setText(sf::String("loading...") + sf::String(ss.str()) + sf::String("%"));
			progressBar->setValue(percent);
			clock.restart();
		}
		window.clear();
		gui.draw();
		window.draw(config.cursor);
		window.display();
	}
}
