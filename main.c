#include "Includes.h"
#include "Chess.h"

int main(int argc, char const *argv[])
{
    Length window = {.x = 900, .y = 900};
    init();
    setWindowLen(window);

    Board board = bNew();
    bPrint(board);

    while(1){
        const uint t = frameStart();

        if(keyPressed(SDL_SCANCODE_ESCAPE) || ((keyHeld(SDL_SCANCODE_RCTRL) || keyHeld(SDL_SCANCODE_LCTRL)) && keyPressed(SDL_SCANCODE_Q)))
            return 0;

        board.scale = bRescale();
        bDraw(board);

        frameEnd(t);
    }
    return 0;
}
