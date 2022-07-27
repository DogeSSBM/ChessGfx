#ifndef ACTIVEPLAYER_H
#define ACTIVEPLAYER_H

mCoord aMouseMpos(const uint scale)
{
    if(inBound(mouse.pos.x, 0, scale*8) && inBound(mouse.pos.y, 0, scale*8))
        return (const mCoord){.valid = true, .pos = mouse.pos};
    return (const mCoord){0};
}

mCoord aBoardMpos(const uint scale)
{
    const mCoord mpos = aMouseMpos(scale);
    if(mpos.valid)
        return (const mCoord){.valid = true, .pos = coordDiv(mpos.pos, imax(scale, 1))};
    return (const mCoord){0};
}

void aCircle(const Coord pos, const uint scale)
{
    drawCircleCoord(
        coordOffset(
            coordMul(pos, scale),
            coordDiv(iC(scale, scale), 2)
        ),
        scale / 2
    );
    drawCircleCoord(
        coordOffset(
            coordMul(pos, scale),
            coordDiv(iC(scale, scale), 2)
        ),
        (scale / 2)-1
    );
}

void aHighlight(const Board board, const ActivePlayer active)
{
    if(active.mbpos.valid){
        if(pAt(board, active.mbpos.pos).color == active.color){
            setColor(cColor[cInv(active.color)]);
            fillBorderCoordSquare(
                coordMul(active.mbpos.pos, board.scale),
                board.scale,
                -8
            );
            setColor(cColor[active.color]);
            fillBorderCoordSquare(
                coordOffset(coordMul(active.mbpos.pos, board.scale),(const Coord){2,2}),
                board.scale - 4,
                -4
            );
        }else{
            setColor(GREY);
            fillBorderCoordSquare(
                coordMul(active.mbpos.pos, board.scale),
                board.scale,
                -8
            );
        }
    }

    if(active.msrc.valid){
        setColor(GREEN);
        fillBorderCoordSquare(coordMul(active.msrc.pos, board.scale), board.scale, -8);

        // const bBoard pcs = bbPieces(board);
        // const bBoard threat = bbRem(
        //     pThreat(
        //         pcs, pAt(board, active.msrc.pos), active.msrc.pos
        //     ),
        //     bbColor(board, active.color)
        // );
        // const bBoard atk = bbRem(
        //     threat,
        //     bbInv(pcs)
        // );
        // const bBoard move = pMove(pcs, pAt(board, active.msrc.pos), active.msrc.pos);

        const Coord ppos = active.msrc.pos;
        for(uint y = 0; y < 8; y++){
            for(uint x = 0; x < 8; x++){
                const Coord bbpos = iC(x,y);

                if(bbAt(board.threat[ppos.x][ppos.y], bbpos)){
                    setColor(GREY);
                    aCircle(bbpos, board.scale);
                }

                if(bbAt(board.move[ppos.x][ppos.y], bbpos)){
                    setColor(BLUE);
                    aCircle(bbpos, board.scale);
                }

                if(bbAt(board.attack[ppos.x][ppos.y], bbpos)){
                    setColor(RED);
                    aCircle(bbpos, board.scale);
                }
            }
        }
    }
}

ActivePlayer aMbtn(const Board board, ActivePlayer active)
{
    if(mouseBtnPressed(MOUSE_L)){
        active.downAt = active.mbpos;
    }

    if(mouseBtnReleased(MOUSE_L)){
        active.upAt = active.mbpos;
        if(
            active.downAt.valid && active.upAt.valid && coordSame(active.downAt.pos, active.upAt.pos) &&
            pAt(board, active.mbpos.pos).color == active.color
        ){
            active.msrc = active.mbpos;
        }else{
            active.msrc = (const mCoord){0};
        }
        active.downAt = (const mCoord){0};
    }
    return active;
}

#endif /* end of include guard: ACTIVEPLAYER_H */
