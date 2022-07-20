#include "Includes.h"

typedef enum{T_EMPTY, T_KING, T_QUEEN, T_KNIGHT, T_BISHOP, T_ROOK, T_PAWN}pType;
typedef enum{C_EMPTY, C_WHITE, C_BLACK}pColor;

typedef struct{
    pColor color;
    pType type;
}Piece;

typedef struct{
    uint scale;
    Piece arr[8][8];
}Board;

uint bRescale(void)
{
    return coordMin(getWindowLen()) / 8;
}

Board bNew(void)
{
    Board ret = {
        .scale = bRescale(),
        .arr = {0}
    };
    const pType home[8] = {T_ROOK, T_KNIGHT, T_BISHOP, T_QUEEN, T_KING, T_BISHOP, T_KNIGHT, T_ROOK};

    for(uint i = 0; i < 8; i++){
        ret.arr[i][0] = (const Piece){.color = C_BLACK, .type = home[i]};
        ret.arr[i][7] = (const Piece){.color = C_WHITE, .type = home[i]};
        ret.arr[i][1] = (const Piece){.color = C_BLACK, .type = T_PAWN};
        ret.arr[i][6] = (const Piece){.color = C_WHITE, .type = T_PAWN};
    }

    return ret;
}

int main(int argc, char const *argv[])
{
    Length window = {.x = 800, .y = 600};
    init();
    setWindowLen(window);

    Board board = bNew();

    while(1){
       const uint t = frameStart();

        if(mouseBtnState(MOUSE_L)){
            drawTextCenteredCoord("Left clicked", mouse.pos);
        }

        for(Direction i = DIR_U; i <= DIR_L; i++)
            pos = coordShift(pos, i, 8*keyState(dirKey[i]));

        fillCircleCoord(pos, 32);

        frameEnd(t);
    }
    return 0;
}
