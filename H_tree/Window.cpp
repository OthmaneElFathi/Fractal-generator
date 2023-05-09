#include "window.h"
#include <math.h>

Window::Window()
{
	isRunning = false;
	height = 0;
	width = 0;
	window = nullptr;
	renderer = nullptr;
}
Window::~Window()
{}
void Window::save_texture(const char *filename)
{
    SDL_Texture *ren_tex;
    SDL_Surface *surf;
    int st;
    int w;
    int h;
    int format;
    void *pixels;

    pixels  = NULL;
    surf    = NULL;
    ren_tex = NULL;
    format  = SDL_PIXELFORMAT_RGBA32;

    /* Get information about texture we want to save */
    st = SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    if (st != 0) {
        SDL_Log("Failed querying texture: %s\n", SDL_GetError());
        goto cleanup;
    }

    ren_tex = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, w, h);
    if (!ren_tex) {
        SDL_Log("Failed creating render texture: %s\n", SDL_GetError());
        goto cleanup;
    }

    /*
     * Initialize our canvas, then copy texture to a target whose pixel data we 
     * can access
     */
    st = SDL_SetRenderTarget(renderer, ren_tex);
    if (st != 0) {
        SDL_Log("Failed setting render target: %s\n", SDL_GetError());
        goto cleanup;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    st = SDL_RenderCopy(renderer, texture, NULL, NULL);
    if (st != 0) {
        SDL_Log("Failed copying texture data: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Create buffer to hold texture data and load it */
    pixels = malloc(w * h * SDL_BYTESPERPIXEL(format));
    if (!pixels) {
        SDL_Log("Failed allocating memory\n");
        goto cleanup;
    }

    st = SDL_RenderReadPixels(renderer, NULL, format, pixels, w * SDL_BYTESPERPIXEL(format));
    if (st != 0) {
        SDL_Log("Failed reading pixel data: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Copy pixel data over to surface */
    surf = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, SDL_BITSPERPIXEL(format), w * SDL_BYTESPERPIXEL(format), format);
    if (!surf) {
        SDL_Log("Failed creating new surface: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Save result to an image */
    st = IMG_SavePNG(surf, filename);
    if (st != 0) {
        SDL_Log("Failed saving image: %s\n", SDL_GetError());
        goto cleanup;
    }
    SDL_Log("Saved texture as PNG to \"%s\"\n", filename);

cleanup:
    SDL_FreeSurface(surf);
    free(pixels);
    SDL_DestroyTexture(ren_tex);
}

void Window::init(const char* title, int xpos, int ypos, int w, int h, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		width = 1920;
		height = 1200;
		flags = SDL_WINDOW_FULLSCREEN;
	}
	else
	{
		width = w;
		height = h;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initislised" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			std::cout << "Window created" << std::endl;
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0,0, 0, 255);
			std::cout << "Renderer created" << std::endl;
		}
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
		if (texture)
		{
			SDL_SetRenderTarget(renderer, texture);
			std::cout << "texture created" << std::endl;
		}
		isRunning = true;
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
}
void Window::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

}
void Window::shape(int n, int x, float size, float xpos, float ypos, float pvx, float pvy) {
	float AX, BX, CX, DX, EX, FX, AY, BY, CY, DY, EY, FY;
	switch (x)
	{
	case 1:
		// lines 
		size = size / 2;
		AX = xpos - size;
		BX = xpos + size;
		AY = ypos - size;
		BY = ypos + size;
		SDL_RenderDrawLine(renderer, BX, ypos, AX, ypos);
		SDL_RenderDrawLine(renderer, BX, BY, BX, AY);
		SDL_RenderDrawLine(renderer, AX, BY, AX, AY);
		this->update(n - 1, x, size, BX, BY, xpos, ypos);
		this->update(n - 1, x, size, BX, AY, xpos, ypos);
		this->update(n - 1, x, size, AX, BY, xpos, ypos);
		this->update(n - 1, x, size, AX, AY, xpos, ypos);
		break;
	case 2:

		size = size / 2;
		AX = xpos - size;
		BX = xpos + size;
		AY = ypos - size;
		BY = ypos + size;
		SDL_RenderDrawLine(renderer, BX, BY, BX, AY);
		SDL_RenderDrawLine(renderer, BX, BY, AX, BY);
		SDL_RenderDrawLine(renderer, AX, AY, BX, AY);
		SDL_RenderDrawLine(renderer, AX, AY, AX, BY);
		this->update(n - 1, x, size, BX, BY, xpos, ypos);
		this->update(n - 1, x, size, BX, AY, xpos, ypos);
		this->update(n - 1, x, size, AX, BY, xpos, ypos);
		this->update(n - 1, x, size, AX, AY, xpos, ypos);
		break;
	case 3:
		size = size / 2;
		AX = xpos - size;
		BX = xpos + size;
		AY = ypos - size;
		BY = ypos + size;
		SDL_RenderDrawLine(renderer, BX, BY, BX, AY);
		SDL_RenderDrawLine(renderer, BX, BY, AX, BY);
		SDL_RenderDrawLine(renderer, AX, AY, BX, AY);
		SDL_RenderDrawLine(renderer, AX, AY, AX, BY);
		this->update(n - 1, x, size, xpos + 1.5 * size, ypos + 1.5 * size, BX, BY);
		this->update(n - 1, x, size, xpos + 1.5 * size, ypos - 1.5 * size, BX, AY);
		this->update(n - 1, x, size, xpos - 1.5 * size, ypos + 1.5 * size, AX, BY);
		this->update(n - 1, x, size, xpos - 1.5 * size, ypos - 1.5 * size, AX, AY);
		break;
	case 4:
		size = size / 2;
		AX = xpos - size;
		BX = xpos + size;
		AY = ypos - size;
		BY = ypos + size;
		SDL_RenderDrawLine(renderer, BX, BY, BX, AY);
		SDL_RenderDrawLine(renderer, BX, BY, AX, BY);
		SDL_RenderDrawLine(renderer, AX, AY, BX, AY);
		SDL_RenderDrawLine(renderer, AX, AY, AX, BY);
		if (BX != pvx || BY != pvy)
			this->update(n - 1, x, size, xpos + 1.5 * size, ypos + 1.5 * size, BX, BY);
		if (BX != pvx || AY != pvy)
			this->update(n - 1, x, size, xpos + 1.5 * size, ypos - 1.5 * size, BX, AY);
		if (AX != pvx || BY != pvy)
			this->update(n - 1, x, size, xpos - 1.5 * size, ypos + 1.5 * size, AX, BY);
		if (AX != pvx || AY != pvy)
			this->update(n - 1, x, size, xpos - 1.5 * size, ypos - 1.5 * size, AX, AY);
		break;
	case 5:
		size = size / 2;
		AX = xpos; 
		AY = ypos - sqrt(3) / 3 * size;
		BX = xpos - size / 2;
		BY = ypos + sqrt(3) / 6 * size;
		CX = xpos + size / 2;
		CY = ypos + sqrt(3) / 6 * size;
		SDL_RenderDrawLine(renderer, AX, AY, BX, BY);
		SDL_RenderDrawLine(renderer, AX, AY, CX, CY);
		SDL_RenderDrawLine(renderer, CX, CY, BX, BY);
		this->update(n - 1, x, size, AX, AY, xpos, ypos);
		this->update(n - 1, x, size, BX, BY, xpos, ypos);
		this->update(n - 1, x, size, CX, CY, xpos, ypos);
		break;
	case 6:
		size = size / 2;
		AX = xpos;
		AY = ypos - sqrt(3) / 3 * size;
		BX = xpos - size / 2;
		BY = ypos + sqrt(3) / 6 * size;
		CX = xpos + size / 2;
		CY = ypos + sqrt(3) / 6 * size;
		SDL_RenderDrawLine(renderer, xpos, ypos, BX, BY);
		SDL_RenderDrawLine(renderer, xpos, ypos, CX, CY);
		SDL_RenderDrawLine(renderer, xpos, ypos, AX, AY);
		this->update(n - 1, x, size, AX, AY, xpos, ypos);
		this->update(n - 1, x, size, BX, BY, xpos, ypos);
		this->update(n - 1, x, size, CX, CY, xpos, ypos);
		break;
	case 7:
		size = size / 2;
		AX = xpos;
		AY = ypos - sqrt(3) / 3 * size;
		BX = xpos - size / 2;
		BY = ypos + sqrt(3) / 6 * size;
		CX = xpos + size / 2;
		CY = ypos + sqrt(3) / 6 * size;
		FX = xpos;
		FY = ypos + sqrt(3) / 3 * size;
		DX = BX;
		DY = ypos - sqrt(3) / 6 * size;
		EX = CX;
		EY= ypos - sqrt(3) / 6 * size;
		SDL_RenderDrawLine(renderer, xpos, ypos, BX, BY);
		SDL_RenderDrawLine(renderer, xpos, ypos, CX, CY);
		SDL_RenderDrawLine(renderer, xpos, ypos, AX, AY);
		SDL_RenderDrawLine(renderer, xpos, ypos, FX, FY);
		SDL_RenderDrawLine(renderer, xpos, ypos, DX, DY);
		SDL_RenderDrawLine(renderer, xpos, ypos, EX, EY);
		this->update(n - 1, x, size, AX, AY, xpos, ypos);
		this->update(n - 1, x, size, BX, BY, xpos, ypos);
		this->update(n - 1, x, size, CX, CY, xpos, ypos);
		this->update(n - 1, x, size, DX, DY, xpos, ypos);
		this->update(n - 1, x, size, EX, EY, xpos, ypos);
		this->update(n - 1, x, size, FX, FY, xpos, ypos);
		break;
	case 8:
		size = size / 2;
		AX = xpos;
		AY = ypos - sqrt(3) / 3 * size;
		BX = xpos - size / 2;
		BY = ypos + sqrt(3) / 6 * size;
		CX = xpos + size / 2;
		CY = ypos + sqrt(3) / 6 * size;
		FX = xpos;
		FY = ypos + sqrt(3) / 3 * size;
		DX = BX;
		DY = ypos - sqrt(3) / 6 * size;
		EX = CX;
		EY = ypos - sqrt(3) / 6 * size;
		SDL_RenderDrawLine(renderer, AX,AY, DX, DY);
		SDL_RenderDrawLine(renderer, FX, FY, CX, CY);
		SDL_RenderDrawLine(renderer, FX, FY, BX, BY);
		SDL_RenderDrawLine(renderer, CX, CY, EX, EY);
		SDL_RenderDrawLine(renderer, BX, BY, DX, DY);
		SDL_RenderDrawLine(renderer, AX, AY, EX, EY);
		this->update(n - 1, x, size, AX, AY, xpos, ypos);
		this->update(n - 1, x, size, BX, BY, xpos, ypos);
		this->update(n - 1, x, size, CX, CY, xpos, ypos);
		this->update(n - 1, x, size, DX, DY, xpos, ypos);
		this->update(n - 1, x, size, EX, EY, xpos, ypos);
		this->update(n - 1, x, size, FX, FY, xpos, ypos);
		break;
	default:
		break;
	}
}
void Window::update(int n,int x,float size,float xpos,float ypos, float pvx=0, float pvy=0)
{
	if (n>0 && xpos>0 && ypos>0 && xpos<width && ypos<height)
	{	
		this->shape(n,x, size, xpos, ypos,pvx,pvy);	
	}

}
void Window::render()
{
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
void Window::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Window cleaned" << std::endl;
}

