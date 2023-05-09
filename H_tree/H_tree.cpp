#include <iostream>
#include "SDL.h"
#include "window.h"



int main(int argc,char *argv[])
{
	Window* window = nullptr;
	int n, x,width = 1000, height = 1000;
	float size = 500;
	std::cin >> x;
	std::cin >> n;
	window = new Window();
	window->init("H-tree", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false);
	window->update(n,x, size, window->win_width() / 2.0, window->win_height() / 2.0, window->win_width() / 2.0, window->win_height() / 2.0);
	window->render();
	window->save_texture("image2.png");
	while(window->running())
	window->handleEvents();
	window->clean();
    return 0;
}

