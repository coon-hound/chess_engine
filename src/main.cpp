#include "utility/SDL2Wrapper.h"
#include <iostream>

int main(int argc, char* argv[]) {
   SDL2Wrapper &wrapper = wrapper.getInstance();

    auto renderer = wrapper.GetRenderer();
   

    SDL_Rect square;
    square.x = 320 - 50;  // 50 is half the width of the square
    square.y = 240 - 50;  // 50 is half the height of the square
    square.w = 100;  // width of the square
    square.h = 100;  // height of the square

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

        wrapper.Display();
        wrapper.Delay(100);

    }


   return 0;
}