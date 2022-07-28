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

Turn *applyTurn(Board *board, Turn *turn)
{
    if(!turn)
        return NULL;
    switch(turn->type){
        case M_MOVE:
            *board = pSet(*board, turn->move.src, (const Piece){0});
            *board = pSet(*board, turn->move.dst, turn->move.moved);
            break;
        case M_CAPTURE:
            *board = pSet(*board, turn->capture.src, (const Piece){0});
            *board = pSet(*board, turn->capture.dst, turn->capture.moved);
            break;
    }
    return turn->next;
}

void tConstructBoard(Board *board, Turn *turns)
{
    Turn *cur = turns;
    *board = bNew();
    board->scale = bRescale();
    while((cur = applyTurn(board, cur)));
    bInfluences(board);
}

bool tValid(Board *const board, Turn *const turn)
{
    Board after;
    memcpy(&after, board, sizeof(Board));
    applyTurn(&after, turn);
    bInfluences(&after);

    return !bCheck(after, turn->color);
}

#endif /* end of include guard: TURN_H */
