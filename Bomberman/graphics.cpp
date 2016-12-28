#include "graphics.h"
#include "Globals.h"

SDL_Window* Graphics::window = nullptr;
SDL_Renderer* Graphics::renderer = nullptr;
Map <std::string, SDL_Surface*> Graphics::images;

void Graphics::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	SDL_CreateWindowAndRenderer
	(
		Globals::SCREEN_WIDTH, 
		Globals::SCREEN_HEIGHT, 
		0, 
		&window, 
		&renderer
	);
	SDL_SetWindowTitle(window, "Bomberman Evolved");
}


void Graphics::destroy()
{
	images.clear();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


SDL_Surface* Graphics::loadImage(const std::string &filepath)
{
	SDL_Surface* loaded = images[filepath];
	if (!loaded)
	{
		loaded = IMG_Load(filepath.c_str());
		if (!loaded)
		{
			printf("There has been an error loading from: %s: %s", filepath, SDL_GetError());
		}
		else
		{
			images[filepath] = loaded;
		}
	}
	return loaded;
}

SDL_Texture* Graphics::loadTexture(const std::string &filepath)
{
	SDL_Surface* image = loadImage(filepath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	return texture;
}

void Graphics::addToRenderer(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
	SDL_RenderCopy(renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::drawRenderer() {
	SDL_RenderPresent(renderer);
}

void Graphics::clearRenderer() {
	SDL_RenderClear(renderer);
}

SDL_Renderer* Graphics::getRenderer() {
	return renderer;
}
