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

void aHighlight(const mCoord bpos, const pColor color, const uint scale)
{
    if(!bpos.valid)
        return;
    setColor(cColor[cInv(color)]);
    fillBorderCoordSquare(coordMul(bpos.pos, scale), scale, -8);
    setColor(cColor[color]);
    fillBorderCoordSquare(coordOffset(coordMul(bpos.pos, scale), (const Coord){2,2}), scale-4, -4);
}


#endif /* end of include guard: ACTIVEPLAYER_H */
