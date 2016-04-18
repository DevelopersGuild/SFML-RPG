#include "Lobby.h"

Lobby::Lobby(Configuration & newConfig) :
	config(newConfig)
{
	panel = std::make_shared<tgui::Panel>();
	panel->setSize(822, 614);
	panel->setPosition(102, 77);
	panel->setBackgroundColor(tgui::Color(0, 0, 0, 60));

	backButton = std::make_shared<tgui::Button>();
	panel->add(backButton);
	backButton->setText("Back");
	backButton->setPosition(65, 542);

	startButton = std::make_shared<tgui::Button>();
	panel->add(startButton);
	startButton->setText("Start");
	startButton->setPosition(571, 546);

	chatBox = std::make_shared<tgui::ChatBox>();
	panel->add(chatBox);
	chatBox->setSize(340, 150);
	chatBox->setPosition(51, 323);
	chatBox->addLine("Test");

	chatInput = std::make_shared<tgui::TextBox>();
	panel->add(chatInput);
	chatInput->setSize(340, 22);
	chatInput->setPosition(51, 473);
	chatInput->setMaximumCharacters(33);

	chatInputButton = std::make_shared<tgui::Button>();
	panel->add(chatInputButton);
	chatInputButton->setSize(34, 22);
	chatInputButton->setPosition(357, 473);
	chatInputButton->setText("send");
	chatInputButton->connect("mousereleased", [&]() {
		std::string str = chatInput->getText();
		if (str != "")
		{
			chatBox->addLine(str);
			chatInput->setText("");
		}
			
	});

	mapPicture = std::make_shared<tgui::Picture>();
	panel->add(mapPicture);
	mapPicture->setSize(234, 210);
	mapPicture->setPosition(535, 50);
	mapPicture->setTexture(config.texMan.get("shadow_kingdom_map.png"));
}

void Lobby::addTgui(tgui::Gui & gui)
{
	gui.add(panel);
}

void Lobby::hide()
{
	panel->hide();
}

void Lobby::show()
{
	panel->show();
}

void Lobby::showWithEffect()
{
	panel->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(0.2));
}
