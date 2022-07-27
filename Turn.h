#ifndef TURN_H
#define TURN_H

Turn *tNew(const pColor color)
{
    Turn *t = calloc(1, sizeof(Turn));
    if(!t)
        panic("Failed to calloc turn!\n");
    t->color = color;
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

void tConstructBoard(Board *board, Turn *turns)
{
    *board = bNew();
    board->scale = bRescale();
    while(turns){
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
        turns = turns->next;
    }
    bInfluences(board);
}

#endif /* end of include guard: TURN_H */
