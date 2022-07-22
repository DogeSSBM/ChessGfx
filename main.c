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
    mCoord downAt = {0};
    mCoord upAt = {0};

    ActivePlayer active = {.color = C_WHITE};
    while(1){
        const uint t = frameStart();

        if(
            (keyHeld(SDL_SCANCODE_RCTRL) || keyHeld(SDL_SCANCODE_LCTRL)) &&
            (keyPressed(SDL_SCANCODE_ESCAPE) || keyPressed(SDL_SCANCODE_Q))
        )
            return 0;

        board.scale = bRescale();
        bDraw(board);

        active.mbpos = aBoardMpos(board.scale);
        if(mouseBtnPressed(MOUSE_L)){
            downAt = active.mbpos;
        }

        if(mouseBtnReleased(MOUSE_L)){
            upAt = active.mbpos;
            if(
                downAt.valid && upAt.valid && coordSame(downAt.pos, upAt.pos) &&
                pAt(board, active.mbpos.pos).color == active.color
            ){
                active.msrc = active.mbpos;
            }else{
                active.msrc = (const mCoord){0};
            }
            downAt = (const mCoord){0};
        }

        

        if(active.msrc.valid && active.mdst.valid){
            Turn *t = tNew(active.color);
            // const Move m = {.src = pAt(board, active.msrc.pos), .dst = pAt(board, active.mdst.pos)};
            const Piece srcp = pAt(board, active.msrc.pos);
            const Piece dstp = pAt(board, active.mdst.pos);
            if(dstp.color){
                t->type = M_CAPTURE;
                t->capture.src = active.msrc.pos;
                t->capture.dst = active.mdst.pos;
                t->capture.moved = srcp;
                t->capture.captured = dstp;
            }else{
                t->type = M_MOVE;
                t->move.src = active.msrc.pos;
                t->move.dst = active.mdst.pos;
                t->move.moved = srcp;
            }
            turns = tAppend(turns, t);
            board = pSet(board, active.mdst.pos, pAt(board, active.msrc.pos));
            board = pClear(board, active.msrc.pos);
            active.mbpos.valid = false;
            active.msrc.valid = false;
            active.mdst.valid = false;
            active.color = cInv(active.color);
        }

        frameEnd(t);
    }
    return 0;
}
