#include "utility/SDL2Wrapper.h"

#include <SDL.h>
#include <iostream>
#include <assert.h>

#include "board/piece.h"
#include "board/board.h"

int SDL2Wrapper::GetBoardIndiceFromCoordinates (int x, int y) {
    int startX = (WINDOW_WIDTH - CHESS_BOARD_WIDTH) / 2;
    int startY = (WINDOW_HEIGHT - CHESS_BOARD_WIDTH) / 2;
	int cellSize = CHESS_BOARD_WIDTH / 8;

    x -= startX;
    x /= cellSize; 
    // x -= (x % cellSize);

    y -= startY;
    y /= cellSize;
    // y -= (y % cellSize);

    if (x < 0 || y < 0 || x > 7 || y > 7) {
        return -1;
    }

    int ret = y * 8 + x;

    assert(ret >= 0 && ret <= 63);

    return ret;
} 

SDL2Wrapper& SDL2Wrapper::GetInstance() {
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

    IMG_Init(IMG_INIT_PNG);

    //pieces texture (white pieces)
    pieceTextures[Piece::White | Piece::King] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_klt60.png")); 
    pieceTextures[Piece::White | Piece::Pawn] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_plt60.png")); 
    pieceTextures[Piece::White | Piece::Knight] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_nlt60.png")); 
    pieceTextures[Piece::White | Piece::Bishop] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_blt60.png")); 
    pieceTextures[Piece::White | Piece::Rook] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_rlt60.png")); 
    pieceTextures[Piece::White | Piece::Queen] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_qlt60.png")); 
    
    pieceTextures[Piece::Black | Piece::King] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_kdt60.png")); 
    pieceTextures[Piece::Black | Piece::Pawn] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_pdt60.png")); 
    pieceTextures[Piece::Black | Piece::Knight] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_ndt60.png")); 
    pieceTextures[Piece::Black | Piece::Bishop] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_bdt60.png")); 
    pieceTextures[Piece::Black | Piece::Rook] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_rdt60.png")); 
    pieceTextures[Piece::Black | Piece::Queen] = SDL_CreateTextureFromSurface(renderer, IMG_Load("resources/Chess_qdt60.png")); 

    selectedPieceIndice = -1;
    selectedPiece = -1;
}

SDL2Wrapper::~SDL2Wrapper() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

    // free textures
    // for (int i = 0; i < 

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

void SDL2Wrapper::RenderPieces() {
	Board &board = board.GetInstance();
	int* square = board.GetSquare();

	int cellSize = CHESS_BOARD_WIDTH / 8;

    int startX = (WINDOW_WIDTH - CHESS_BOARD_WIDTH) / 2;
    int startY = (WINDOW_HEIGHT - CHESS_BOARD_WIDTH) / 2;    

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            SDL_Texture* currPieceTexture;
            int currBoardIndice = i * 8 + j;

            if (currBoardIndice == selectedPieceIndice && selectedPieceIndice != -1) {
                printf("curr board indice = %d, selected piece indice = %d, selected piece = %d\n", currBoardIndice, selectedPieceIndice, selectedPiece);

                currPieceTexture = pieceTextures[selectedPiece];                

                SDL_Rect rect;

                rect.x = mouseX - (cellSize / 2);
                rect.y = mouseY - (cellSize / 2);
                rect.w = cellSize;
                rect.h = cellSize;

                SDL_RenderCopy(renderer, currPieceTexture, NULL, &rect);

                continue;
            }

            switch (square[currBoardIndice]) { 
                case Piece::White | Piece::King:
                    currPieceTexture = pieceTextures[Piece::White | Piece::King];
                    break;
                
                case Piece::White | Piece::Pawn:
                    currPieceTexture = pieceTextures[Piece::White | Piece::Pawn];
                    break;

                case Piece::White | Piece::Knight:
                    currPieceTexture = pieceTextures[Piece::White | Piece::Knight];
                    break;

                case Piece::White | Piece::Bishop:
                    currPieceTexture = pieceTextures[Piece::White | Piece::Bishop];
                    break;

                case Piece::White | Piece::Rook:
                    currPieceTexture = pieceTextures[Piece::White | Piece::Rook];
                    break;

                case Piece::White | Piece::Queen:
                    currPieceTexture = pieceTextures[Piece::White | Piece::Queen];
                    break;

                case Piece::Black | Piece::King:
                    currPieceTexture = pieceTextures[Piece::Black | Piece::King];
                    break;
                
                case Piece::Black | Piece::Pawn:
                    currPieceTexture = pieceTextures[Piece::Black | Piece::Pawn];
                    break;

                case Piece::Black | Piece::Knight:
                    currPieceTexture = pieceTextures[Piece::Black | Piece::Knight];
                    break;

                case Piece::Black | Piece::Bishop:
                    currPieceTexture = pieceTextures[Piece::Black | Piece::Bishop];
                    break;

                case Piece::Black | Piece::Rook:
                    currPieceTexture = pieceTextures[Piece::Black | Piece::Rook];
                    break;

                case Piece::Black | Piece::Queen:
                    currPieceTexture = pieceTextures[Piece::Black | Piece::Queen];
                    break;
                default:
                    continue;
            }
            
            
            SDL_Rect rect;

            rect.x = startX + j * cellSize;
            rect.y = startY + i * cellSize;
            rect.w = cellSize;
            rect.h = cellSize;

            SDL_RenderCopy(renderer, currPieceTexture, NULL, &rect);
        }
    }
}

int SDL2Wrapper::PollInputs() {
	Board &board = board.GetInstance();
	int* square = board.GetSquare();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Check for the quit eventj
        SDL_GetMouseState(&mouseX, &mouseY);
        int currBoardIndice = GetBoardIndiceFromCoordinates(mouseX, mouseY);

        switch (event.type) {
            case SDL_QUIT:
                return false;
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button != SDL_BUTTON_LEFT)
                    break;

                if (currBoardIndice == -1) {
                    break;
                }

                selectedPieceIndice = currBoardIndice;
                selectedPiece = square[currBoardIndice];
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button != SDL_BUTTON_LEFT)
                    break;

                if (currBoardIndice == -1) {
                    break;
                }
                board.Move(selectedPieceIndice, currBoardIndice);
                selectedPieceIndice = -1;
                selectedPiece = -1;
                break;


        };
        printf("predicted coord = %d\n", GetBoardIndiceFromCoordinates(mouseX, mouseY));

    }

    return 1; 
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
