#ifndef BOARD_H
#define BOARD_H

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
        .pieces = loadTexture("./Pieces/piecesTransparent.png"),
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

void bDraw(const Board board)
{
    setColor(board.whiteSquare);
    fillSquareCoord(iC(0,0), board.scale*8);
    for(uint y = 0; y < 8; y++){
        for(uint x = 0; x < 8; x++){
            const Coord bpos = iC(x,y);
            const Coord wpos = coordMul(bpos, board.scale);
            if((x+y)&1){
                setColor(board.blackSquare);
                fillSquareCoord(wpos, board.scale);
            }

            const Piece p = pAt(board, bpos);
            if(p.type != T_EMPTY){
                SDL_RenderCopy(
                    gfx.renderer,
                    board.pieces,
                    &((const Rect){.x = 64*(p.type-1), p.color == C_WHITE ? 64 : 0, .w = 64, .h = 64}),
                    &((const Rect){.x = wpos.x, .y = wpos.y, .w = board.scale, .h = board.scale})
                );
            }
        }
    }
}

bool bCoordValid(const Coord pos)
{
    return coordMin(pos) >= 0 && coordMax(pos) < 8;
}

#endif /* end of include guard: BOARD_H */
