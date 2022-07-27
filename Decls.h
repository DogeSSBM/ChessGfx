#ifndef DECLS_H
#define DECLS_H

// PANIC_H
void panic( const char *, ... );

// PIECE_H
const char* pStr(const Piece);
Piece pAt(const Board, const Coord);
Board pSet(Board, const Coord, const Piece);
bBoard pThreat(const bBoard, const bBoard, const Piece, const Coord);

// BOARD_H
uint bRescale(void);
Board bNew(void);
void bPrint(const Board);
void bDraw(const Board);
bool bCoordValid(const Coord);
bBoard bbOr(const bBoard, const bBoard);
bBoard bbRem(bBoard, const bBoard);
bBoard bbInv(const bBoard);
bBoard bbColor(const Board, const pColor);
bBoard bbPieces(const Board);
bool bbAt(const bBoard, const Coord);
bBoard bbSet(bBoard, const Coord, const bool);
bBoard bbCast(const bBoard, const Coord, const Ang, const uint);

// TURN_H
Turn *tNew(const pColor);
Turn *tLast(Turn *const);
Turn *tAppend(Turn *const, Turn *const);
void tFree(Turn *const);

// ACTIVEPLAYER_H
mCoord aMouseMpos(const uint);
mCoord aBoardMpos(const uint);
void aHighlight(const Board, const ActivePlayer);
ActivePlayer aMbtn(const Board, ActivePlayer);
ActivePlayer aClick(const Board, ActivePlayer);
bool aValidClick(const ActivePlayer);
ActivePlayer aUpdateMouse(ActivePlayer, const Board);

#endif /* end of include guard: DECLS_H */
