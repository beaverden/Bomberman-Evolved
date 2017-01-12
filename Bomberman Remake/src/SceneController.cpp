#include "SceneController.h"
#include <algorithm>


SceneController::SceneController() {}

void SceneController::prepareScenes()
{
	prepareMenu();
	prepareStage();
	prepareDifficultyMenu();
}

void SceneController::prepareMenu()
{
	menuBg.setTexture("resources/Images/menu.jpg");
	menuBg.setRect({ 254, 0, 636, 636 });

	currentMenuOptionSelected = 0;
	soundEffects = 1;
}

void SceneController::prepareStage() {}

void SceneController::prepareDifficultyMenu() 
{
	currentDifficultyOptionSelected = 0;
	difficultySelectLogo.setTexture("resources/Images/difficulty_select.jpg");
	difficultySelectLogo.setRect({ 0, 0, 800, 800 });
}



void SceneController::setCurrentScene(std::string name)
{
	currentScene = name;

	if (name == "menu")
	{
		
		SoundEffects::playMusic("resources/Sounds/Menu_theme.mp3");
	}
	else if (name == "stage")
	{
		game->resetGame();
		SoundEffects::playMusic("resources/Sounds/Stage_theme.mp3");
	}
	else if (name == "difficulty_select") {}
}



void SceneController::handleInputs(KeyboardInput& input)
{
	if (currentScene == "menu")
	{
		handleMenuInputs(input);
	}
	else if (currentScene == "stage")
	{
		handleStageInputs(input);
	}
	else if (currentScene == "difficulty_select")
	{
		handleDifficultyMenuInputs(input);
	}
}

void SceneController::handleMenuInputs(KeyboardInput& input)
{
	if (input.closePressed)
	{
		game->ended = true;
		return;
	}
	if (input.wasKeyPressed(SDL_SCANCODE_DOWN) ||
		input.wasKeyPressed(SDL_SCANCODE_S))
	{
		if (currentMenuOptionSelected == MAX_MENU_OPTIONS - 1)
			currentMenuOptionSelected = 0;
		else
			currentMenuOptionSelected++;
	}
	else if (input.wasKeyPressed(SDL_SCANCODE_UP) ||
			 input.wasKeyPressed(SDL_SCANCODE_W))
	{
		if (currentMenuOptionSelected == 0)
			currentMenuOptionSelected = MAX_MENU_OPTIONS - 1;
		else
			currentMenuOptionSelected--;
	}
	else if (input.wasKeyPressed(SDL_SCANCODE_RETURN))
	{
		if (currentMenuOptionSelected == 0)
		{
			//setCurrentScene("stage");
			setCurrentScene("difficulty_select");
			return;
		}
		else if (currentMenuOptionSelected == 1)
		{
			game->ended = true;
			return;	
		}
		else if (currentMenuOptionSelected == 2)
		{
			soundEffects ^= 1;
			if (soundEffects == 0)
				SoundEffects::turnVolumeOff();
			else
				SoundEffects::turnVolumeOn();
		}
	}
}

void SceneController::handleStageInputs(KeyboardInput& input)
{
	if (input.closePressed)
	{
		game->ended = true;
		return;
	}
	if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
	{
		this->setCurrentScene("menu");
		return;
	}
	if (input.isKeyHeld(SDL_SCANCODE_D))
	{
		game->player.moveRight(game->arena.getObjects());
	}
	if (input.isKeyHeld(SDL_SCANCODE_A))
	{
		game->player.moveLeft(game->arena.getObjects());
	}
	if (input.isKeyHeld(SDL_SCANCODE_W))
	{
		game->player.moveUp(game->arena.getObjects());
	}
	if (input.isKeyHeld(SDL_SCANCODE_S))
	{
		game->player.moveDown(game->arena.getObjects());
	}
	if (input.wasKeyPressed(SDL_SCANCODE_SPACE))
	{
		game->arena.placeBomb(
			game->player.getObjectX(),
			game->player.getObjectY(),
			Globals::DEFAUT_BOMB_DURATION
		);
	}
	if (!game->player.moved())
	{
		game->player.idle();
	}
}

void SceneController::handleDifficultyMenuInputs(KeyboardInput& input)
{
	if (input.closePressed)
	{
		game->ended = true;
		return;
	}
	if (input.wasKeyPressed(SDL_SCANCODE_DOWN) ||
		input.wasKeyPressed(SDL_SCANCODE_S))
	{
		if (currentDifficultyOptionSelected == MAX_DIFICULTY_OPTIONS - 1)
			currentDifficultyOptionSelected = 0;
		else
			currentDifficultyOptionSelected++;
	}
	else if (input.wasKeyPressed(SDL_SCANCODE_UP) ||
		input.wasKeyPressed(SDL_SCANCODE_W))
	{
		if (currentDifficultyOptionSelected == 0)
			currentDifficultyOptionSelected = MAX_DIFICULTY_OPTIONS - 1;
		else
			currentDifficultyOptionSelected--;
	}
	else if (input.wasKeyPressed(SDL_SCANCODE_RETURN))
	{
		if (currentDifficultyOptionSelected == 0)
		{
			game->setDifficulty(0);
			setCurrentScene("stage");
			return;
		}
		else if (currentDifficultyOptionSelected == 1)
		{
			game->setDifficulty(1);
			setCurrentScene("stage");
			return;
		}
		else if (currentDifficultyOptionSelected == 2)
		{
			game->setDifficulty(2);
			setCurrentScene("stage");
			return;
		}
	}
}



void SceneController::updateCurrentScene()
{
	if (currentScene == "menu")
	{
		updateMenu();
	}
	else if (currentScene == "stage")
	{
		updateStage();
	}
	else if (currentScene == "difficulty_select")
	{
		updateDifficultyMenu();
	}
}

void SceneController::updateStage()
{
	if (game->arena.getEnemies().size() == 0)
	{
		SoundEffects::playEffect("Win");
		SDL_Delay(2000);
		setCurrentScene("menu");
		return;
	}
	if (!game->player.canDraw())
	{
		SoundEffects::playEffect("Lost");
		SDL_Delay(2000);
		setCurrentScene("menu");
		return;
	}
	
	if (game->timeOver())
	{
		SoundEffects::playEffect("TimeOver");
		setCurrentScene("menu");
		return;
	}

	game->player.update(game->arena.getObjects(), game->arena.getEnemies());
	game->arena.update();
}

void SceneController::updateMenu() {}

void SceneController::updateDifficultyMenu() {}


void SceneController::drawCurrentScene()
{
	if (currentScene == "menu")
	{
		drawMenu();
	}
	else if (currentScene == "stage")
	{
		drawStage();
	}
	else if (currentScene == "difficulty_select")
	{
		drawDifficultyMenu();
	}
}

void SceneController::drawMenu()
{
	Graphics::clearRenderer();

	menuBg.draw(
		0,
		0,
		Globals::SCREEN_WIDTH,
		Globals::SCREEN_HEIGHT
	);

	const int LOGO_WIDTH = std::max(Globals::SCREEN_WIDTH - 50, 500);
	const int LOGO_HEIGHT = 200;
	const int LOGO_X = 50;
	const int LOGO_Y = (Globals::SCREEN_WIDTH - LOGO_WIDTH) / 2;

	const SDL_Color WHITE = { 255, 255, 255 };
	const SDL_Color YELLOW = { 255, 255, 0 };

	const int TEXT_WIDTH = 170;
	const int TEXT_HEIGHT = 25;
	const int TEXT_X = 250;
	const int TEXT_Y = 90;
	SDL_Rect textRect = {
		TEXT_Y,
		TEXT_X,
		TEXT_WIDTH,
		TEXT_HEIGHT
	};

	const std::string fontName = "hellovetica";
	const std::string fontPath = "resources/Fonts/hellovetica.ttf";

	SDL_Color color = (currentMenuOptionSelected == 0) ? YELLOW : WHITE;
	Graphics::addText(
		"PLAY GAME",
		fontName,
		fontPath,
		30,
		color,
		&textRect
	);

	color = (currentMenuOptionSelected == 1) ? YELLOW : WHITE;
	textRect.y += 50;
	Graphics::addText(
		"EXIT GAME",
		fontName,
		fontPath,
		30,
		color,
		&textRect
	);


	color = (currentMenuOptionSelected == 2) ? YELLOW : WHITE;
	textRect.y += 50;
	std::string sounds = "SOUNDS ";
	if (soundEffects == 1)
		sounds += "ON";
	else 
		sounds += "OFF";
	Graphics::addText(
		sounds,
		fontName,
		fontPath,
		30,
		color,
		&textRect
	);

	Graphics::drawRenderer();
}

void SceneController::drawStage()
{
	Graphics::clearRenderer();

	game->hud.draw();
	game->arena.drawArena();
	game->player.draw();

	Graphics::drawRenderer();
}

void SceneController::drawDifficultyMenu()
{
	Graphics::clearRenderer();
	Graphics::setRendererDrawColor({ 255, 255, 255 });

	difficultySelectLogo.draw(
		(float)50,
		(float)0,
		(float)Globals::SCREEN_WIDTH - 100,
		(float)Globals::SCREEN_HEIGHT - 100
	);

	const SDL_Color BLACK = { 0, 0, 0 };
	const SDL_Color RED = { 255, 0, 0 };

	const int TEXT_WIDTH = 170;
	const int TEXT_HEIGHT = 25;
	const int TEXT_GAP = 60;
	const int BLOCK_HEIGHT = TEXT_HEIGHT * 3 + TEXT_GAP * 2;

	const int TEXT_X = Globals::SCREEN_WIDTH - TEXT_WIDTH - 20;
	const int TEXT_Y = Globals::SCREEN_HEIGHT - BLOCK_HEIGHT - 20;
	SDL_Rect textRect = {
		TEXT_Y,
		TEXT_X,
		TEXT_WIDTH,
		TEXT_HEIGHT
	};

	const std::string fontName = "hellovetica";
	const std::string fontPath = "resources/Fonts/hellovetica.ttf";

	SDL_Color color;
	color = (currentDifficultyOptionSelected == 0) ? RED : BLACK;
	Graphics::addText(
		"EASY",
		fontName,
		fontPath,
		30,
		color,
		&textRect
	);

	textRect.y += TEXT_GAP;
	color = (currentDifficultyOptionSelected == 1) ? RED : BLACK;
	Graphics::addText(
		"MEDIUM",
		fontName,
		fontPath,
		30,
		color,
		&textRect
	);

	textRect.y += TEXT_GAP;
	color = (currentDifficultyOptionSelected == 2) ? RED : BLACK;
	Graphics::addText(
		"HARD",
		fontName,
		fontPath,
		30,
		color,
		&textRect
	);

	Graphics::drawRenderer();
}


void SceneController::setGame(Game* _game)
{
	game = _game;
}
