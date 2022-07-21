#include "./DogeLib/Includes.h"
#include "Chess.h"

int main(int argc, char **argv)
{
    Length window = {.x = 900, .y = 900};
    init();
    setWindowLen(window);

    Board board = bNew();
    bPrint(board);

    Turn *turns = NULL;

    while(1){
        const uint t = frameStart();

        const lastTurn = tLast(turns);
        const pColor activePlayer = lastTurn ? cInv(lastTurn->color) : C_WHITE;

        if(keyPressed(SDL_SCANCODE_ESCAPE) || ((keyHeld(SDL_SCANCODE_RCTRL) || keyHeld(SDL_SCANCODE_LCTRL)) && keyPressed(SDL_SCANCODE_Q)))
            return 0;

        board.scale = bRescale();
        bDraw(board);

        frameEnd(t);
    }
    return 0;
}
