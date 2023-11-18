#ifndef SDL2WRAPPER_H
#define SDL2WRAPPER_H

#include <SDL.h>
#include <SDL_image.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define CHESS_BOARD_WIDTH 600

#define BG_COLOR {48, 46, 43, 255}
#define LIGHT_SQUARE_COLOR {233, 215, 180, 255}
#define DARK_SQUARE_COLOR {177, 137, 103, 255}

class SDL2Wrapper{
public:
	static SDL2Wrapper& getInstance();  // Static method for getting the single instance

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();

	void RenderBackground();
	void RenderChessBoard();

	void Display();
	void Delay(uint32_t ms);

	SDL2Wrapper(SDL2Wrapper const&) = delete;  // Deleting the copy constructor
	void operator=(SDL2Wrapper const&)  = delete;  // Deleting the assignment operator

private:
	SDL2Wrapper();  // Private constructor
	~SDL2Wrapper();  // Private destructor

	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif  // SDL2WRAPPER_H