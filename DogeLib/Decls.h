#ifndef DECLS_H
#define DECLS_H

// PANIC_H
void panic( const char *, ... );

// PIECE_H
const char* pStr(const Piece);
Piece pAt(const Board, const Coord);

// BOARD_H
uint bRescale(void);
Board bNew(void);
void bPrint(const Board );
void bDraw(const Board );

#endif /* end of include guard: DECLS_H */
