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
    if(!bCoordValid(pos))
        panic("Cannot get piece at coord {%i,%i}\n", pos.x, pos.y);
    return board.arr[pos.x][pos.y];
}

Board pSet(Board board, const Coord pos, const Piece p)
{
    if(!bCoordValid(pos))
        panic("Cannot set piece at coord {%i,%i}\n", pos.x, pos.y);
    board.arr[pos.x][pos.y] = p;
    return board;
}

Board pClear(Board board, const Coord pos)
{
    if(!bCoordValid(pos))
        panic("Cannot clear piece at coord {%i,%i}\n", pos.x, pos.y);
    board.arr[pos.x][pos.y] = (const Piece){0};
    return board;
}

bBoard pThreat(const bBoard pieces, const Piece p, const Coord pos)
{
    bBoard ret = {0};
    switch(p.type){
        case T_KING:
            for(uint i = 0; i < 8; i++)
                ret = bbOr(ret, bbCast(pieces, pos, i, 1));
            break;
        case T_QUEEN:
            for(uint i = 0; i < 8; i++)
                ret = bbOr(ret, bbCast(pieces, pos, i, 0));
            break;
        case T_KNIGHT:
            for(uint i = 0; i < 8; i+=2){
                const Coord f1 = aMov(pos, i, 1);
                Coord atk = aMov(f1, aRoi(i,  2), 2);
                if(bCoordValid(atk))
                    ret = bbSet(ret, atk, true);

                atk = aMov(f1, aRoi(i, -2), 2);
                if(bCoordValid(atk))
                    ret = bbSet(ret, atk, true);

                const Coord f2 = aMov(pos, i, 2);
                atk = aMov(f2, aRoi(i,  2), 1);
                if(bCoordValid(atk))
                    ret = bbSet(ret, atk, true);

                atk = aMov(f2, aRoi(i, -2), 1);
                if(bCoordValid(atk))
                    ret = bbSet(ret, atk, true);
            }
            break;
        case T_BISHOP:
            for(uint i = 1; i < 8; i+=2)
                ret = bbOr(ret, bbCast(pieces, pos, i, 0));
            break;
        case T_ROOK:
            for(uint i = 0; i < 8; i+=2)
                ret = bbOr(ret, bbCast(pieces, pos, i, 0));
            break;
        case T_PAWN:
            ;
            Coord atk = aMov(pos, p.color == C_BLACK ? A_DR : A_UR, 1);
            if(bCoordValid(atk))
                ret = bbSet(ret, atk, true);

            atk = aMov(pos, p.color == C_BLACK ? A_DL : A_UL, 1);
            if(bCoordValid(atk))
                ret = bbSet(ret, atk, true);
            break;
        case T_EMPTY:
        default:
            panic("Cant pMoves unknown piece:%i\n", p);
            break;
    }

    return ret;
}

bBoard pMove(const bBoard pieces, const Piece p, const Coord pos)
{
    bBoard ret = {0};
    switch(p.type){
        case T_KING:
            for(uint i = 0; i < 8; i++)
                ret = bbOr(ret, bbCast(pieces, pos, i, 1));
            break;
        case T_QUEEN:
            for(uint i = 0; i < 8; i++)
                ret = bbOr(ret, bbCast(pieces, pos, i, 0));
            break;
        case T_KNIGHT:
            for(uint i = 0; i < 8; i+=2){
                const Coord f1 = aMov(pos, i, 1);
                Coord atk = aMov(f1, aRoi(i,  2), 2);
                if(bCoordValid(atk))
                    ret = bbSet(ret, atk, true);

                atk = aMov(f1, aRoi(i, -2), 2);
                if(bCoordValid(atk))
                    ret = bbSet(ret, atk, true);

                const Coord f2 = aMov(pos, i, 2);
                atk = aMov(f2, aRoi(i,  2), 1);
                if(bCoordValid(atk))
                    ret = bbSet(ret, atk, true);

                atk = aMov(f2, aRoi(i, -2), 1);
                if(bCoordValid(atk))
                    ret = bbSet(ret, atk, true);
            }
            break;
        case T_BISHOP:
            for(uint i = 1; i < 8; i+=2)
                ret = bbOr(ret, bbCast(pieces, pos, i, 0));
            break;
        case T_ROOK:
            for(uint i = 0; i < 8; i+=2)
                ret = bbOr(ret, bbCast(pieces, pos, i, 0));
            break;
        case T_PAWN:
            ;
            const Coord m1 = aMov(pos, p.color == C_BLACK ? A_DD : A_UU, 1);
            if(bCoordValid(m1)){
                ret = bbSet(ret, m1, true);
                if(pos.y == (p.color == C_BLACK ? 1 : 6)){
                    const Coord m2 = aMov(pos, p.color == C_BLACK ? A_DD : A_UU, 2);
                    if(bCoordValid(m2))
                        ret = bbSet(ret, m2, true);
                }
            }
            break;
        case T_EMPTY:
        default:
            panic("Cant pMoves unknown piece:%i\n", p);
            break;
    }
    ret = bbRem(ret, pieces);
    return ret;
}

#endif /* end of include guard: PIECE_H */
