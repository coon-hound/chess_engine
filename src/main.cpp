#include "utility/SDL2Wrapper.h"
#include "board/board.h"
#include "utility/FenUtility.h"
#include <iostream>

int main(int argc, char* argv[]) {
    SDL2Wrapper &wrapper = wrapper.getInstance();

    auto renderer = wrapper.GetRenderer();
   
    FenUtility::LoadPositionFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

    // The window is open: enter program loop (see SDL_PollEvent)
    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Check for the quit event
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        wrapper.RenderBackground();
        wrapper.RenderChessBoard();
        wrapper.RenderPieces();

        wrapper.Display();
        wrapper.Delay(100);

    }


   return 0;
}