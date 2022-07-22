#ifndef PIECE_H
#define PIECE_H

const char* pStr(const Piece p)
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

Board pSet(Board board, const Coord pos, const Piece p)
{
    if(coordMin(pos) < 0 || coordMax(pos) > 7)
        panic("Cannot set piece at coord {%i,%i}\n", pos.x, pos.y);
    board.arr[pos.x][pos.y] = p;
    return board;
}

Board pClear(Board board, const Coord pos)
{
    if(coordMin(pos) < 0 || coordMax(pos) > 7)
        panic("Cannot clear piece at coord {%i,%i}\n", pos.x, pos.y);
    board.arr[pos.x][pos.y] = (const Piece){0};
    return board;
}

bBoard pMoves(const bBoard pieces, const Piece p, const Coord pos)
{
    bBoard ret = {0};
    switch(p.type){
        case T_KING:

            break;
        case T_QUEEN:

            break;
        case T_KNIGHT:

            break;
        case T_BISHOP:

            break;
        case T_ROOK:

            break;
        case T_PAWN:

            break;
        case T_EMPTY:
        default:

            break;
    }
    return ret;
}

#endif /* end of include guard: PIECE_H */
