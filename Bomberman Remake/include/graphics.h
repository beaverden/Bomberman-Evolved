#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#undef main
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Map.h"
#include "Vector.h"


class Graphics
{
public:

	/**
	*	Initializes the graphics library
	*	Sets up the window and the image library
	*/
	static void init();


	/**
	*	Frees up all the memory and destroys the window 
	*	Also destroys the renderer
	*/
	static void destroy();

	static void setRendererDrawColor(SDL_Color color);

	/**
	*	Adds a texture to the renderer
	*	@param source texture to be added
	*	@param sourceRectangle to crop from source texture
	*	@param destinationRectangle of the window to be printed on
	*/
	static void addToRenderer(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/**
	*	Draws all the content pushed into the renderer to the screen
	*/
	static void drawRenderer();

	/**
	*	Removes all the content from the renderer
	*/
	static void clearRenderer();

	static SDL_Renderer* getRenderer();

	/**
	*	Loads a image from the specified path
	*	If loaded for the first time, it will be saved
	*	If loaded again, it will be pulled out of the images map
	*	@param filepath on the machine (relative to project .exe)
	*/
	static SDL_Surface* loadImage(const std::string &filepath);

	/**
	*	Transforms a loaded image (surface) into a texture
	*	Loads the image with the @function [loadImage]
	*	@param filepath on the machine (relative to project .exe)
	*/
	static SDL_Texture* loadTexture(const std::string &filepath);


	static TTF_Font* loadFont(
		const std::string& fontName, 
		const std::string& fontPath, 
		const int fontSize);

	static void Graphics::addText(const std::string& text,
		const std::string& fontName,
		const std::string& fontPath,
		const int fontSize,
		SDL_Color color,
		SDL_Rect* destinationRect);


private:
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static Map <std::string, SDL_Surface*> images;
	static Map <std::string, TTF_Font*> fonts;


};

#endif /* GRAPHICS_H */