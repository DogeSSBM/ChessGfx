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

#endif /* end of include guard: PIECE_H */
