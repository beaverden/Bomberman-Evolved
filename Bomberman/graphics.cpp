#include "graphics.h"
#include "Globals.h"

SDL_Window* Graphics::window = nullptr;
SDL_Renderer* Graphics::renderer = nullptr;
Map <std::string, SDL_Surface*> Graphics::images;
Map <std::string, TTF_Font*> Graphics::fonts;

void Graphics::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();

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

void Graphics::setRendererDrawColor(SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
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

void Graphics::addText( const std::string& text,
						const std::string& fontName,
						const std::string& fontPath,
						const int fontSize,
						SDL_Color color,
						SDL_Rect* destinationRect)
{
	TTF_Font* font = loadFont(fontName, fontPath, fontSize);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
	
	addToRenderer(texture, NULL, destinationRect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

TTF_Font* Graphics::loadFont(const std::string& fontName, const std::string& fontPath, const int fontSize)
{
	TTF_Font* font = fonts[fontName];
	if (!font)
	{
		font = TTF_OpenFont(fontPath.c_str(), fontSize);
		if (!font)
		{
			printf("Error loading %s font: %s", fontPath, SDL_GetError());
		}
		else
		{
			fonts[fontName] = font;
		}
	}
	return font;
}