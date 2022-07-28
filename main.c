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
            Turn *t = tNew(
                pAt(board, active.msrc.pos),
                pAt(board, active.mdst.pos),
                active.msrc.pos,
                active.mdst.pos
            );

            Board after;
            memcpy(&after, &board, sizeof(Board));
            applyTurn(&after, t);
            bInfluences(&after);
            if(bCheck(after, active.color)){
                free(t);
            }else{
                turns = tAppend(turns, t);
                active.color = cInv(active.color);
            }
            active.msrc.valid = false;
            active.mdst.valid = false;
        }

        aHighlight(board, active);

        frameEnd(t);
    }
    return 0;
}
