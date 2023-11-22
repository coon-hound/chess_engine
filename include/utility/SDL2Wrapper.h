#ifndef SDL2WRAPPER_H
#define SDL2WRAPPER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <cstdint>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define CHESS_BOARD_WIDTH 600

#define BG_COLOR {48, 46, 43, 255}
#define LIGHT_SQUARE_COLOR {233, 215, 180, 255}
#define DARK_SQUARE_COLOR {177, 137, 103, 255}

class SDL2Wrapper{
public:
	static SDL2Wrapper& GetInstance();  // Static method for getting the single instance

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();

	void RenderBackground();
	void RenderChessBoard();
	void RenderPieces();

	void PlaySound();

	int PollInputs();

	void Display();
	void Delay(uint32_t ms);

	SDL2Wrapper(SDL2Wrapper const&) = delete;  // Deleting the copy constructor
	void operator=(SDL2Wrapper const&)  = delete;  // Deleting the assignment operator

private:
	SDL2Wrapper();  // Private constructor
	~SDL2Wrapper();  // Private destructor

	// graphics
	int GetBoardIndiceFromCoordinates (int x, int y);

	SDL_Texture* pieceTextures[32];

	SDL_Window* window;
	SDL_Renderer* renderer;

	int selectedPieceIndice;
	int selectedPiece;

	int mouseX, mouseY;

	// sound
	Mix_Chunk* pieceDown;

	const int frequency = 22050;
    const uint16_t format = AUDIO_S16SYS;
    const int channels = 2;
    const int chunk_size = 4096;

};

#endif  // SDL2WRAPPER_H