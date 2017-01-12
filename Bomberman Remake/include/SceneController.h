#pragma once
#include "Game.h"
class SceneController
{
public:
	SceneController();

	/*
	Runs the preparation functions for all the specified scenes
	*/
	void prepareScenes();

	/*
	Sets the current scene and runs all the logic required to run it
	@param name of the new current scene
	*/
	void setCurrentScene(std::string name);

	/*
	Checks all the inputs in the queue that are needed for the current scene
	@param input class
	*/
	void handleInputs(KeyboardInput& input);
	
	void updateCurrentScene();
	
	void drawCurrentScene();

	void setGame(Game* game);

private:
	std::string currentScene;
	Game* game;

	
	void prepareMenu();
	void prepareStage();
	void prepareDifficultyMenu();

	void handleMenuInputs(KeyboardInput& input);
	void handleStageInputs(KeyboardInput& input);
	void handleDifficultyMenuInputs(KeyboardInput& input);

	void updateMenu();
	void updateStage();
	void updateDifficultyMenu();

	void drawMenu();
	void drawStage();
	void drawDifficultyMenu();

	//Menu requisites
	Sprite menuLogo;
	Sprite menuBg;
	int currentMenuOptionSelected;
	const int MAX_MENU_OPTIONS = 3;
	int soundEffects;

	//Difficulty requisites
	Sprite difficultySelectLogo;
	int currentDifficultyOptionSelected;
	const int MAX_DIFICULTY_OPTIONS = 3;
};

