#pragma once
#include "Game.h"
class SceneController
{
public:
	SceneController();

	void prepareScenes();

	void setCurrentScene(std::string name);
	void handleInputs(KeyboardInput& input);

	void updateCurrentScene();
	
	void drawCurrentScene();

	void setGame(Game* game);

private:
	std::string currentScene;
	Game* game;

	

	void prepareMenu();
	void prepareStage();

	void handleMenuInputs(KeyboardInput& input);
	void handleStageInputs(KeyboardInput& input);

	void updateMenu();
	void updateStage();

	void drawMenu();
	void drawStage();

	//Menu requisites
	Sprite menuLogo;
	Sprite menuBg;
	int currentMenuOptionSelected;
	const int MAX_MENU_OPTIONS = 3;
	int soundEffects;
};

