#pragma once

#include <iostream>
#include <vector>
#include <list>


#define WIN_VALUE  50000	// win the game
#define PAWN_VALUE    30	// 8x
#define ROOK_VALUE    90	// 2x
#define KNIGHT_VALUE  85	// 2x
#define BISHOP_VALUE  84	// 2x
#define QUEEN_VALUE  300	// 1x
#define KING_VALUE 	 ((PAWN_VALUE * 8) + (ROOK_VALUE * 2) \
						+ (KNIGHT_VALUE * 2) + (BISHOP_VALUE * 2) + QUEEN_VALUE + WIN_VALUE)

/* use the first four bits to define the piece figure */

#define PAWN 0x01
#define ROOK 0x02
#define KNIGHT 0x03
#define BISHOP 0x04
#define QUEEN 0x05
#define KING 0x06

/* gets the piece's figure */
#define FIGURE 0x0F
#define GET_FIGURE(x) (x & FIGURE);
#define CLEAR_FIGURE(x) (x & 0xF0);

/* store the color in the 5th bit */
#define WHITE 0x00
#define BLACK 0x10
#define SET_BLACK(x) (BLACK | x);
#define GET_COLOR(x) (x & BLACK);
#define TOGGLE_COLOR(x) (BLACK ^ x)

/* store if the piece has moved in the 6th bit */
#define MOVED 0x20
#define SET_MOVED(x) (x | MOVED)
#define IS_MOVED(x)  (MOVED & x)

/* store au passant candidacy in 7th bit */
#define PASSANT 0x40
#define SET_PASSANT(x)   (x | PASSANT)
#define CLEAR_PASSANT(x) (x & 0xbf)
#define GET_PASSANT(x)   (PASSANT & x)

/* store promotion eligibility in 8th bit */
#define PROMOTION_ELIGIBLE
#define SET_PROMOTED(x)   (x | PROMOTION_ELIGIBLE)
#define IS_PROMOTED(x)    (PROMOTION_ELIGIBLE & x)
#define CLEAR_PROMOTED(x) (x & 0x7f)

#define GRABBED_PIECE 32
#define EMPTY 33


/* structures */

struct PieceInfo_s
{

    int identifier;
    int figure;
    int space;
    int previousSpace;
};

struct PieceInfoLog_s               /* keeps track of the piece info of the moved pieces
                                     * before they were moved
                                     */
{
    PieceInfo_s piece1;
    PieceInfo_s piece2;
};

struct Special_Move_s               /* castleing, au passant */
{

    int piece1, from1, to1;

    int piece2, from2, to2;
};

struct Move_s                       /* standard moves */
{
    int piece, to, from;
};


struct MoveLog_s {                  /* this move log keeps track of the last move made */

    MoveLog_s();
    
    int piece1, to1, from1;
    int piece2, to2, from2;
};

/* enumerators */

enum class GameState_ec
{
    PLAY, EXIT
};

enum Spaces_e
{
    A8 = 0, B8, C8, D8, E8, F8, G8, H8,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A1, B1, C1, D1, E1, F1, G1, H1,
    Grabbed, Captured
};

struct MoveNode {
    Move_s move;
    std::vector<MoveNode> nextMoves;

    // constructors
    MoveNode();
    MoveNode(int n)                // where n is the number of next possible moves in response]
    {
        MoveNode possMove;
        nextMoves.push_back(possMove);
    }
};

/* classes */

class Board_c
{
    public:

        enum Direction
        {
            DirectionNorth = 0, DirectionSouth = 1, DirectionWest = 2, DirectionEast = 3,
            DirectionNorthWest = 4, DirectionNorthEast = 5, DirectionSouthWest = 6, DirectionSouthEast = 7
        };

        Board_c();
        ~Board_c();

        //static int board[64];
        std::vector<int> board;
        void printBoard(std::vector<int> board);
        

        /* These arrays are created to provide the functionality of the edges since the board array is only in 1 dimension */
        static const int directionOffSets[8];
        static const int knightDirectionOffsets[8];
        static const int knightMaxSpacesToEdge[8][4];
        static int numSquaresToEdge[64][8];

    private:

        void initializeStartingBoard();
        static void initializeNumSquaresToEdge();

};

class Piece_c
{
    public:

        Piece_c();
        ~Piece_c();

        /* initialize structure for each piece */
        PieceInfo_s w1; PieceInfo_s w2; PieceInfo_s w3; PieceInfo_s w4; PieceInfo_s w5; PieceInfo_s w6; PieceInfo_s w7; PieceInfo_s w8;
        PieceInfo_s w9; PieceInfo_s w10; PieceInfo_s w11; PieceInfo_s w12; PieceInfo_s w13; PieceInfo_s w14; PieceInfo_s w15; PieceInfo_s w16;
        PieceInfo_s b1; PieceInfo_s b2; PieceInfo_s b3; PieceInfo_s b4; PieceInfo_s b5; PieceInfo_s b6; PieceInfo_s b7; PieceInfo_s b8;
        PieceInfo_s b9; PieceInfo_s b10; PieceInfo_s b11; PieceInfo_s b12; PieceInfo_s b13; PieceInfo_s b14; PieceInfo_s b15; PieceInfo_s b16;
        PieceInfo_s grabbedPiece; PieceInfo_s grabbedPieceLog;

        static std::vector<PieceInfo_s> pieceInfo;

        MoveLog_s moveLog;
        std::vector<PieceInfoLog_s> pieceInfoLog; PieceInfo_s clearedPieceInfo;

        void initializeClearedPieceInfo();

    protected:

        void initializePieceStates();
        void clearGrabbedPieceLog();
        void clearGrabbedPiece();

        // testing
        void printPieceInfo();
};

