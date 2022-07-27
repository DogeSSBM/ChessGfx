#include "./DogeLib/Includes.h"
#include "Chess.h"

int main(int argc, char **argv)
{
    Length window = {.x = 800, .y = 800};
    init();
    setWindowLen(window);

    Board board = bNew();
    bPrint(board);

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
    bInfluences(&board);
    while(1){
        const uint t = frameStart();

        if(
            (keyHeld(SDL_SCANCODE_RCTRL) || keyHeld(SDL_SCANCODE_LCTRL)) &&
            (keyPressed(SDL_SCANCODE_ESCAPE) || keyPressed(SDL_SCANCODE_Q))
        ){
            printf("Game exiting...\n");
            return 0;
        }

        if(keyPressed(SDL_SCANCODE_SPACE)){
            active.color = cInv(active.color);
            printf("%s is now active player.\n", pColorStr[active.color]);
        }

        board.scale = bRescale();
        bDraw(board);

        active.mbpos = aBoardMpos(board.scale);
        if(mouseBtnPressed(MOUSE_L))
            active.downAt = active.mbpos;
        if(mouseBtnReleased(MOUSE_L)){
            active.upAt = active.mbpos;
            if(aValidClick(active))
                active = aClick(board, active);
        }

        if(active.mdst.valid){
            const Piece p = pAt(board, active.msrc.pos);
            board = pSet(board, active.msrc.pos, (const Piece){0});
            board = pSet(board, active.mdst.pos, p);
            active.msrc.valid = false;
            active.mdst.valid = false;
            active.color = cInv(active.color);
            bInfluences(&board);
        }


        aHighlight(board, active);

        frameEnd(t);
    }
    return 0;
}
