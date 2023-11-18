#include "utility/SDL2Wrapper.h"
#include <SDL.h>
#include <iostream>

SDL2Wrapper& SDL2Wrapper::getInstance() {
	static SDL2Wrapper instance;  // Guaranteed to be destroyed and instantiated on first use
	return instance;
}

SDL2Wrapper::SDL2Wrapper() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(1);
    }

    window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_OPENGL);

    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
		exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
		exit(1);
    }

}

SDL2Wrapper::~SDL2Wrapper() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void SDL2Wrapper::RenderBackground() {
    SDL_Color bgColor = BG_COLOR;
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 255);  // Black color
    SDL_RenderClear(renderer);
}

void SDL2Wrapper::RenderChessBoard() {
    SDL_Color lightSquareColor = LIGHT_SQUARE_COLOR;
    SDL_Color darkSquareColor = DARK_SQUARE_COLOR;
	int cellSize = CHESS_BOARD_WIDTH / 8;
	SDL_Rect rect;
    rect.w = cellSize;
    rect.h = cellSize;

    // calculate the starting x and y coordinates to center the board
    int startX = (WINDOW_WIDTH - CHESS_BOARD_WIDTH) / 2;
    int startY = (WINDOW_HEIGHT - CHESS_BOARD_WIDTH) / 2;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            rect.x = startX + j * cellSize;
            rect.y = startY + i * cellSize;

            // alternate between white and black cells
            if ((i + j) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, lightSquareColor.r, lightSquareColor.g, lightSquareColor.b, lightSquareColor.a); // white
            } else {
                SDL_SetRenderDrawColor(renderer, darkSquareColor.r, darkSquareColor.g, darkSquareColor.b, darkSquareColor.a); // black
            }

            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void SDL2Wrapper::Display() {
	SDL_RenderPresent(renderer);
}

void SDL2Wrapper::Delay(uint32_t ms) {
    SDL_Delay(ms);
}

SDL_Renderer* SDL2Wrapper::GetRenderer() {
	return renderer;
}

SDL_Window* SDL2Wrapper::GetWindow() {
	return window;
}
