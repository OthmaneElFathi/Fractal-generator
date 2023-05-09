#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
class Window
{
public:
	Window();
	~Window();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update(int n,int x,float size,float xpos,float ypos,float pvx,float pvy);
	void render();
	void clean();
	void shape(int n,int x,float size, float xpos, float ypos, float pvx, float pvy);
	bool running() { return isRunning; };
	int win_width() { return width; };
	int win_height() { return height; }
	void save_texture(const char* filename);
	SDL_Renderer* renderer;
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Texture* texture;
	int height, width;
	
};

