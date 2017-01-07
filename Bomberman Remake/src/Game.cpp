#include "Game.h"
#include "SceneController.h"

#define blockW Globals::BLOCK_WIDTH
#define blockH Globals::BLOCK_HEIGHT


Game::Game()
{
	srand(time(0));
	Graphics::init();

	arena.init();
	arena.generateRandomArena();
	arena.addEnemies(7);

	this->setupPlayer();

	hud.setArena(&this->arena);
	hud.setPlayer(&this->player);
	hud.init();

	SoundEffects::init();

	scenes = new SceneController;
	scenes->setGame(this);
	scenes->prepareScenes();
	scenes->setCurrentScene("menu");

	this->ended = false;
	this->gameLoop();
}

Game::~Game() {}


void Game::endGame()
{
	Graphics::destroy();
	SoundEffects::destroy();
	arena.clear();
}

void Game::resetGame()
{
	arena.clear();
	arena.generateRandomArena();
	arena.addEnemies(7);

	this->setupPlayer();

	hud.setArena(&this->arena);
	hud.setPlayer(&this->player);
	this->ended = false;

	hud.resetTimer();
}

void Game::gameLoop()
{
	KeyboardInput input;
	
	while (!ended)
	{
		const int FRAME_START = SDL_GetTicks();
		input.newFrame();
		input.processInputs();

		scenes->handleInputs(input);
		scenes->updateCurrentScene();
		scenes->drawCurrentScene();

		cap_FPS(FRAME_START);
	}
	endGame();
}

void Game::setupPlayer()
{
	player.init();
	player.setSpeed(PLAYER_SPEED);
	player.setBox({ 30, 30, 17, 22 });
	player.setDeathAnimationTime(500);
	player.setLives(3);

	player.setSprite("Resources/Images/second.png", { 125, 2, 15, 22 }, 170);
	player.getSprite().addAnimationFrame("default", 125, 2, 15, 22);
	player.getSprite().setAnimation("default");

	player.getSprite().addAnimationFrame("idle_up", 15, 2, 15, 22);
	player.getSprite().addAnimationFrame("idle_right", 69, 2, 15, 22);
	player.getSprite().addAnimationFrame("idle_down", 125, 2, 15, 22);
	player.getSprite().addAnimationFrame("idle_left", 179, 2, 17, 22);

	player.getSprite().addAnimationFrame("walk_up", 32, 2, 15, 22);
	player.getSprite().addAnimationFrame("walk_up", 49, 2, 15, 22);

	player.getSprite().addAnimationFrame("walk_right", 87, 2, 15, 22);
	player.getSprite().addAnimationFrame("walk_right", 105, 2, 15, 22);

	player.getSprite().addAnimationFrame("walk_down", 142, 2, 15, 22);
	player.getSprite().addAnimationFrame("walk_down", 159, 2, 15, 22);

	player.getSprite().addAnimationFrame("walk_left", 179, 2, 17, 22);
	player.getSprite().addAnimationFrame("walk_left", 198, 2, 17, 22);

	player.getSprite().addAnimationFrame("die_1", 152, 176, 17, 23);
	player.getSprite().addAnimationFrame("die_2", 171, 175, 19, 24);
	player.getSprite().addAnimationFrame("die_3", 192, 174, 23, 25);
	player.getSprite().addAnimationFrame("die_4", 217, 174, 28, 25);
	player.setDeathFrames(4);
}

void Game::cap_FPS(const int FRAME_START)
{
	const int FRAME_END = SDL_GetTicks();
	const int ELAPSED = FRAME_END - FRAME_START;
	if (ELAPSED < MAX_FRAME_TIME)
		SDL_Delay(MAX_FRAME_TIME - ELAPSED);
}

bool Game::timeOver()
{
	const int CURRENT_TIME_S = SDL_GetTicks() / 1000;
	const int DIFF_TIME_S = CURRENT_TIME_S - hud.getStartTime() / 1000;
	return (DIFF_TIME_S >= GAME_MAX_TIME_S);
}