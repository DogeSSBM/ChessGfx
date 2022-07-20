#include "Includes.h"
#include "Chess.h"

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

Piece pAt(const Board board, const Coord pos)
{
    if(coordMin(pos) < 0 || coordMax(pos) > 7)
        panic("Cannot get piece at coord {%i,%i}\n", pos.x, pos.y);
    return board.arr[pos.x][pos.y];
}

void bDraw(const Board board)
{
    setColor(GREY3);
    fillSquareCoord(iC(0,0), board.scale)
    for(uint y = 0; y < 8; y++){
        for(uint x = 0; x < 8; x++){
            const Coord bpos = iC(x,y);
            const Piece p = pAt(board, bpos);
            if(p.type != T_EMPTY){

            }
        }
    }
}

int main(int argc, char const *argv[])
{
    Length window = {.x = 800, .y = 600};
    init();
    setWindowLen(window);

    Board board = bNew();

    while(1){
        const uint t = frameStart();

        if((keyHeld(SDL_SCANCODE_RCTRL) || keyHeld(SDL_SCANCODE_LCTRL)) && keyPressed(SDL_SCANCODE_Q))
            return 0;

        frameEnd(t);
    }
    return 0;
}
