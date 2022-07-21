#ifndef CHESSTYPES_H
#define CHESSTYPES_H

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
    SDL_Texture *pieces;
    Piece arr[8][8];
}Board;

typedef enum{M_MOVE, M_CAPTURE, M_CASTLE, M_PROMOTE, M_P_CHARGE, M_P_PASSANT}mType;

typedef struct Turn{
    mType type;
    union{
        struct{
            Coord src;
            Coord dst;
        }move;
        struct{
            Coord src;
            Coord dst;
            Piece captured;
        }capture;
        struct{
            Coord rook;
            Coord king;
        }castle;
        struct{
            Coord
        }
    }
    struct Turn *next;
}Turn;

#endif /* end of include guard: CHESSTYPES_H */
