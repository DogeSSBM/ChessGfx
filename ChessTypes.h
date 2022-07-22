#ifndef CHESSTYPES_H
#define CHESSTYPES_H

int imax(const int a, const int b)
{
    return a > b ? a : b;
}

int imin(const int a, const int b)
{
    return a < b ? a : b;
}

int iabs(const int i)
{
    return i > 0 ? i : -i;
}

typedef struct{
    bool valid;
    union{
        struct{
            int x;
            int y;
        };
        Coord pos;
    };
}mCoord;

typedef enum{T_EMPTY, T_KING, T_QUEEN, T_KNIGHT, T_BISHOP, T_ROOK, T_PAWN}pType;
typedef enum{C_EMPTY, C_WHITE, C_BLACK}pColor;
const Color cColor[3] = {(const Color){0}, WHITE, BLACK};

pColor cInv(const pColor color){
    if(color == C_EMPTY)
        return color;
    return color == C_WHITE ? C_BLACK : C_WHITE;
}

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

typedef struct{
    Coord src;
    Coord dst;
}Move;

typedef enum{M_INVALID, M_MOVE, M_CAPTURE, M_CASTLE, M_PROMOTE, M_P_CHARGE, M_P_PASSANT}mType;

typedef struct Turn{
    mType type;
    pColor color;
    union{
        struct{
            Coord src;
            Coord dst;
            Piece moved;
        }move;
        struct{
            Coord src;
            Coord dst;
            Piece moved;
            Piece captured;
        }capture;
        struct{
            struct{
                Coord src;
                Coord dst;
            }rook;
            struct{
                Coord src;
                Coord dst;
            }king;
        }castle;
        struct{
            Coord src;
            Coord dst;
            Piece before;
            Piece promoted;
        }promote;
        struct{
            Coord src;
            Coord dst;
            Piece pawn;
        }charge;
        struct{
            Coord src;
            Coord dst;
            Piece moved;
            Piece captured;
        }passant;
    };
    struct Turn *next;
}Turn;

typedef struct{
    pColor color;
    mCoord downAt;
    mCoord upAt;
    mCoord mbpos;
    mCoord msrc;
    mCoord mdst;
}ActivePlayer;

#endif /* end of include guard: CHESSTYPES_H */
