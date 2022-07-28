#ifndef TURN_H
#define TURN_H

Turn *tNew(const Piece srcpiece, const Piece dstpiece, const Coord srcpos, const Coord dstpos)
{
    Turn *t = calloc(1, sizeof(Turn));
    if(!t)
        panic("Failed to calloc turn!\n");
    t->color = srcpiece.color;
    if(dstpiece.color == C_EMPTY){
        t->type = M_MOVE;
        t->move.src = srcpos;
        t->move.dst = dstpos;
        t->move.moved = srcpiece;
    }else{
        t->type = M_CAPTURE;
        t->capture.src = srcpos;
        t->capture.dst = dstpos;
        t->capture.moved = srcpiece;
        t->capture.captured = dstpiece;
    }

    return t;
}

Turn *tLast(Turn *const head)
{
    if(!head)
        return NULL;
    Turn *cur = head;
    while(cur->next)
        cur = cur->next;
    return cur;
}

Turn *tAppend(Turn *const head, Turn *const tail)
{
    if(!head)
        return tail;
    tLast(head)->next = tail;
    return head;
}

void tFree(Turn *const head)
{
    if(!head)
        return;
    Turn *cur = head;
    while(cur->next)
    {
        Turn *next = cur->next;
        free(cur);
        cur = next;
    }
    free(cur);
}

Turn *applyTurn(Board *board, Turn *turns)
{
    if(!turns)
        return NULL;
    switch(turns->type){
        case M_MOVE:
            *board = pSet(*board, turns->move.src, (const Piece){0});
            *board = pSet(*board, turns->move.dst, turns->move.moved);
            break;
        case M_CAPTURE:
            *board = pSet(*board, turns->capture.src, (const Piece){0});
            *board = pSet(*board, turns->capture.dst, turns->capture.moved);
            break;
    }
    return turns->next;
}

void tConstructBoard(Board *board, Turn *turns)
{
    *board = bNew();
    board->scale = bRescale();
    while((turns = applyTurn(board, turns)));
    bInfluences(board);
}

#endif /* end of include guard: TURN_H */
