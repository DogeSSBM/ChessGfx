#ifndef BOARD_H
#define BOARD_H

uint bRescale(void)
{
    return coordMin(getWindowLen()) / 8;
}

Board bNew(void)
{
    Board ret = {
        .scale = bRescale(),
        .pieces = loadTexture("./piecesTransparent.png"),
        .arr = {0}
    };
    const pType home[8] = {T_ROOK, T_KNIGHT, T_BISHOP, T_QUEEN, T_KING, T_BISHOP, T_KNIGHT, T_ROOK};

    for(uint i = 0; i < 8; i++){
        ret.arr[i][0] = (const Piece){.color = C_BLACK, .type = home[i]};
        ret.arr[i][1] = (const Piece){.color = C_BLACK, .type = T_PAWN};

        ret.arr[i][6] = (const Piece){.color = C_WHITE, .type = T_PAWN};
        ret.arr[i][7] = (const Piece){.color = C_WHITE, .type = home[i]};
    }

    return ret;
}

void bPrint(const Board board)
{
    for(uint y = 0; y < 8; y++){
        printf("+---+---+---+---+---+---+---+---+\n|");
        for(uint x = 0; x < 8; x++){
            printf(" %s |", pStr(pAt(board, iC(x,y))));
        }
        printf("\n");
    }
    printf("+---+---+---+---+---+---+---+---+\n");
}

void bbPrint(const bBoard board)
{
    for(uint y = 0; y < 8; y++){
        printf("+---+---+---+---+---+---+---+---+\n|");
        for(uint x = 0; x < 8; x++){
            printf(" %c |", bbAt(board, iC(x,y)) ? 'X' : ' ');
        }
        printf("\n");
    }
    printf("+---+---+---+---+---+---+---+---+\n");
}

void bDraw(const Board board)
{
    setColor((const Color){.r=0xb9, .g=0xb9, .b=0xb9, .a=0xff});
    fillSquareCoord(iC(0,0), board.scale*8);
    for(uint y = 0; y < 8; y++){
        for(uint x = 0; x < 8; x++){
            const Coord bpos = iC(x,y);
            const Coord wpos = coordMul(bpos, board.scale);
            if((x+y)&1){
                setColor((const Color){.r=0x3b, .g=0x3b, .b=0x3b, .a=0xff});
                fillSquareCoord(wpos, board.scale);
            }

            const Piece p = pAt(board, bpos);
            if(p.type != T_EMPTY){
                SDL_RenderCopy(
                    gfx.renderer,
                    board.pieces,
                    &((const Rect){
                        .x = 64*(p.type-1), p.color == C_WHITE ? 64 : 0,
                        .w = 64,
                        .h = 64}
                    ),
                    &((const Rect){
                        .x = wpos.x,
                        .y = wpos.y,
                        .w = board.scale,
                        .h = board.scale}
                    )
                );
            }
        }
    }
}

bool bCoordValid(const Coord pos)
{
    return coordMin(pos) >= 0 && coordMax(pos) < 8;
}

void bInfluences(Board *board)
{
    const bBoard pcs = bbPieces(*board);
    const bBoard blk = bbColor(*board, C_BLACK);
    const bBoard wte = bbColor(*board, C_WHITE);
    for(uint y = 0; y < 8; y++){
        for(uint x = 0; x < 8; x++){
            const Coord pos = iC(x,y);
            if(!bbAt(pcs, pos))
                continue;

            const Piece p = pAt(*board, pos);
            board->threat[x][y] = pThreat(pcs, p.color == C_WHITE ? wte : blk, p, pos);
            board->attack[x][y] = bbRem(board->threat[x][y], bbInv(pcs));
            board->move[x][y] = pMove(pcs, p, pos);
        }
    }
}

Coord bKingPos(const Board board, const pColor color)
{
    if(color == C_EMPTY)
        panic("There are no kings with color C_EMPTY o.0\n");

    for(uint y = 0; y < 8; y++){
        for(uint x = 0; x < 8; x++){
            const Coord pos = iC(x,y);
            const Piece p = pAt(board, pos);
            if(p.type == T_KING && p.color == color)
                return pos;
        }
    }
    panic("I guess there was no %s king???\n", pColorStr[color]);
    return (const Coord){0};
}

bool bCheck(const Board board, const pColor color)
{
    if(color == C_EMPTY)
        panic("C_EMPTY can't be in check you dufas\n");

    const Coord kingPos = bKingPos(board, color);
    for(uint y = 0; y < 8; y++){
        for(uint x = 0; x < 8; x++){
            const Coord pos = iC(x,y);
            const Piece p = pAt(board, pos);
            if(p.color != C_EMPTY && board.threat[x][y].b[kingPos.x][kingPos.y])
                return true;
        }
    }

    return false;
}

bBoard bbOr(const bBoard a, const bBoard b)
{
    bBoard ret = {0};
    for(uint y = 0; y < 8; y++){
        for(uint x = 0; x < 8; x++){
            ret.b[x][y] = a.b[x][y] || b.b[x][y];
        }
    }
    return ret;
}

bBoard bbRem(bBoard board, const bBoard rem)
{
    for(uint y = 0; y < 8; y++){
        for(uint x = 0; x < 8; x++){
            if(rem.b[x][y])
                board.b[x][y] = false;
        }
    }
    return board;
}

bBoard bbInv(const bBoard a)
{
    bBoard ret = {0};
    for(uint y = 0; y < 8; y++){
        for(uint x = 0; x < 8; x++){
            ret.b[x][y] = !a.b[x][y];
        }
    }
    return ret;
}

bBoard bbColor(const Board board, const pColor color)
{
    bBoard ret = {0};
    for(uint y = 0; y < 8; y++){
        for(uint x = 0; x < 8; x++){
            ret.b[x][y] = board.arr[x][y].color == color;
        }
    }
    return ret;
}

bBoard bbPieces(const Board board)
{
    return bbInv(bbColor(board, C_EMPTY));
}

bool bbAt(const bBoard board, const Coord pos)
{
    if(!bCoordValid(pos))
        panic("Cannot get b at coord {%i,%i}\n", pos.x, pos.y);
    return board.b[pos.x][pos.y];
}

bBoard bbSet(bBoard board, const Coord pos, const bool b)
{
    if(!bCoordValid(pos))
        panic("Cannot set b at coord {%i,%i}\n", pos.x, pos.y);
    board.b[pos.x][pos.y] = b;
    return board;
}

bBoard bbCast(const bBoard pieces, const Coord pos, const Ang a, const uint len)
{
    bBoard ret = {0};
    for(uint i = 1; i <= (len ? len : 7); i++){
        const Coord at = aMov(pos, a, i);
        if(!bCoordValid(at))
            return ret;
        ret = bbSet(ret, at, true);
        if(bbAt(pieces, at))
            return ret;
    }
    return ret;
}

#endif /* end of include guard: BOARD_H */
