#include "Includes.h"
#include "Chess.h"

typedef enum{T_EMPTY, T_KING, T_QUEEN, T_KNIGHT, T_BISHOP, T_ROOK, T_PAWN}pType;
typedef enum{C_EMPTY, C_WHITE, C_BLACK}pColor;

typedef struct{
    pColor color;
    pType type;
}Piece;

typedef struct{
    Color whiteSquare;
    Color blackSquare;
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
        .whiteSquare = (const Color){.r=0xb9, .g=0xb9, .b=0xb9, .a=0xff},
        .blackSquare = (const Color){.r=0x3b, .g=0x3b, .b=0x3b, .a=0xff},
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

const char* pUtf(const Piece p)
{
    static const char b[8][8] = {" ", "♕", "♔", "♘", "♗", "♖", "♙"};
    static const char w[8][8] = {" ", "♛", "♚", "♝", "♞", "♜", "♟"};

    if(p.color == C_BLACK)
        return b[p.type];
    return w[p.type];
}

Piece pAt(const Board board, const Coord pos)
{
    if(coordMin(pos) < 0 || coordMax(pos) > 7)
        panic("Cannot get piece at coord {%i,%i}\n", pos.x, pos.y);
    return board.arr[pos.x][pos.y];
}

// void bDraw(const Board board)
// {
//     setColor(board.whiteSquare);
//     fillSquareCoord(iC(0,0), board.scale*8);
//     for(uint y = 0; y < 8; y++){
//         for(uint x = 0; x < 8; x++){
//             const Coord bpos = iC(x,y);
//             const Coord wpos = coordMul(bpos, board.scale);
//             if((x+y)&1){
//                 setColor(board.blackSquare);
//                 fillSquareCoord(wpos, board.scale);
//             }
//
//             const Piece p = pAt(board, bpos);
//             if(p.type != T_EMPTY){
//                 setTextSize(board.scale);
//                 setTextColor(p.color == C_BLACK ? BLACK : WHITE);
//                 drawUtfCoord(pUtf(p), wpos);
//             }
//         }
//     }
// }

int main(int argc, char const *argv[])
{
    // setlocale(LC_ALL, "en_US.utf8");
    Length window = {.x = 800, .y = 600};
    init();
    setWindowLen(window);

    printf("♕ ♔ ♘ ♗ ♖ ♙\n");
    Board board = bNew();

    while(1){
        const uint t = frameStart();

        if(keyPressed(SDL_SCANCODE_ESCAPE) || ((keyHeld(SDL_SCANCODE_RCTRL) || keyHeld(SDL_SCANCODE_LCTRL)) && keyPressed(SDL_SCANCODE_Q)))
            return 0;

        board.scale = bRescale();
        //bDraw(board);
        setTextSize(board.scale);
        setTextColor(PINK);
        drawUtfCoord(L"♕ ♔ ♘ ♗ ♖ ♙", getWindowMid());

        frameEnd(t);
    }
    return 0;
}
