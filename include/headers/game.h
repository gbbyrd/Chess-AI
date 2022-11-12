#pragma once

#include "../sdl2/SDL.h"
#include "../sdl2/SDL_image.h"
#include <iostream>
#include <vector>
#include <stack>

#include "board.h"

class Game_c: Board_c, Piece_c
{

    public:
        
        Game_c();
        ~Game_c();

        void run();

    protected:
        /* CRUCIAL VARIABLES FOR RENDERING AND INITIALIZING THE GAME */
        GameState_ec gameState_ec;
        SDL_Window* window; SDL_Renderer* renderer;

        /* SURFACES AND TEXTURES */
        SDL_Surface* titleSurface; SDL_Texture* titleTexture;
        SDL_Surface* boardSurface; SDL_Texture* boardTexture;
        /* piece surfaces */
        SDL_Surface* bPSurface; SDL_Surface* bRSurface; SDL_Surface* bNSurface; SDL_Surface* bBSurface; SDL_Surface* bQSurface; SDL_Surface* bKSurface;
        SDL_Surface* wPSurface; SDL_Surface* wRSurface; SDL_Surface* wNSurface; SDL_Surface* wBSurface; SDL_Surface* wQSurface; SDL_Surface* wKSurface;
        /* piece textures */
        SDL_Texture* wPTex; SDL_Texture* wRTex; SDL_Texture* wNTex; SDL_Texture* wBTex; SDL_Texture* wQTex; SDL_Texture* wKTex;
        SDL_Texture* bPTex; SDL_Texture* bRTex; SDL_Texture* bNTex; SDL_Texture* bBTex; SDL_Texture* bQTex; SDL_Texture* bKTex;
        /* surface and texture for the possible move square that highlights possible moves when you grab a piece */
        SDL_Surface* whiteSquareSurface; SDL_Texture* whiteSquareTex;

        /* RECTANGLE ORIGIN LOCATION VARIABLES */
        int boardTextureRectOriginx; 
        int boardTextureRectOriginy;
        int boardSpaceTextureRectOriginx; 
        int boardSpaceTextureRectOriginy; 
        /* heights and widths of various textures */
        int titleWidth;
        int titleHeight;
        int boardWidth;
        int boardHeight;
        int boardSpaceTextureRectWidth; 
        int boardSpaceTextureRectHeight;
        int boardSpaceWidth; 
        int boardSpaceHeight;

        /* RECTANGLES FOR THE PIECES, BOARD, POSSIBLE MOVES, AND TITLE */
        SDL_Rect srcTitleRect; 
        SDL_Rect dstTitleRect;
        SDL_Rect srcBoardRect; 
        SDL_Rect dstBoardRect;
        SDL_Rect srcPieceRect; 
        SDL_Rect srcPromotionPieceRect;
        SDL_Rect srcWhiteSquare; 
        SDL_Rect dstWhiteSquare;

        /* RECTANGLES FOR EACH SPACE ON THE BOARD */
        SDL_Rect A8Rect; SDL_Rect B8Rect; SDL_Rect C8Rect; SDL_Rect D8Rect; SDL_Rect E8Rect; SDL_Rect F8Rect; SDL_Rect G8Rect; SDL_Rect H8Rect;
        SDL_Rect A7Rect; SDL_Rect B7Rect; SDL_Rect C7Rect; SDL_Rect D7Rect; SDL_Rect E7Rect; SDL_Rect F7Rect; SDL_Rect G7Rect; SDL_Rect H7Rect;
        SDL_Rect A6Rect; SDL_Rect B6Rect; SDL_Rect C6Rect; SDL_Rect D6Rect; SDL_Rect E6Rect; SDL_Rect F6Rect; SDL_Rect G6Rect; SDL_Rect H6Rect;
        SDL_Rect A5Rect; SDL_Rect B5Rect; SDL_Rect C5Rect; SDL_Rect D5Rect; SDL_Rect E5Rect; SDL_Rect F5Rect; SDL_Rect G5Rect; SDL_Rect H5Rect;
        SDL_Rect A4Rect; SDL_Rect B4Rect; SDL_Rect C4Rect; SDL_Rect D4Rect; SDL_Rect E4Rect; SDL_Rect F4Rect; SDL_Rect G4Rect; SDL_Rect H4Rect;
        SDL_Rect A3Rect; SDL_Rect B3Rect; SDL_Rect C3Rect; SDL_Rect D3Rect; SDL_Rect E3Rect; SDL_Rect F3Rect; SDL_Rect G3Rect; SDL_Rect H3Rect;
        SDL_Rect A2Rect; SDL_Rect B2Rect; SDL_Rect C2Rect; SDL_Rect D2Rect; SDL_Rect E2Rect; SDL_Rect F2Rect; SDL_Rect G2Rect; SDL_Rect H2Rect;
        SDL_Rect A1Rect; SDL_Rect B1Rect; SDL_Rect C1Rect; SDL_Rect D1Rect; SDL_Rect E1Rect; SDL_Rect F1Rect; SDL_Rect G1Rect; SDL_Rect H1Rect;
        /* vector containing all of the board rectangles */
        std::vector<SDL_Rect*> boardSpaceRects;

        /* GAME WINDOW RENDERING */
        void initializeGameDisplay(const char* title, int displayLocX, int displayLocY, 
            int width, int height, Uint32 flags);
        void handleEvents();
        void gameLoop();

        /* ARTIFICIAL INTELLIGENCE */
        int maximizingPlayer;
        int minimizingPlayer;
        /* detemines which piece will be an artificial intelligence */
        int aiPlayer;
        bool isBothPlayerAI;
        /* this controls the difficulty of the ai */
        int setDepth; 
        int currentDepth;
        Move_s aiBestMove;
        Special_Move_s aiBestSpecialMove;
        int minimax(int depth, int maximizingPlayer);
        int getBoardEvaluation();
        void clearAiBestMove();
        void clearAiBestSpecialMove();

        /* METHODS AND VARIABLES FOR GETTING THE POSSIBLE MOVES */ 
        std::vector<std::list<Move_s>> possibleMoves;
        std::vector<std::list<Special_Move_s>> possibleSpecialMoves;
        void initializePossibleMoves(int setDepth);
        void initializePossibleSpecialMoves(int setDepth);
        void clearPossibleMoves();
        void clearPossibleSpecialMoves();
        void getPossibleMoves(int pieceIdentifier);
        /* get all possible moves for various pieces */
        void getPawnMoves(int piece, int from);
        void getSlidingPieceMoves(int piece, int from);
        void getKnightMoves(int piece, int from);
        void getKingMoves(int king, int from);
        /* creating, making, reversing, and verifying moves */
        Move_s createMove(int piece, int to, int from);
        Special_Move_s createSpecialMove(int piece1, int piece2, int from1, 
                                         int from2, int to1, int to2);
        void addMoveIfValid(Move_s move);
        void addSpecialMoveIfValid(Special_Move_s specialMove);
        void makeMove(Move_s move);
        void makeSpecialMove(Special_Move_s specialMove);
        void reverseMove();
        void clearPieceInfoLog(int depth);
        bool isInCheck(int friendlyColor);
        void updateMoveLog(Move_s move);
        void updateMoveLog(Special_Move_s specialMove);
        void clearPreviousPassant();
        void clearPieceInfoLog();
        void initializePieceInfoLog(int depth);

        /* CHECKMATE */
        bool isInCheckmate;
        SDL_Surface* checkmateSurface;
        SDL_Texture* checkmateTex;
        int checkmateBoxWidth;
        int checkmateBoxHeight;
        SDL_Rect srcCheckmateBox;
        SDL_Rect dstCheckmateBox;
        void checkForCheckmate();

        /* PAWN PROMOTION */
        bool isPromotionPossible; 
        int promotionPiece;
        /* rectangles and vector for pawn promotion */
        std::vector<SDL_Rect*> promotionRectVector;
        SDL_Rect dstPromoteToQueen; SDL_Rect dstPromoteToRook; SDL_Rect dstPromoteToBishop; SDL_Rect dstPromoteToKnight; 
        /* pawn promotion methods */
        void updatePromotionStatus(int piece);
        void clearPromotionStatus();
        void promotePawn(int figure);

        /* CLICK AND DRAG */
        static SDL_Point mousePosition;
        bool isClicked;
        SDL_Rect grabRect;
        int grabbedPieceInitLoc;
        int turn;
        void grabPiece();
        void dropPiece();

        /* DEGBUGGING */
        bool waitUntilPressContinue;
        int count;
        /* debug button */
        SDL_Texture* debugRectTex; SDL_Surface* debugRectSurface;
        int debugButtonHeight, debugButtonWidth;
        SDL_Rect srcDebugRect; SDL_Rect dstDebugRect; 
        /* print board button */
        SDL_Texture* printBoardRectTex; SDL_Surface* printBoardSurface;
        int printBoardButtonHeight, printBoardButtonWidth;
        SDL_Rect srcPrintBoardRect; SDL_Rect dstPrintBoardRect;
        /* print piece info button */
        SDL_Texture* printPieceInfoRectTex; SDL_Surface* printPieceInfoSurface;
        int printPieceInfoButtonHeight, printPieceInfoButtonWidth;
        SDL_Rect srcPrintPieceInfoRect; SDL_Rect dstPrintPieceInfoRect;
        /* toggle AI button */
        SDL_Texture* toggleAIRectTex; SDL_Surface* toggleAISurface;
        int toggleAIButtonHeight, toggleAIButtonWidth;
        SDL_Rect srcToggleAIRect; SDL_Rect dstToggleAIRect;
        void toggleAI();
        /* printing functions */
        void printMoveLog();

        /* UNDO FUNCTIONALITY */
        SDL_Texture* undoRectTex; SDL_Surface* undoRectSurface;
        int undoButtonHeight, undoButtonWidth; 
        SDL_Rect srcUndoRect; SDL_Rect dstUndoRect; 
        void logUndo();
        void undo();
        /* stacks for the undo functionality */
        std::stack<std::vector<PieceInfo_s>> undoPieceInfoStack;
        std::stack<std::vector<int>> undoBoardStack;
        std::stack<int> undoTurnStack;

        /* DIFFICULTY SELECT */
        /*difficulty banner */
        SDL_Texture* difficultyTex; SDL_Surface* difficultySurface;
        int difficultyHeight, difficultyWidth;                          // we will use the difficulty height for the other buttons
        SDL_Rect srcDifficulty; SDL_Rect dstDifficulty;
        /* very easy button */
        SDL_Texture* veryEasyTex; SDL_Surface* veryEasySurface;
        int veryEasyWidth;
        SDL_Rect srcVeryEasy; SDL_Rect dstVeryEasy;
        /* easy button */
        SDL_Texture* easyTex; SDL_Surface* easySurface;
        int easyWidth;
        SDL_Rect srcEasy; SDL_Rect dstEasy;
        /* medium button */
        SDL_Texture* mediumTex; SDL_Surface* mediumSurface;
        int mediumWidth;
        SDL_Rect srcMedium; SDL_Rect dstMedium;
        /* hard button */
        SDL_Texture* hardTex; SDL_Surface* hardSurface;
        int hardWidth;
        SDL_Rect srcHard; SDL_Rect dstHard;
        /* methods */
        void changeDifficulty(int newSetDepth);

        /* COMMON OPENINGS */

        /* These openings will be hard coded into the code
         * Once the standard responses to the openings have been completed,
         * the minimax function will take over from there.
         * 
         * A tree will be used for each opening. A custom data structure that holds move data and pointers
         * to the next path in the opening will be used.
         */

        /* openings */
        void ruyLopez();
        void italianGame();
        void sicilianDefence();
        void frenchDefence();
        void caroKannDefence();
        void pircDefence();
        void queensGambit();
        void indianDefence();
        void englishOpening();
        void retiOpening();
};
