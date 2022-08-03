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

//            000   001   010   011   100   101   110   111
typedef enum{A_UU, A_UR, A_RR, A_DR, A_DD, A_DL, A_LL, A_UL, A_END}Ang;
const char *const AngStr[8] = {"A_UU", "A_UR", "A_RR", "A_DR", "A_DD", "A_DL", "A_LL", "A_UL"};

Offset aOff(const Ang a)
{
    switch(a){
        case A_UU:
            return (const Offset){.y = -1};
            break;
        case A_UR:
            return (const Offset){.x = 1, .y = -1};
            break;
        case A_RR:
            return (const Offset){.x = 1};
            break;
        case A_DR:
            return (const Offset){.x = 1, .y = 1};
            break;
        case A_DD:
            return (const Offset){.y = 1};
            break;
        case A_DL:
            return (const Offset){.x = -1, .y = 1};
            break;
        case A_LL:
            return (const Offset){.x = -1};
            break;
        case A_UL:
            return (const Offset){.x = -1, .y = -1};
            break;
        default:
            break;
    }
    fprintf(stderr, "Invalid Ang:%i\n", a);
    exit(EXIT_FAILURE);
    return (const Offset){0};
}

Ang aInv(const Ang a)
{
    return a^0b100;
}

Ang aRoi(const Ang a, const int i)
{
    return a+i < 0 ? A_END - (iabs(i)%A_END) : (a+i)%A_END;
}

Coord aMov(const Coord pos, const Ang a, const int i)
{
    return coordOffset(pos, coordMul(aOff(a), i));
}

typedef enum{T_EMPTY, T_QUEEN, T_KING, T_KNIGHT, T_BISHOP, T_ROOK, T_PAWN}pType;
const char *pTypeStr[7] = {
    "T_EMPTY", "T_QUEEN", "T_KING", "T_KNIGHT", "T_BISHOP", "T_ROOK", "T_PAWN"
};

typedef enum{C_EMPTY, C_WHITE, C_BLACK}pColor;
const char *const pColorStr[3] = {"C_EMPTY", "C_WHITE", "C_BLACK"};
const Color cColor[3] = {(const Color){0}, WHITE, BLACK};

pColor cInv(const pColor color){
    if(color == C_EMPTY)
        return color;
    return color == C_WHITE ? C_BLACK : C_WHITE;
}

Ang cFward(const pColor color)
{
    if(color == C_EMPTY){
        fprintf(stderr, "C_EMPTY does not have a forward direction\n");
        exit(EXIT_FAILURE);
    }
    return color ==  C_WHITE ? A_UU : A_DD;
}

Ang cBward(const pColor color)
{
    if(color == C_EMPTY){
        fprintf(stderr, "C_EMPTY does not have a backward direction\n");
        exit(EXIT_FAILURE);
    }
    return color ==  C_BLACK ? A_UU : A_DD;
}

typedef struct{
    pColor color;
    pType type;
}Piece;

typedef struct{
    bool b[8][8];
}bBoard;

typedef struct{
    bBoard move[8][8];
    bBoard threat[8][8];
    bBoard attack[8][8];
    uint scale;
    SDL_Texture *pieces;
    Piece arr[8][8];
}Board;

typedef enum{M_MOVE, M_CAPTURE}mType;

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
