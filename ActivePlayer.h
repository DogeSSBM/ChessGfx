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
    }
}


#endif /* end of include guard: ACTIVEPLAYER_H */
