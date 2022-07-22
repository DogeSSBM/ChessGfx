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

        const Turn *lastTurn = tLast(turns);
        const pColor activePlayer = lastTurn ? cInv(lastTurn->color) : C_WHITE;
        board.scale = bRescale();
        bDraw(board);

        const Coord mbPos = coordDiv(mouse.pos, board.scale);
        if(bCoordValid(mbPos) && pAt(board, mbPos).color == activePlayer){
            setColor(activePlayer == C_WHITE ? BLACK : WHITE);
            fillBorderCoordSquare(coordMul(mbPos, board.scale), board.scale, -8);
            setColor(activePlayer == C_WHITE ? WHITE : BLACK);
            fillBorderCoordSquare(coordOffset(coordMul(mbPos, board.scale), (const Coord){2,2}), board.scale-4, -4);
        }


        if(
            (keyHeld(SDL_SCANCODE_RCTRL) || keyHeld(SDL_SCANCODE_LCTRL)) &&
            (keyPressed(SDL_SCANCODE_ESCAPE) || keyPressed(SDL_SCANCODE_Q))
        )
            return 0;

        frameEnd(t);
    }
    return 0;
}
