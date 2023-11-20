#include "utility/SDL2Wrapper.h"
#include "board/board.h"
#include "utility/FenUtility.h"
#include <iostream>

int main(int argc, char* argv[]) {
    SDL2Wrapper &wrapper = wrapper.GetInstance();

    auto renderer = wrapper.GetRenderer();
    
    // load starting position
    FenUtility::LoadPositionFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    // FenUtility::LoadPositionFromFen("2r4r/ppq1nk2/4b1pp/3pPp2/3P1Q1P/3B3N/P1PK1P2/R6R w - - 8 21");


    // The window is open: enter program loop (see SDL_PollEvent)
    int running = true;
    while (running) {
        running = wrapper.PollInputs();

        wrapper.RenderBackground();
        wrapper.RenderChessBoard();
        wrapper.RenderPieces();

        wrapper.Display();
        wrapper.Delay(10);

    }


   return 0;
}