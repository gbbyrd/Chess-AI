#include "../include/headers/board.h"

MoveLog_s::MoveLog_s() 
{
    piece1 = EMPTY;
    from1 = Captured;
    to1 = Captured;
    piece2 = EMPTY;
    from2 = Captured;
    to2 = Captured;
}

Board_c::Board_c()
{
    initializeNumSquaresToEdge();
    board = {
            24, 25, 26, 27, 28, 29, 30, 31,
            16, 17, 18, 19, 20, 21, 22, 23,
            33, 33, 33, 33, 33, 33, 33, 33,
            33, 33, 33, 33, 33, 33, 33, 33,
            33, 33, 33, 33, 33, 33, 33, 33,
            33, 33, 33, 33, 33, 33, 33, 33,
            0,  1,  2,  3,  4,  5,  6,  7,
            8,  9,  10, 11, 12, 13, 14, 15
            };
}

Board_c::~Board_c(){}

void Board_c::printBoard(std::vector<int> board){

    int rank[] = {8, 7, 6, 5, 4, 3, 2, 1};

    char file[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    std::cout << "-";

    for (int i = 0; i < 8; i++)
    {
        std::cout << "  " << file[i];
    }

    std::cout << "  -" << std::endl;

    std::cout << rank[0];

    for (int i = 0; i < 64; i++)
    {
        if (board[i] < 10)
        {
            std::cout << "  " << board[i];
        }
        else
        {
            std::cout << " " << board[i];
        }

        if ((i + 1) % 8 == 0 && i != 63)
        {
            std::cout  << "  " << rank[((i + 1) / 8) - 1] << std::endl << rank[(i + 1) / 8];
        }
    }

    std::cout << "  " << rank[7] << std::endl;

    std::cout << "-";

    for (int i = 0; i < 8; i++)
    {
        std::cout << "  " << file[i];
    }

    std::cout << "  -" << std::endl;
    std::cout << std::endl;
}

MoveNode::MoveNode(){}

const int Board_c::directionOffSets[8] = {-8, 8, -1, 1, -9, -7, 7, 9};

const int Board_c::knightDirectionOffsets[8] = {-15, -6, 10, 17, 15, 6, -10, -17};

const int Board_c::knightMaxSpacesToEdge[8][4] = 
{
                                                {DirectionNorth, 2, DirectionEast, 1},
                                                {DirectionNorth, 1, DirectionEast, 2},
                                                {DirectionSouth, 1, DirectionEast, 2},
                                                {DirectionSouth, 2, DirectionEast, 1},
                                                {DirectionSouth, 2, DirectionWest, 1},
                                                {DirectionSouth, 1, DirectionWest, 2},
                                                {DirectionNorth, 1, DirectionWest, 2},
                                                {DirectionNorth, 2, DirectionWest, 1}
                                                };

int Board_c::numSquaresToEdge[64][8] = 
{
                                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}
                                    };

void Board_c::initializeNumSquaresToEdge() 
{

   for (int i = 0; i < 10; i++)
    {
        for (int rank = 0; rank < 8; rank++)
        {
            for (int file = 0; file < 8; file++)
            {
                int squareIndex = (8 * rank) + file;

                    numSquaresToEdge[squareIndex][0] = rank;                                    // north
                    numSquaresToEdge[squareIndex][1] = 7 - rank;                                // south 
                    numSquaresToEdge[squareIndex][2] = file;                                    // west
                    numSquaresToEdge[squareIndex][3] = 7 - file;                                // east
                    numSquaresToEdge[squareIndex][4] = std::min(rank, file);                    // northwest
                    numSquaresToEdge[squareIndex][5] = std::min(rank, 7 - file);                // northeast
                    numSquaresToEdge[squareIndex][6] = std::min(7 - rank, file);                // southwest
                    numSquaresToEdge[squareIndex][7] = std::min(7 - rank, 7 - file);            // southeast     
            }
        }
    } 
}

std::vector<PieceInfo_s> Piece_c::pieceInfo = {};

Piece_c::Piece_c()
{
    initializePieceStates();
    clearGrabbedPieceLog();
    clearGrabbedPiece();
    initializeClearedPieceInfo();
}

Piece_c::~Piece_c(){}

void Piece_c::initializeClearedPieceInfo()
{
    clearedPieceInfo.identifier = 32;
    clearedPieceInfo.figure = 0;
    clearedPieceInfo.previousSpace = Captured;
    clearedPieceInfo.space = Captured;
}

void Piece_c::initializePieceStates()
{
    // initialize piece information
    w1.identifier = 0; w1.figure = PAWN; w1.space = A2; w1.previousSpace = A2; w2.identifier = 1; w2.figure = PAWN; w2.space = B2; w2.previousSpace = B2; 
    w3.identifier = 2; w3.figure = PAWN; w3.space = C2; w3.previousSpace = C2; w4.identifier = 3; w4.figure = PAWN; w4.space = D2; w4.previousSpace = D2; 
    w5.identifier = 4; w5.figure = PAWN; w5.space = E2; w5.previousSpace = E2; w6.identifier = 5; w6.figure = PAWN; w6.space = F2; w6.previousSpace = F2;
    w7.identifier = 6; w7.figure = PAWN; w7.space = G2; w7.previousSpace = G2; w8.identifier = 7; w8.figure = PAWN; w8.space = H2; w8.previousSpace = H2;
    w9.identifier = 8; w9.figure = ROOK; w9.space = A1; w9.previousSpace = A1; w10.identifier = 9; w10.figure = KNIGHT; w10.space = B1; w10.previousSpace = B1;
    w11.identifier = 10; w11.figure = BISHOP; w11.space = C1; w11.previousSpace = C1; w12.identifier = 11; w12.figure = QUEEN; w12.space = D1; w12.previousSpace = D1;
    w13.identifier = 12; w13.figure = KING; w13.space = E1; w13.previousSpace = E1; w14.identifier = 13; w14.figure = BISHOP; w14.space = F1; w14.previousSpace = F1;
    w15.identifier = 14; w15.figure = KNIGHT; w15.space = G1; w15.previousSpace = G1; w16.identifier = 15; w16.figure = ROOK; w16.space = H1; w16.previousSpace = H1;

    b1.identifier = 16; b1.figure = SET_BLACK(PAWN); b1.space = A7; b1.previousSpace = A7; b2.identifier = 17; b2.figure = SET_BLACK(PAWN); b2.space = B7; b2.previousSpace = B7; 
    b3.identifier = 18; b3.figure = SET_BLACK(PAWN); b3.space = C7; b3.previousSpace = C7; b4.identifier = 19; b4.figure = SET_BLACK(PAWN); b4.space = D7; b4.previousSpace = D7; 
    b5.identifier = 20; b5.figure = SET_BLACK(PAWN); b5.space = E7; b5.previousSpace = E7; b6.identifier = 21; b6.figure = SET_BLACK(PAWN); b6.space = F7; b6.previousSpace = F7;
    b7.identifier = 22; b7.figure = SET_BLACK(PAWN); b7.space = G7; b7.previousSpace = G7; b8.identifier = 23; b8.figure = SET_BLACK(PAWN); b8.space = H7; b8.previousSpace = H7;
    b9.identifier = 24; b9.figure = SET_BLACK(ROOK); b9.space = A8; b9.previousSpace = A8; b10.identifier = 25; b10.figure = SET_BLACK(KNIGHT); b10.space = B8; b10.previousSpace = B8;
    b11.identifier = 26; b11.figure = SET_BLACK(BISHOP); b11.space = C8; b11.previousSpace = C8; b12.identifier = 27; b12.figure = SET_BLACK(QUEEN); b12.space = D8; b12.previousSpace = D8;
    b13.identifier = 28; b13.figure = SET_BLACK(KING); b13.space = E8; b13.previousSpace = E8; b14.identifier = 29; b14.figure = SET_BLACK(BISHOP); b14.space = F8; b14.previousSpace = F8;
    b15.identifier = 30; b15.figure = SET_BLACK(KNIGHT); b15.space = G8; b15.previousSpace = G8; b16.identifier = 31; b16.figure = SET_BLACK(ROOK); b16.space = H8; b16.previousSpace = H8;

    // initialize grabbed piece piece info
    grabbedPiece.figure = 0; grabbedPiece.identifier = EMPTY; grabbedPiece.space = Captured; grabbedPiece.previousSpace = Captured;

    // initialize the white pieceInfo as the first 16 in the vector
    pieceInfo.push_back(w1); pieceInfo.push_back(w2); pieceInfo.push_back(w3); pieceInfo.push_back(w4);
    pieceInfo.push_back(w5); pieceInfo.push_back(w6); pieceInfo.push_back(w7); pieceInfo.push_back(w8);
    pieceInfo.push_back(w9); pieceInfo.push_back(w10); pieceInfo.push_back(w11); pieceInfo.push_back(w12);
    pieceInfo.push_back(w13); pieceInfo.push_back(w14); pieceInfo.push_back(w15); pieceInfo.push_back(w16);

    // initialize the black pieceInfo as the last 16 in the vector
    pieceInfo.push_back(b1); pieceInfo.push_back(b2); pieceInfo.push_back(b3); pieceInfo.push_back(b4);
    pieceInfo.push_back(b5); pieceInfo.push_back(b6); pieceInfo.push_back(b7); pieceInfo.push_back(b8);
    pieceInfo.push_back(b9); pieceInfo.push_back(b10); pieceInfo.push_back(b11); pieceInfo.push_back(b12);
    pieceInfo.push_back(b13); pieceInfo.push_back(b14); pieceInfo.push_back(b15); pieceInfo.push_back(b16);

    // add the grabbed piece to the piece info vector
    pieceInfo.push_back(grabbedPiece);

    for (int i = 0; i < 32; i++)
    {
        pieceInfo[i].identifier = i;
    }
}

void Piece_c::clearGrabbedPieceLog()
{
    grabbedPieceLog.figure = 0;
    grabbedPieceLog.identifier = EMPTY;
    grabbedPieceLog.space = Captured;
    grabbedPieceLog.previousSpace = Captured;
}

void Piece_c::clearGrabbedPiece()
{
    pieceInfo[GRABBED_PIECE].figure = 0;
    pieceInfo[GRABBED_PIECE].identifier = EMPTY;
    pieceInfo[GRABBED_PIECE].space = Captured;
    pieceInfo[GRABBED_PIECE].previousSpace = Captured;
}

void Piece_c::printPieceInfo()
{
    for (auto piece : pieceInfo)
    {
        std::cout << "Piece Figure: " << piece.figure << " -- ";
        std::cout << "Piece Ident: " << piece.identifier << " -- ";
        std::cout << "Piece Space: " << piece.space << " -- ";
        std::cout << "Piece Prev Space: " << piece.previousSpace << std::endl << std:: endl;
    }
}

