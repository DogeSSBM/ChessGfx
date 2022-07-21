#ifndef TURN_H
#define TURN_H

Turn *tNew(const mType type, const pColor color)
{
    Turn *t = calloc(1, sizeof(Turn));
    if(!t)
        panic("Failed to calloc turn!\n");
    t->color = color;
    t->type = type;
    return t;
}

Turn *tAppend(Turn *const head, Turn *const tail)
{
    if(!head)
        return tail;
    Turn *cur = head;
    while(cur->next)
        cur = cur->next;
    cur->next = tail;
    return head;
}

#endif /* end of include guard: TURN_H */
