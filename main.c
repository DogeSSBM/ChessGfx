#include "./DogeLib/Includes.h"
#include "Chess.h"

int main(int argc, char **argv)
{
    Length window = {.x = 800, .y = 800};
    init();
    setWindowLen(window);

    Board board = bNew();
    bPrint(board);

    Turn *turns = NULL;

    int a = 0;
    int b = aInv(a);
    for(int i = 0; i < 16; i++){
        printf("%s\t%s\n", AngStr[a], AngStr[b]);
        a = aRoi(a, 3);
        b = aRoi(b, -3);
    }

    board.arr[0][6] = (const Piece){0};
    board.arr[1][6] = (const Piece){0};
    board.arr[2][6] = (const Piece){0};
    board.arr[3][6] = (const Piece){0};
    board.arr[4][6] = (const Piece){0};
    board.arr[6][6] = (const Piece){0};
    board.arr[7][6] = (const Piece){0};

    board.arr[3][7] = (const Piece){0};
    board.arr[3][4] = (const Piece){.color = C_WHITE, .type = T_QUEEN};

    board.arr[0][7] = (const Piece){0};
    board.arr[0][5] = (const Piece){.color = C_WHITE, .type = T_ROOK};

    board.arr[6][2] = (const Piece){.color = C_WHITE, .type = T_PAWN};
    board.arr[7][4] = (const Piece){.color = C_WHITE, .type = T_PAWN};

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
        if(mouseBtnChanged(MOUSE_L))
            active = aMbtn(board, active);

        aHighlight(board, active);

        if(active.msrc.valid && active.mdst.valid){
            Turn *t = tNew(active.color);
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
