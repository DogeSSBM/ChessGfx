#include "./DogeLib/Includes.h"
#include "Chess.h"

int main(int argc, char **argv)
{
    Length window = {.x = 800, .y = 800};
    init();
    setWindowLen(window);

    ActivePlayer active = {.color = C_WHITE};
    Turn *turns = NULL;
    while(1){
        const uint t = frameStart();

        if(
            (keyHeld(SDL_SCANCODE_RCTRL) || keyHeld(SDL_SCANCODE_LCTRL)) &&
            (keyPressed(SDL_SCANCODE_ESCAPE) || keyPressed(SDL_SCANCODE_Q))
        ){
            printf("Game exiting...\n");
            return 0;
        }

        Board board;
        tConstructBoard(&board, turns);
        bDraw(board);
        active = aUpdateMouse(active, board);

        if(active.mdst.valid){
            Turn *t = tNew(active.color);
            t->color = active.color;

            const Coord srcpos = active.msrc.pos;
            const Coord dstpos = active.mdst.pos;
            const Piece srcpiece = pAt(board, active.msrc.pos);
            const Piece dstpiece = pAt(board, active.mdst.pos);

            if(dstpiece.color == cInv(active.color)){
                t->type = M_CAPTURE;
                t->capture.src = srcpos;
                t->capture.dst = dstpos;
                t->capture.moved = srcpiece;
                t->capture.captured = dstpiece;
            }else{
                t->type = M_MOVE;
                t->move.src = srcpos;
                t->move.dst = dstpos;
                t->move.moved = srcpiece;
            }

            turns = tAppend(turns, t);
            active.msrc.valid = false;
            active.mdst.valid = false;
            active.color = cInv(active.color);
        }

        aHighlight(board, active);

        frameEnd(t);
    }
    return 0;
}
