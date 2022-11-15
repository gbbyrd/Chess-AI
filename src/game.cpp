#include <iostream>
#include <chrono>
#include <thread>

#include "../include/headers/game.h"

using namespace std::chrono; using namespace std::this_thread;

Game_c::Game_c(){
    /* CRUCIAL VARIABLES FOR RENDERING AND INITIALIZING THE GAME */
    gameState_ec = GameState_ec::PLAY;
    window = nullptr; renderer = nullptr;

    /* SURFACES AND TEXTURES */
    titleSurface = IMG_Load("res/Title.png");
    boardSurface = IMG_Load("res/Board.png");
    /* piece surfaces */
    bPSurface = IMG_Load("res/BP.png"); bRSurface = IMG_Load("res/BR.png"); 
    bNSurface = IMG_Load("res/BN.png"); bBSurface = IMG_Load("res/BB.png"); 
    bQSurface = IMG_Load("res/BQ.png"); bKSurface = IMG_Load("res/BK.png");
    wPSurface = IMG_Load("res/WP.png"); wRSurface = IMG_Load("res/WR.png"); 
    wNSurface = IMG_Load("res/WN.png"); wBSurface = IMG_Load("res/WB.png"); 
    wQSurface = IMG_Load("res/WQ.png"); wKSurface = IMG_Load("res/WK.png");
    /* surface for squares used to show possible moves */
    whiteSquareSurface = IMG_Load("res/WhiteSquare.png");

    /* RECTANGLE ORIGIN AND LOCATION VARIABLES */
    /* change the below two values to shift the location of everything together */
    boardTextureRectOriginx = 25; 
    boardTextureRectOriginy = 25;
    boardSpaceTextureRectOriginx = boardTextureRectOriginx + 45; 
    boardSpaceTextureRectOriginy = boardTextureRectOriginy + 24;
    /* heights and widths of various textures */
    titleWidth = 403;
    titleHeight = 812; 
    boardWidth = 1360;
    boardHeight = 1372;
    boardSpaceTextureRectWidth = 100; 
    boardSpaceTextureRectHeight = 100; 
    boardSpaceWidth = 119; 
    boardSpaceHeight = 118;

    /* RECTANGLES FOR THE PIECES, BOARD, POSSIBLE MOVES, AND TITLE */
    srcTitleRect = {0, 0, titleHeight, titleWidth}; 
    dstTitleRect = {boardTextureRectOriginx + 1040, 
        boardTextureRectOriginy, titleHeight, titleWidth};
    srcBoardRect = {0, 0, boardWidth, boardHeight}; 
    dstBoardRect = {boardTextureRectOriginx, boardTextureRectOriginy, 
        1000, 1000};
    srcPieceRect = {0, 0, boardSpaceTextureRectWidth, boardSpaceTextureRectHeight};
    srcPromotionPieceRect = {0, 0, boardSpaceTextureRectWidth / 2, 
        boardSpaceTextureRectHeight / 2};
    srcWhiteSquare = {80, 80, 100, 100};

    /* RECTANGLES FOR EACH SPACE ON THE BOARD */
    boardSpaceRects.push_back(&A8Rect); boardSpaceRects.push_back(&B8Rect); 
    boardSpaceRects.push_back(&C8Rect); boardSpaceRects.push_back(&D8Rect); 
    boardSpaceRects.push_back(&E8Rect); boardSpaceRects.push_back(&F8Rect); 
    boardSpaceRects.push_back(&G8Rect); boardSpaceRects.push_back(&H8Rect);
    boardSpaceRects.push_back(&A7Rect); boardSpaceRects.push_back(&B7Rect); 
    boardSpaceRects.push_back(&C7Rect); boardSpaceRects.push_back(&D7Rect); 
    boardSpaceRects.push_back(&E7Rect); boardSpaceRects.push_back(&F7Rect); 
    boardSpaceRects.push_back(&G7Rect); boardSpaceRects.push_back(&H7Rect);
    boardSpaceRects.push_back(&A6Rect); boardSpaceRects.push_back(&B6Rect); 
    boardSpaceRects.push_back(&C6Rect); boardSpaceRects.push_back(&D6Rect); 
    boardSpaceRects.push_back(&E6Rect); boardSpaceRects.push_back(&F6Rect); 
    boardSpaceRects.push_back(&G6Rect); boardSpaceRects.push_back(&H6Rect);
    boardSpaceRects.push_back(&A5Rect); boardSpaceRects.push_back(&B5Rect); 
    boardSpaceRects.push_back(&C5Rect); boardSpaceRects.push_back(&D5Rect); 
    boardSpaceRects.push_back(&E5Rect); boardSpaceRects.push_back(&F5Rect); 
    boardSpaceRects.push_back(&G5Rect); boardSpaceRects.push_back(&H5Rect);
    boardSpaceRects.push_back(&A4Rect); boardSpaceRects.push_back(&B4Rect); 
    boardSpaceRects.push_back(&C4Rect); boardSpaceRects.push_back(&D4Rect); 
    boardSpaceRects.push_back(&E4Rect); boardSpaceRects.push_back(&F4Rect); 
    boardSpaceRects.push_back(&G4Rect); boardSpaceRects.push_back(&H4Rect);
    boardSpaceRects.push_back(&A3Rect); boardSpaceRects.push_back(&B3Rect); 
    boardSpaceRects.push_back(&C3Rect); boardSpaceRects.push_back(&D3Rect); 
    boardSpaceRects.push_back(&E3Rect); boardSpaceRects.push_back(&F3Rect); 
    boardSpaceRects.push_back(&G3Rect); boardSpaceRects.push_back(&H3Rect);
    boardSpaceRects.push_back(&A2Rect); boardSpaceRects.push_back(&B2Rect); 
    boardSpaceRects.push_back(&C2Rect); boardSpaceRects.push_back(&D2Rect); 
    boardSpaceRects.push_back(&E2Rect); boardSpaceRects.push_back(&F2Rect); 
    boardSpaceRects.push_back(&G2Rect); boardSpaceRects.push_back(&H2Rect);
    boardSpaceRects.push_back(&A1Rect); boardSpaceRects.push_back(&B1Rect); 
    boardSpaceRects.push_back(&C1Rect); boardSpaceRects.push_back(&D1Rect); 
    boardSpaceRects.push_back(&E1Rect); boardSpaceRects.push_back(&F1Rect); 
    boardSpaceRects.push_back(&G1Rect); boardSpaceRects.push_back(&H1Rect);
    boardSpaceRects.push_back(&grabRect);
    /* below algorithm sets the destination rectangle values for each space on the board */
    int iteratorx = 0; int iteratory = 0;
    for (auto const& boardSpace : boardSpaceRects)
    {
        *boardSpace = {boardSpaceTextureRectOriginx + iteratorx * boardSpaceWidth,
            boardSpaceTextureRectOriginy + iteratory * boardSpaceHeight, 
            boardSpaceTextureRectWidth, boardSpaceTextureRectHeight};

        iteratorx++;

        if (iteratorx == 8)
        {
            iteratorx = 0;
            iteratory++;
        }
    }

    /* BUTTON HIGHLIGHT */
    buttonHighlightSurface = IMG_Load("res/ButtonHighlight.png");
    srcButtonHighlightRect = {0, 0, 670, 419};

    /* ARTIFICIAL INTELLIGENCE SELECTION */
    /* ai selector banner */
    aiSelectorSurface = IMG_Load("res/ai_selector.png");
    aiSelectorOriginX = boardTextureRectOriginx + 1040 + 150;
    aiSelectorOriginY = boardTextureRectOriginy + 406 + 10;
    aiSelectorHeight = 128; aiSelectorWidth = 520;
    srcAiSelectorRect = {0, 0, aiSelectorWidth, aiSelectorHeight};
    dstAiSelectorRect = {aiSelectorOriginX,  
        aiSelectorOriginY, aiSelectorWidth, aiSelectorHeight};
    /* "black" button */
    blackButtonSurface = IMG_Load("res/Black.png");
    blackButtonOriginX = aiSelectorOriginX + 27;
    blackButtonOriginY = aiSelectorOriginY + aiSelectorHeight + 10; 
    blackButtonHeight = 89; blackButtonWidth = 215;
    srcBlackButtonRect = {0, 0, blackButtonWidth, blackButtonWidth};
    dstBlackButtonRect = {blackButtonOriginX, blackButtonOriginY,
        blackButtonWidth, blackButtonHeight};
    /* "black" button highlight rect */
    dstBlackButtonHighlightRect = {blackButtonOriginX - 5, 
        blackButtonOriginY - 5, blackButtonWidth + 10, blackButtonHeight + 10};
    /* "white" button */
    whiteButtonSurface = IMG_Load("res/White.png");
    whiteButtonOriginX = blackButtonOriginX + blackButtonWidth + 35;
    whiteButtonOriginY = blackButtonOriginY;
    whiteButtonHeight = blackButtonHeight; whiteButtonWidth = blackButtonWidth;
    srcWhiteButtonRect = {0, 0, whiteButtonWidth, whiteButtonHeight};
    dstWhiteButtonRect = {whiteButtonOriginX, whiteButtonOriginY,
        whiteButtonWidth, whiteButtonHeight};
    /* "white" button highlight rect */
    dstWhiteButtonHighlightRect = {whiteButtonOriginX - 5, 
        whiteButtonOriginY - 5, whiteButtonWidth + 10, whiteButtonHeight + 10};

    /* EXIT BUTTON */
    exitButtonSurface = IMG_Load("res/Exit.png");
    exitButtonOriginX = boardTextureRectOriginx + 1040 + 620;
    exitButtonOriginY = boardTextureRectOriginy + titleHeight + 100;
    exitButtonHeight = 87; exitButtonWidth = 185;
    srcExitButtonRect = {0, 0, exitButtonWidth, exitButtonHeight};
    dstExitButtonRect = {exitButtonOriginX, exitButtonOriginY, exitButtonWidth,
        exitButtonHeight};
    dstExitButtonHighlightRect = {exitButtonOriginX - 5, exitButtonOriginY - 5,
        exitButtonWidth + 10, exitButtonHeight + 10};
    
    /* ARTIFICIAL INTELLIGENCE */
    maximizingPlayer = WHITE; 
    minimizingPlayer = BLACK;
    /* detemines which piece will be an artificial intelligence */
    aiPlayer = 1; 
    isBothPlayerAI = false;
    isWhiteAi = false;
    isBlackAi = false;
    /* change "setDepth" to change the amount of moves ahead the AI looks
     * this effectively changes the difficulty of the AI
     */
    setDepth = 4; 
    currentDepth = setDepth;
    clearAiBestMove();
    clearAiBestSpecialMove();
    clearAiBestPawnPromMove();

    /* METHODS AND VARIABLES FOR GETTING THE POSSIBLE MOVES */
    clearPossibleMoves();
    clearPossibleSpecialMoves();
    clearPossiblePawnPromMoves();
    initializePossibleMoves(setDepth);
    initializePossibleSpecialMoves(setDepth);
    initializePossiblePawnPromMoves(setDepth);
    initializePieceInfoLog(setDepth);
    
    /* CLICK AND DRAG */
    isClicked = false;
    turn = WHITE;         

    /* CHECKMATE */
    isInCheckmate = false;
    checkmateSurface = IMG_Load("res/Checkmate.png");
    checkmateBoxWidth = 504;
    checkmateBoxHeight = 151;
    srcCheckmateBox = {0, 0, checkmateBoxWidth, checkmateBoxHeight};
    dstCheckmateBox = {boardTextureRectOriginx + 260, 
                       boardTextureRectOriginy + 400, 
                       checkmateBoxWidth, checkmateBoxHeight};

    /* PAWN PROMOTION */
    isPromotionPossible = false; 
    promotionPiece = EMPTY;
    /* initialize vector for pawn promotion */
    promotionRectVector.push_back(&dstPromoteToQueen);
    promotionRectVector.push_back(&dstPromoteToRook);  
    promotionRectVector.push_back(&dstPromoteToBishop);
    promotionRectVector.push_back(&dstPromoteToKnight);

    /* DEBUGGING */
    waitUntilPressContinue = false;
    count = 0;
    /* degub button */
    debugRectSurface = IMG_Load("res/Debug.png");
    debugButtonHeight = 83; debugButtonWidth = 219;
    srcDebugRect = {0, 0, debugButtonWidth, debugButtonHeight};
    dstDebugRect = {boardTextureRectOriginx + 1040,
        boardTextureRectOriginy + titleHeight + 10 + debugButtonHeight + 10,
        debugButtonWidth, debugButtonHeight};
    /* print board button */
    printBoardSurface = IMG_Load("res/Print_Board.png");
    printBoardButtonHeight = 46; printBoardButtonWidth = 203;
    srcPrintBoardRect = {0, 0, printBoardButtonWidth, printBoardButtonHeight};
    dstPrintBoardRect = {boardTextureRectOriginx + 1040,
        boardTextureRectOriginy + 600,
        printBoardButtonWidth, printBoardButtonHeight};
    /* print piece info button */
    printPieceInfoSurface = IMG_Load("res/Print_PieceInfo.png");
    printPieceInfoButtonHeight = 45; printPieceInfoButtonWidth = 244;
    srcPrintPieceInfoRect = {0, 0, printPieceInfoButtonWidth, printPieceInfoButtonHeight};
    dstPrintPieceInfoRect = {boardTextureRectOriginx + 1040,
        boardTextureRectOriginy + 550,
        printPieceInfoButtonWidth, printPieceInfoButtonHeight};
    /* toggle AI button */
    toggleAISurface = IMG_Load("res/Toggle_AI.png");
    toggleAIButtonHeight = 48; toggleAIButtonWidth = 162;
    srcToggleAIRect = {0, 0, toggleAIButtonWidth, toggleAIButtonHeight};
    dstToggleAIRect = {boardTextureRectOriginx + 1040,
        boardTextureRectOriginy + 650,
        toggleAIButtonWidth, toggleAIButtonHeight};

    /* UNDO FUNCTIONALITY */
    undoRectSurface = IMG_Load("res/Undo.png");
    undoButtonHeight = 83; undoButtonWidth = 187;
    srcUndoRect = {0, 0, undoButtonWidth, undoButtonHeight};
    dstUndoRect = {boardTextureRectOriginx + 1040, 
        boardTextureRectOriginy + titleHeight + 10,
        undoButtonWidth, undoButtonHeight};

    /* DIFFICULTY SELECT */
    /* difficulty banner */
    difficultySurface = IMG_Load("res/Difficulty.png");
    difficultyHeight = 58; difficultyWidth = 242;
    srcDifficulty = {0, 0, difficultyWidth, difficultyHeight};
    dstDifficulty = {boardTextureRectOriginx + 1040,
        boardTextureRectOriginy + 450,
        difficultyWidth, difficultyHeight};
    /* very easy button */
    veryEasySurface = IMG_Load("res/Very_Easy.png");
    veryEasyWidth = 232;
    srcVeryEasy = {0, 0, veryEasyWidth, difficultyHeight};
    dstVeryEasy = {boardTextureRectOriginx + 1040,
        boardTextureRectOriginy + 450 + difficultyHeight + 10,
        veryEasyWidth, difficultyHeight};
    /* easy button */
    easySurface = IMG_Load("res/Easy.png");
    easyWidth = 119;
    srcEasy = {0, 0, easyWidth, difficultyHeight};
    dstEasy = {boardTextureRectOriginx + 1040 + veryEasyWidth + 10,
        boardTextureRectOriginy + 450 + difficultyHeight + 10,
        easyWidth, difficultyHeight};
    /* medium button */
    mediumSurface = IMG_Load("res/Medium.png");
    mediumWidth = 202;
    srcMedium = {0, 0, mediumWidth, difficultyHeight};
    dstMedium = {boardTextureRectOriginx + 1040 + veryEasyWidth + easyWidth + 20,
        boardTextureRectOriginy + 450 + difficultyHeight + 10,
        mediumWidth, difficultyHeight};
    /* hard button */
    hardSurface = IMG_Load("res/Hard.png");
    hardWidth = 139;
    srcHard = {0, 0, hardWidth, difficultyHeight};
    dstHard = {boardTextureRectOriginx + 1040 + veryEasyWidth + easyWidth + mediumWidth + 30,
        boardTextureRectOriginy + 450 + difficultyHeight + 10,
        hardWidth, difficultyHeight};

    /* COMMON OPENINGS */
    MoveNode ruyLopez(1);
    MoveNode italianGame(1);
    MoveNode sicilianDefence(1);
    MoveNode frenchDefence(1);
    MoveNode caroKannDefence(1);
    MoveNode pircDefence(1);
    MoveNode queensGambit(1);
    MoveNode indianDefence(1);
    MoveNode englishOpening(1);
    MoveNode retiOpening(1);
}

SDL_Point Game_c::mousePosition = {0, 0};

Game_c::~Game_c(){};

void Game_c::run() {
    initializeGameDisplay("ByrdAI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1920, 1200, SDL_WINDOW_FULLSCREEN_DESKTOP);
    gameLoop();
}

/* GAME WINDOW RENDERING */

void Game_c::initializeGameDisplay(const char* title, int displayLocX, int displayLocY, 
            int width, int height, Uint32 flags){

    // initialize window and renderer to display game window and graphics
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(title, displayLocX, displayLocY, width, height, flags);
    renderer = SDL_CreateRenderer(window, -1, 0);

    // initialize game textures and free their respective surfaces

    titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface); 
    SDL_FreeSurface(titleSurface);
    boardTexture = SDL_CreateTextureFromSurface(renderer, boardSurface); 
    SDL_FreeSurface(boardSurface);
    wPTex = SDL_CreateTextureFromSurface(renderer, wPSurface); 
    SDL_FreeSurface(wPSurface);
    bPTex = SDL_CreateTextureFromSurface(renderer, bPSurface); 
    SDL_FreeSurface(bPSurface);
    wRTex = SDL_CreateTextureFromSurface(renderer, wRSurface); 
    SDL_FreeSurface(wRSurface);
    bRTex = SDL_CreateTextureFromSurface(renderer, bRSurface); 
    SDL_FreeSurface(bRSurface);
    wNTex = SDL_CreateTextureFromSurface(renderer, wNSurface); 
    SDL_FreeSurface(wNSurface);
    bNTex = SDL_CreateTextureFromSurface(renderer, bNSurface); 
    SDL_FreeSurface(bNSurface);
    wBTex = SDL_CreateTextureFromSurface(renderer, wBSurface); 
    SDL_FreeSurface(wBSurface);
    bBTex = SDL_CreateTextureFromSurface(renderer, bBSurface); 
    SDL_FreeSurface(bBSurface);
    wQTex = SDL_CreateTextureFromSurface(renderer, wQSurface); 
    SDL_FreeSurface(wQSurface);
    bQTex = SDL_CreateTextureFromSurface(renderer, bQSurface); 
    SDL_FreeSurface(bQSurface);
    wKTex = SDL_CreateTextureFromSurface(renderer, wKSurface); 
    SDL_FreeSurface(wKSurface);
    bKTex = SDL_CreateTextureFromSurface(renderer, bKSurface); 
    SDL_FreeSurface(bKSurface);
    whiteSquareTex = SDL_CreateTextureFromSurface(renderer, whiteSquareSurface); 
    SDL_FreeSurface(whiteSquareSurface);

    /* BUTTON HIGHLIGHT */
    buttonHighlightTex = SDL_CreateTextureFromSurface(renderer, buttonHighlightSurface);
    SDL_FreeSurface(buttonHighlightSurface);

    /* AI SELECTOR */
    aiSelectorTex = SDL_CreateTextureFromSurface(renderer, aiSelectorSurface);
    SDL_FreeSurface(aiSelectorSurface);
    blackButtonTex = SDL_CreateTextureFromSurface(renderer, blackButtonSurface);
    SDL_FreeSurface(blackButtonSurface);
    whiteButtonTex = SDL_CreateTextureFromSurface(renderer, whiteButtonSurface);
    SDL_FreeSurface(whiteButtonSurface);

    /* EXIT BUTTON */
    exitButtonTex = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);
    SDL_FreeSurface(exitButtonSurface);

    /* CHECKMATE */
    checkmateTex = SDL_CreateTextureFromSurface(renderer, checkmateSurface); 
    SDL_FreeSurface(checkmateSurface);

    /* UNDO FUNCTIONALITY */
    undoRectTex = SDL_CreateTextureFromSurface(renderer, undoRectSurface); 
    SDL_FreeSurface(undoRectSurface);

    /* DEBUGGING */
    /* debug button */
    debugRectTex = SDL_CreateTextureFromSurface(renderer, debugRectSurface); 
    SDL_FreeSurface(debugRectSurface);
    /* print board button */
    printBoardRectTex = SDL_CreateTextureFromSurface(renderer, printBoardSurface); 
    SDL_FreeSurface(printBoardSurface);
    /* print piece info button */
    printPieceInfoRectTex = SDL_CreateTextureFromSurface(renderer, printPieceInfoSurface); 
    SDL_FreeSurface(printPieceInfoSurface);
    /* toggle AI button */
    toggleAIRectTex = SDL_CreateTextureFromSurface(renderer, toggleAISurface); 
    SDL_FreeSurface(toggleAISurface);

    /* DIFFICULTY SELECT */
    difficultyTex = SDL_CreateTextureFromSurface(renderer, difficultySurface); 
    SDL_FreeSurface(difficultySurface);
    veryEasyTex = SDL_CreateTextureFromSurface(renderer, veryEasySurface); 
    SDL_FreeSurface(veryEasySurface);
    easyTex = SDL_CreateTextureFromSurface(renderer, easySurface); 
    SDL_FreeSurface(easySurface);
    mediumTex = SDL_CreateTextureFromSurface(renderer, mediumSurface); 
    SDL_FreeSurface(mediumSurface);
    hardTex = SDL_CreateTextureFromSurface(renderer, hardSurface); 
    SDL_FreeSurface(hardSurface);
}

void Game_c::handleEvents(){

    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            gameState_ec = GameState_ec::EXIT;
            break;
        
        case SDL_MOUSEMOTION:
            mousePosition = {event.motion.x, event.motion.y};
            grabRect.x = mousePosition.x - boardSpaceTextureRectWidth/2;
            grabRect.y = mousePosition.y - boardSpaceTextureRectHeight/2;
            break;
        
        case SDL_MOUSEBUTTONUP:
        {
            if (!isClicked || event.button.button != SDL_BUTTON_LEFT)
            {
                break;
            }
            isClicked = false;
            dropPiece();
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            if (!isPromotionPossible)
            {
                if (isClicked || event.button.button != SDL_BUTTON_LEFT)
                {
                    break;
                }
                isClicked = true;
                grabPiece();

                if (SDL_PointInRect(&mousePosition, &dstWhiteButtonRect))
                {
                    isWhiteAi = isWhiteAi ? false : true;
                    isBothPlayerAI = isWhiteAi && isBlackAi ? true : false;
                    if (isBlackAi && !isWhiteAi)
                        aiPlayer = BLACK;
                    else if (!isBlackAi && isWhiteAi)
                        aiPlayer = WHITE;
                    else
                        aiPlayer = 1;
                }
                if (SDL_PointInRect(&mousePosition, &dstBlackButtonRect))
                {
                    isBlackAi = isBlackAi ? false : true;
                    isBothPlayerAI = isWhiteAi && isBlackAi ? true : false;
                    if (isBlackAi && !isWhiteAi)
                        aiPlayer = BLACK;
                    else if (!isBlackAi && isWhiteAi)
                        aiPlayer = WHITE;
                    else
                        aiPlayer = 1;
                }
                if (SDL_PointInRect(&mousePosition, &dstExitButtonRect))
                {
                    gameState_ec = GameState_ec::EXIT;
                    break;
                }

                /* DEBUGGING */
                /* this is used as a breakpoint so you can start 
                debugging and adding breakpoints at will */
                if (SDL_PointInRect(&mousePosition, &dstDebugRect))
                    int debug = 0;                                              
                if (SDL_PointInRect(&mousePosition, &dstPrintBoardRect))
                    printBoard(board);
                if (SDL_PointInRect(&mousePosition, &dstPrintPieceInfoRect))
                    printPieceInfo();
                if (SDL_PointInRect(&mousePosition, &dstToggleAIRect))
                    toggleAI();
                /* UNDO FUNCTIONALITY */
                if (SDL_PointInRect(&mousePosition, &dstUndoRect))
                    undo();
                /* DIFFICULTY SELECT */
                // if (SDL_PointInRect(&mousePosition, &dstVeryEasy))
                // {
                //     changeDifficulty(1);
                //     std::cout << "Difficulty: Very Easy";
                // }
                // if (SDL_PointInRect(&mousePosition, &dstEasy))
                // {
                //     changeDifficulty(2);
                //     std::cout << "Difficulty: Easy";
                // }
                // if (SDL_PointInRect(&mousePosition, &dstMedium))
                // {
                //     changeDifficulty(3);
                //     std::cout << "Difficulty: Medium";
                // }
                // if (SDL_PointInRect(&mousePosition, &dstHard))
                // {
                //     changeDifficulty(4);
                //     std::cout << "Difficulty: Hard";
                // }
                break;
            }
            if (isClicked || event.button.button != SDL_BUTTON_LEFT)
            {
                break;
            }
            promotePawn(moveLog.piece1);
            break;
        }
    }
}

void Game_c::gameLoop(){

    while(gameState_ec == GameState_ec::PLAY)
    {
        if (isInCheckmate)
        {
            SDL_RenderCopy(renderer, checkmateTex, &srcCheckmateBox, 
                &dstCheckmateBox);
            SDL_RenderPresent(renderer);
        }

        while (isInCheckmate)
        {
            handleEvents();
        }

        if (turn == aiPlayer || isBothPlayerAI)
        {
            minimax(setDepth, turn);
            if (aiBestMove.piece != EMPTY)
            {
                makeMove(aiBestMove);
            }
            else if (aiBestSpecialMove.piece1 != EMPTY)
            {
                makeSpecialMove(aiBestSpecialMove);
            }
            else if (aiBestPawnPromMove.piece != EMPTY)
            {
                makePawnPromMove(aiBestPawnPromMove);
            }
            else
            {
                std::cout << "Checkmate! Congratulations! " << std::endl;
            }
            turn ^= BLACK;
            clearPossibleMoves();
            clearPossibleSpecialMoves();
            clearPossiblePawnPromMoves();
            printBoard(board);
            logUndo();
            checkForCheckmate();
            if (isBothPlayerAI) 
            {
                sleep_for(milliseconds(500));
            }
        }

        handleEvents();
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, titleTexture, &srcTitleRect, &dstTitleRect);
        SDL_RenderCopy(renderer, boardTexture, &srcBoardRect, &dstBoardRect);
        // SDL_RenderCopy(renderer, undoRectTex, &srcUndoRect, &dstUndoRect);

        /* BUTTON HIGHLIGHTS */
        /* "black" button */
        if (SDL_PointInRect(&mousePosition, &dstBlackButtonRect) || isBlackAi)
        {
            SDL_RenderCopy(renderer, buttonHighlightTex, &srcButtonHighlightRect,
                &dstBlackButtonHighlightRect);
        }
        /* "white" button */
        if (SDL_PointInRect(&mousePosition, &dstWhiteButtonRect) || isWhiteAi)
        {
            SDL_RenderCopy(renderer, buttonHighlightTex, &srcButtonHighlightRect,
                &dstWhiteButtonHighlightRect);
        }
        /* "exit" button */
        if (SDL_PointInRect(&mousePosition, &dstExitButtonRect))
        {
            SDL_RenderCopy(renderer, buttonHighlightTex, &srcButtonHighlightRect,
                &dstExitButtonHighlightRect);
        }

        /* AI SELECTOR */
        SDL_RenderCopy(renderer, aiSelectorTex, &srcAiSelectorRect, &dstAiSelectorRect);
        SDL_RenderCopy(renderer, blackButtonTex, &srcBlackButtonRect, &dstBlackButtonRect);
        SDL_RenderCopy(renderer, whiteButtonTex, &srcWhiteButtonRect, &dstWhiteButtonRect);
        /* EXIT BUTTON */
        SDL_RenderCopy(renderer, exitButtonTex, &srcExitButtonRect, &dstExitButtonRect);
        /* DEBUGGING */
        // SDL_RenderCopy(renderer, debugRectTex, &srcDebugRect, &dstDebugRect);
        // SDL_RenderCopy(renderer, printBoardRectTex, &srcPrintBoardRect, &dstPrintBoardRect);
        // SDL_RenderCopy(renderer, printPieceInfoRectTex, &srcPrintPieceInfoRect, &dstPrintPieceInfoRect);
        // SDL_RenderCopy(renderer, toggleAIRectTex, &srcToggleAIRect, &dstToggleAIRect);
        /* DIFFICULTY SELECT */
        // SDL_RenderCopy(renderer, difficultyTex, &srcDifficulty, &dstDifficulty);
        // SDL_RenderCopy(renderer, veryEasyTex, &srcVeryEasy, &dstVeryEasy);
        // SDL_RenderCopy(renderer, easyTex, &srcEasy, &dstEasy);
        // SDL_RenderCopy(renderer, mediumTex, &srcMedium, &dstMedium);
        // SDL_RenderCopy(renderer, hardTex, &srcHard, &dstHard);

        for (auto const& move : possibleMoves[setDepth])
        {
            SDL_RenderCopy(renderer, whiteSquareTex, &srcWhiteSquare, 
                boardSpaceRects[move.to]);
        }

        for (auto const& specialMove : possibleSpecialMoves[setDepth])
        {
            SDL_RenderCopy(renderer, whiteSquareTex, &srcWhiteSquare, 
                boardSpaceRects[specialMove.to1]);
        }

        /* we do not need to include the possible pawn promotion moves here
         * as that is only used for the artificial intelligence functionality
         */

        for (auto const& piece : pieceInfo)
        {
            if (piece.space != Captured)
            {
                switch (piece.figure & 95 /* pull the type, color, and 
                    passant info of each piece */)
            {
                case PAWN:
                    SDL_RenderCopy(renderer, wPTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;

                case PASSANT| PAWN:
                    /* SDL_RenderCopy(renderer, whiteSquareTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]); */
                    SDL_RenderCopy(renderer, wPTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;

                case BLACK | PAWN:
                    SDL_RenderCopy(renderer, bPTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;

                case PASSANT | BLACK | PAWN:
                    // SDL_RenderCopy(renderer, whiteSquareTex, &srcPieceRect, 
                        // boardSpaceRects[piece.space]);
                    SDL_RenderCopy(renderer, bPTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;
                    
                case ROOK:
                    SDL_RenderCopy(renderer, wRTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;

                case BLACK | ROOK:
                    SDL_RenderCopy(renderer, bRTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;

                case KNIGHT:
                    SDL_RenderCopy(renderer, wNTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;

                case BLACK | KNIGHT:
                    SDL_RenderCopy(renderer, bNTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;
                
                case BISHOP:
                    SDL_RenderCopy(renderer, wBTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;

                case BLACK | BISHOP:
                    SDL_RenderCopy(renderer, bBTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;

                case QUEEN:
                    SDL_RenderCopy(renderer, wQTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;

                case BLACK | QUEEN:
                    SDL_RenderCopy(renderer, bQTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;

                case KING:
                    SDL_RenderCopy(renderer, wKTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;

                case BLACK | KING:
                    SDL_RenderCopy(renderer, bKTex, &srcPieceRect, 
                        boardSpaceRects[piece.space]);
                    break;
                
                default:
                    break;
                }
            }
        }

        if (isPromotionPossible)
        {
            if ((pieceInfo[promotionPiece].figure & BLACK) == BLACK)
            {
                SDL_RenderCopy(renderer, bQTex, &srcPieceRect, promotionRectVector[0]);
                SDL_RenderCopy(renderer, bRTex, &srcPieceRect, promotionRectVector[1]);
                SDL_RenderCopy(renderer, bBTex, &srcPieceRect, promotionRectVector[2]);
                SDL_RenderCopy(renderer, bNTex, &srcPieceRect, promotionRectVector[3]);
            }
            else
            {
                SDL_RenderCopy(renderer, wQTex, &srcPieceRect, promotionRectVector[0]);
                SDL_RenderCopy(renderer, wRTex, &srcPieceRect, promotionRectVector[1]);
                SDL_RenderCopy(renderer, wBTex, &srcPieceRect, promotionRectVector[2]);
                SDL_RenderCopy(renderer, wNTex, &srcPieceRect, promotionRectVector[3]);
            }
        }

        SDL_RenderPresent(renderer);
    }
}

/* ARTIFICIAL INTELLIGENCE */

int Game_c::minimax(int depth, int minimaxTurn)
{
    if (depth == 0)
    {
        return getBoardEvaluation();
    }

    currentDepth = depth;

    int boardEval;
    int maxEval = -10000000; int minEval = 10000000;

    int start = (minimaxTurn == WHITE) ? 0 : 16;
    int end = (minimaxTurn == WHITE) ? 16 : 32;

    if (minimaxTurn == maximizingPlayer)
    {
        /* clear out the possible moves lists */
        possibleMoves[currentDepth].clear();
        possibleSpecialMoves[currentDepth].clear();
        possiblePawnPromMoves[currentDepth].clear();
        for (int piece = start; piece < end; piece++)
        {
            if (pieceInfo[piece].space != Captured)
                getPossibleMoves(piece);
        }

        for (auto const& move : possibleMoves[currentDepth])
        {
            makeMove(move);
            // if (pieceInfo[move.piece].figure & FIGURE == PAWN && 
                // (move.to/8 == 7 || move.to/8 == 0))
            // {
            //     pieceInfo[move.piece].figure = CLEAR_FIGURE(pieceInfo[move.piece].figure);
            //     pieceInfo[move.piece].figure = pieceInfo[move.piece].figure & QUEEN;
            // }
            int boardEval = minimax(depth - 1, minimizingPlayer);
            if (boardEval <= maxEval)
            {
                currentDepth = depth;
                reverseMove();
                continue;
            }
            
            if (depth == setDepth)
            {
                aiBestMove = move;
                clearAiBestSpecialMove();
                clearAiBestPawnPromMove();
            }
            maxEval = boardEval;
            currentDepth = depth;
            reverseMove();
        }

        for (auto const& specialMove : possibleSpecialMoves[currentDepth])
        {
            makeSpecialMove(specialMove);
            int boardEval = minimax(depth - 1, minimizingPlayer);
            if (boardEval <= maxEval)
            {
                currentDepth = depth;
                reverseMove();
                continue;
            }
            
            if (depth == setDepth)
            {
                aiBestSpecialMove = specialMove;
                clearAiBestMove();
                clearAiBestPawnPromMove();
            }
            maxEval = boardEval;
            currentDepth = depth;
            reverseMove();
        }

        for (auto const& pawnPromMove : possiblePawnPromMoves[currentDepth])
        {
            makePawnPromMove(pawnPromMove);
            int boardEval = minimax(depth - 1, minimizingPlayer);
            if (boardEval <= maxEval)
            {
                currentDepth = depth;
                reverseMove();
                continue;
            }

            if (depth == setDepth);
            {
                aiBestPawnPromMove = pawnPromMove;
                clearAiBestMove();
                clearAiBestSpecialMove();
            }
            maxEval = boardEval;
            currentDepth = depth;
            reverseMove();
        }

        return maxEval;
    }
    else
    {
        /* clear out the possible moves lists */
        possibleMoves[currentDepth].clear();
        possibleSpecialMoves[currentDepth].clear();
        possiblePawnPromMoves[currentDepth].clear();
        for (int piece = start; piece < end; piece++)
        {
            if (pieceInfo[piece].space != Captured)
                getPossibleMoves(piece);
        }

        for (auto const& move : possibleMoves[currentDepth])
        {
            makeMove(move);
            // if (pieceInfo[move.piece].figure & FIGURE == PAWN && 
                // (move.to/8 == 7 || move.to/8 == 0))
            // {
            //     pieceInfo[move.piece].figure = CLEAR_FIGURE(pieceInfo[move.piece].figure);
            //     pieceInfo[move.piece].figure = pieceInfo[move.piece].figure & QUEEN;
            // }
            int boardEval = minimax(depth - 1, maximizingPlayer);
            if (boardEval >= minEval)
            {
                currentDepth = depth;
                reverseMove();
                continue;
            }
            
            if (depth == setDepth)
            {
                aiBestMove = move;
                clearAiBestSpecialMove();
                clearAiBestPawnPromMove();
            }
            minEval = boardEval;
            currentDepth = depth;
            reverseMove();
        }

        for (auto const& specialMove : possibleSpecialMoves[currentDepth])
        {
            makeSpecialMove(specialMove);
            int boardEval = minimax(depth - 1, maximizingPlayer);
            if (boardEval >= minEval)
            {
                currentDepth = depth;
                reverseMove();
                continue;
            }
            
            if (depth == setDepth)
            {
                aiBestSpecialMove = specialMove;
                clearAiBestMove();
                clearAiBestPawnPromMove();
            }
            minEval = boardEval;
            currentDepth = depth;
            reverseMove();
        }

        for (auto const& pawnPromMove : possiblePawnPromMoves[currentDepth])
        {
            makePawnPromMove(pawnPromMove);
            int boardEval = minimax(depth - 1, maximizingPlayer);
            if (boardEval >= minEval)
            {
                currentDepth = depth;
                reverseMove();
                continue;
            }

            if (depth == setDepth)
            {
                aiBestPawnPromMove = pawnPromMove;
                clearAiBestMove();
                clearAiBestSpecialMove();
            }
            minEval = boardEval;
            currentDepth = depth;
            reverseMove();
        }

        count++;
        return minEval;
    }
}

int Game_c::getBoardEvaluation()
{
    int eval = 0;

    for (auto const& piece : pieceInfo)
    {
        if (piece.space != Captured)
        {
            switch (piece.figure & 31)
            {
            case PAWN:
                eval+= PAWN_VALUE;
                break;

            case ROOK:
                eval+= ROOK_VALUE;
                break;

            case KNIGHT:
                eval+= KNIGHT_VALUE;
                break;

            case BISHOP:
                eval+= BISHOP_VALUE;
                break;

            case QUEEN:
                eval+= QUEEN_VALUE;
                break;

            case KING:
                eval+= KING_VALUE;
                break;

            case PAWN | BLACK:
                eval-= PAWN_VALUE;
                break;

            case ROOK | BLACK:
                eval-= ROOK_VALUE;
                break;

            case KNIGHT | BLACK:
                eval-= KNIGHT_VALUE;
                break;

            case BISHOP | BLACK:
                eval-= BISHOP_VALUE;
                break;

            case QUEEN | BLACK:
                eval-= QUEEN_VALUE;
                break;

            case KING | BLACK:
                eval-= KING_VALUE;
                break;
            
            default:
                break;
            }
        }
    }   
    return eval;
}

void Game_c::clearAiBestMove()
{
    aiBestMove.piece = EMPTY;
    aiBestMove.from = Captured;
    aiBestMove.to = Captured;
}

void Game_c::clearAiBestSpecialMove()
{
    aiBestSpecialMove.piece1 = EMPTY;
    aiBestSpecialMove.piece2 = EMPTY;
    aiBestSpecialMove.from1 = Captured;
    aiBestSpecialMove.from2 = Captured;
    aiBestSpecialMove.to1 = Captured;
    aiBestSpecialMove.to2 = Captured;
}

void Game_c::clearAiBestPawnPromMove()
{
    aiBestPawnPromMove.piece = EMPTY;
    aiBestPawnPromMove.from = Captured;
    aiBestPawnPromMove.to = Captured;
    aiBestPawnPromMove.initFigure = 0x00;
    aiBestPawnPromMove.newFigure = 0x00;
}

/* METHODS AND VARIABLES FOR GETTING THE POSSIBLE MOVES */
void Game_c::initializePossibleMoves(int setDepth)
{
    for (int i = 0; i <= setDepth; i++)
    {
        std::list<Move_s> possMoves;
        possibleMoves.push_back(possMoves);
    }
}

void Game_c::initializePossibleSpecialMoves(int setDepth)
{
    for (int i = 0; i <= setDepth; i++)
    {
        std::list<Special_Move_s> possSpecialMoves;
        possibleSpecialMoves.push_back(possSpecialMoves);
    }
}

void Game_c::initializePossiblePawnPromMoves(int setDepth)
{
    for (int i = 0; i <= setDepth; i++)
    {
        std::list<Pawn_Prom_Move_s> possPawnPromMoves;
        possiblePawnPromMoves.push_back(possPawnPromMoves);
    }
}

void Game_c::clearPossibleMoves()
{
    for (auto& list : possibleMoves)
        list.clear();
}

void Game_c::clearPossibleSpecialMoves()
{
    for (auto& list : possibleSpecialMoves)
        list.clear();
}

void Game_c::clearPossiblePawnPromMoves()
{
    for (auto& list : possiblePawnPromMoves)
        list.clear();
}

void Game_c::getPossibleMoves(int pieceIdentifier)
{

    int figure = GET_FIGURE(pieceInfo[pieceIdentifier].figure);
    int from = pieceInfo[pieceIdentifier].space;

    switch (figure)
    {
    case PAWN:
        getPawnMoves(pieceIdentifier, from);
        break;

    case ROOK:
        getSlidingPieceMoves(pieceIdentifier, from);
        break;

    case BISHOP:
        getSlidingPieceMoves(pieceIdentifier, from);
        break;

    case QUEEN:
        getSlidingPieceMoves(pieceIdentifier, from);
        break;

    case KNIGHT:
        getKnightMoves(pieceIdentifier, from);
        break;

    case KING:
        getKingMoves(pieceIdentifier, from);
        break;
    
    default:
        break;
    }
}
/* get all the possible moves for various pieces */
void Game_c::getPawnMoves(int piece, int from)
{

    int color = (piece < 16) ? WHITE : BLACK;
    int directionOffset = (color == WHITE) ? -1 : 1;
    int startingRank = (color == WHITE) ? 6 : 1;
    int pawnPromotionRank = color == WHITE ? 1 : 6;
    
    /* get the possible straight line pawn moves */
    if (from / 8 == startingRank)
    {
        for (int i = 1; i <= 2; i++)
        {
            int possibleMoveLocation = from + i * directionOffset * 8;
            if (board[possibleMoveLocation] != EMPTY)
            {
                break;
            }
            Move_s move = createMove(piece, possibleMoveLocation, from);
            addMoveIfValid(move);
        }
    }
    else
    {
        int possibleMoveLocation = from + 1 * directionOffset * 8;
            if (board[possibleMoveLocation] == EMPTY)
            {
                Move_s move = createMove(piece, possibleMoveLocation, from);
                addMoveIfValid(move);
            }
    }

    for (int i = -1; i <= 1; i+=2)
    {
        // if (color == WHITE && i == -1 && from % 8 == 7) continue;
        // if (color == WHITE && i == 1 && from % 8 == 0) continue;
        if (i == -1 && from % 8 == 0) continue;
        if (i == 1 && from % 8 == 7) continue;
        int possibleMoveLocation = from + directionOffset * 8 + i;

        if (board[possibleMoveLocation] == EMPTY)
        {
            continue;
        }

        int checkPiece = board[possibleMoveLocation];
        int checkPieceColor = (checkPiece < 16) ? WHITE : BLACK;

        if (checkPieceColor != color)
        {
            Move_s move = createMove(piece, possibleMoveLocation, from);
            addMoveIfValid(move);
        }
    }

    /* get special au passant moves */
    for (int i = -1; i < 2; i+=2)
    {
        if (i == -1 && from % 8 == 0) continue;
        if (i == 1 && from % 8 == 7) continue;
        if (board[from + i] == EMPTY) continue;
        int possiblePassantPiece = board[from + i];
        bool isPassantAvailable = 
            ((pieceInfo[possiblePassantPiece].figure & PASSANT) == PASSANT) ? true : false;
        if (isPassantAvailable)
        {
            int moveOffset = (color == BLACK) ? 8 : -8;
            Special_Move_s special_move = 
                createSpecialMove(piece, possiblePassantPiece,
                from + moveOffset + i, Captured, from, from + i);
            addSpecialMoveIfValid(special_move);
        }
    }

    /* get pawn promotion moves if it is the ai's turn*/
    if (turn == aiPlayer)
    {
        // return if pawn promotion is not possible
        if (from / 8 != pawnPromotionRank)
        {
            return;
        }
        
        // add pawn promotion moves if pawn promotion is possible
        if (board[from + directionOffset * 8] == EMPTY)
        {
            createAndAddPawnPromMove(piece, from, from + directionOffset * 8);
        }

        for (int i = -1; i < 2; i+=2)
        {
            if (board[from + directionOffset * 8 + i] == EMPTY)
            {
                continue;
            }
            createAndAddPawnPromMove(piece, from, from + directionOffset * 8 + i);
        }
    }
    
}

void Game_c::getSlidingPieceMoves(int piece, int from)
{
    int pieceType = GET_FIGURE(pieceInfo[piece].figure);
    int pieceColor = GET_COLOR(pieceInfo[piece].figure);

    int startIndexForDirectionArray = (pieceType == BISHOP) ? 4 : 0;
    int endIndexForDirectionArray = (pieceType == ROOK) ? 4 : 8;

    for (int j = startIndexForDirectionArray; j < endIndexForDirectionArray; j++)
    {
        for (int i = 1; i < numSquaresToEdge[from][j] + 1; i++)
        {
            int possibleMoveLocation = from + (i * directionOffSets[j]);

            if (board[possibleMoveLocation] == EMPTY)
            {
                Move_s move = createMove(piece, possibleMoveLocation, from);
                addMoveIfValid(move);
            }
            else if ((pieceColor == BLACK && board[possibleMoveLocation] > 15) ||
                     (pieceColor == WHITE && board[possibleMoveLocation] < 16))
            {
                break;    
            }
            else
            {
                Move_s move = createMove(piece, possibleMoveLocation, from);
                addMoveIfValid(move);
                break; /* we break here because this block occurs if the move is a capture, 
                thus we cannot move past and we break to move in the next direction */
            }
        }    
    }  
}

void Game_c::getKnightMoves(int piece, int from)
{
    int color = (piece < 16) ? WHITE : BLACK;

    for (int i = 0; i < 8; i++)
    {
        int possibleMoveLocation = from + knightDirectionOffsets[i];

        if (numSquaresToEdge[from][knightMaxSpacesToEdge[i][0]] >= knightMaxSpacesToEdge[i][1] &&
            numSquaresToEdge[from][knightMaxSpacesToEdge[i][2]] >= knightMaxSpacesToEdge[i][3])
        {
            if (board[possibleMoveLocation] == EMPTY)
            {
                Move_s move = createMove(piece, possibleMoveLocation, from);
                addMoveIfValid(move);
                continue;
            }
           
            int checkPiece = board[possibleMoveLocation];
            int checkPieceColor = (checkPiece < 16) ? WHITE : BLACK;

            if (checkPieceColor != color)
            {
                Move_s move = createMove(piece, possibleMoveLocation, from);
                addMoveIfValid(move);
            }
        }
    }
}

void Game_c::getKingMoves(int piece, int from)
{
    int color = (piece < 16) ? WHITE : BLACK;

    for (int i = 0; i < 8; i++)
    {
        if (numSquaresToEdge[from][i] > 0)
        {
            int possibleMoveLocation = from + directionOffSets[i];
            if (board[possibleMoveLocation] == EMPTY)
            {
                Move_s move = createMove(piece, possibleMoveLocation, from);
                addMoveIfValid(move);
                continue;
            }

            int checkPiece = board[possibleMoveLocation];
            int checkPieceColor = (checkPiece < 16) ? WHITE : BLACK;

            if (checkPieceColor != color)
            {
                Move_s move = createMove(piece, possibleMoveLocation, from);
                addMoveIfValid(move);
            } 
        }      
    }
        /* get special moves for casteling 
     * castling can occur if there are no pieces between the king and the target rook
     * and if both the king and the target rook have not moved yet
     */

    int leftRookIdentifier = (color == WHITE) ? 8 : 24;
    int rightRookIdentifier = (color == WHITE) ? 15 : 31;
    bool castlePossible[2] = {true, true};
    if ((pieceInfo[piece].figure & MOVED) == MOVED) return;
    if ((pieceInfo[leftRookIdentifier].figure & MOVED) == MOVED) castlePossible[0] = false;
    if ((pieceInfo[rightRookIdentifier].figure & MOVED) == MOVED) castlePossible[1] = false;
    for (int i = 1; i < 4; i++)
    {
        if (board[from - i] != EMPTY) {castlePossible[0] = false; break;};
    }
    for (int i = 1; i < 3; i++)
    {
        if (board[from + i] != EMPTY) {castlePossible[1] = false; break;};
    }
    if (castlePossible[0])
    {
        Special_Move_s specialMove = createSpecialMove(piece, leftRookIdentifier, 
            from - 3, from - 2, from, from - 4);
        addSpecialMoveIfValid(specialMove);
    }
    if (castlePossible[1])
    {
        Special_Move_s specialMove = createSpecialMove(piece, rightRookIdentifier, 
            from + 2, from + 1, from, from + 3);
        addSpecialMoveIfValid(specialMove);
    }
}
/* creating, making, reversing, and verifying moves */
Move_s Game_c::createMove(int piece, int to, int from)
{
    Move_s move;

    move.piece = piece;
    move.to = to;
    move.from = from;

    return move;
}

Special_Move_s Game_c::createSpecialMove(int piece1, int piece2, int to1, 
    int to2, int from1, int from2)
{
    Special_Move_s special_move;
    special_move.piece1 = piece1;
    special_move.from1 = from1;
    special_move.to1 = to1;
    special_move.piece2 = piece2;
    special_move.from2 = from2;
    special_move.to2 = to2;
    return special_move;
}

Pawn_Prom_Move_s Game_c::createPawnPromMove(int piece1, int from, int to,
    int newFigure)
{
    Pawn_Prom_Move_s pawnPromMove;

    pawnPromMove.piece = piece1;
    pawnPromMove.initFigure = pieceInfo[piece1].figure;
    pawnPromMove.from = from;
    pawnPromMove.to = to;
    pawnPromMove.newFigure = newFigure;

    return pawnPromMove;
}

void Game_c::addMoveIfValid(Move_s move) {
    bool inCheck;
    if (move.to > 63 || move.to < 0)
        return;
    int color = ((pieceInfo[move.piece].figure & BLACK) == BLACK) ? BLACK : WHITE;
    makeMove(move);
    inCheck = isInCheck(color);
    reverseMove();
    if (!inCheck) possibleMoves[currentDepth].push_back(move);
}

void Game_c::addSpecialMoveIfValid(Special_Move_s specialMove)
{
    bool inCheck;
    int color = ((pieceInfo[specialMove.piece1].figure & BLACK) == BLACK) ? BLACK : WHITE;
    makeSpecialMove(specialMove);
    inCheck = isInCheck(color);
    reverseMove();
    if (!inCheck) possibleSpecialMoves[currentDepth].push_back(specialMove);
}

void Game_c::addPawnPromMoveIfValid(Pawn_Prom_Move_s pawnPromMove)
{
    bool inCheck;
    int color = ((pieceInfo[pawnPromMove.piece].figure & BLACK) == BLACK) ? BLACK : WHITE;
    makePawnPromMove(pawnPromMove);
    inCheck = isInCheck(color);
    reverseMove();
    if (!inCheck) possiblePawnPromMoves[currentDepth].push_back(pawnPromMove);
}

void Game_c::createAndAddPawnPromMove(int piece, int from, int to)
{
    int clearedFigure = CLEAR_FIGURE(pieceInfo[piece].figure);
    int knightFigure = clearedFigure | KNIGHT;
    int queenFigure = clearedFigure | QUEEN;
    Pawn_Prom_Move_s pawnPromKnight = createPawnPromMove(piece, from,
        to, knightFigure);
    Pawn_Prom_Move_s pawnPromQueen = createPawnPromMove(piece, from,
        to, queenFigure);
    /* we only add the knight and queen promotions because there is never a 
     * reason to promote to a bishop or rook when you could promote to a queen
     * instead 
     * */
    addPawnPromMoveIfValid(pawnPromKnight);
    addPawnPromMoveIfValid(pawnPromQueen);
    return;
}

void Game_c::makeMove(Move_s move)
{
    clearPieceInfoLog(currentDepth);
    // update piece info vector
    if (board[move.to] != EMPTY && board[move.to] != move.piece)
    {
        int capturedPiece = board[move.to];

        // update move log
        pieceInfoLog[currentDepth].piece2 = pieceInfo[capturedPiece];

        // update piece info vector
        pieceInfo[capturedPiece].previousSpace = pieceInfo[capturedPiece].space;
        pieceInfo[capturedPiece].space = Captured;
    }
    
    // update move log
    pieceInfoLog[currentDepth].piece1 = pieceInfo[move.piece];

    // update piece info vector
    pieceInfo[move.piece].space = move.to;
    pieceInfo[move.piece].previousSpace = move.from;

    // update the board
    board[move.from] = EMPTY;
    board[move.to] = move.piece;
    
    // update has moved and passant status
    int figure = pieceInfo[move.piece].figure;
    int newFigure = SET_MOVED(figure);
    if ((pieceInfo[move.piece].figure & FIGURE) == PAWN && 
        abs(move.from - move.to) == 16) newFigure = SET_PASSANT(newFigure);
    pieceInfo[move.piece].figure = newFigure;
    return;
}

void Game_c::makeSpecialMove(Special_Move_s specialMove)
{
    pieceInfoLog[currentDepth].piece1 = pieceInfo[specialMove.piece1];
    pieceInfoLog[currentDepth].piece2 = pieceInfo[specialMove.piece2];
    board[specialMove.from1] = EMPTY;
    board[specialMove.from2] = EMPTY;
    board[specialMove.to1] = specialMove.piece1;
    if (specialMove.to2 != Captured) board[specialMove.to2] = specialMove.piece2;
    pieceInfo[specialMove.piece1].previousSpace = specialMove.from1;
    pieceInfo[specialMove.piece2].previousSpace = specialMove.from2;
    pieceInfo[specialMove.piece1].space = specialMove.to1;
    pieceInfo[specialMove.piece2].space = specialMove.to2;
    int piece1Figure = pieceInfo[specialMove.piece1].figure;
    int piece2Figure = pieceInfo[specialMove.piece2].figure;
    pieceInfo[specialMove.piece1].figure = SET_MOVED(piece1Figure);
    pieceInfo[specialMove.piece2].figure = SET_MOVED(piece2Figure);
    return;
}

void Game_c::makePawnPromMove(Pawn_Prom_Move_s pawnPromMove)
{
    clearPieceInfoLog(currentDepth);
    if (board[pawnPromMove.to] != EMPTY && 
        board[pawnPromMove.to] != pawnPromMove.piece)
    {
        int capturedPiece = board[pawnPromMove.to];

        // update move log
        pieceInfoLog[currentDepth].piece2 = pieceInfo[capturedPiece];

        // update piece info vector
        pieceInfo[capturedPiece].previousSpace = pieceInfo[capturedPiece].space;
        pieceInfo[capturedPiece].space = Captured;
    }

    // update move log
    pieceInfoLog[currentDepth].piece1 = pieceInfo[pawnPromMove.piece];

    // update piece info vector
    // update figure to new figure
    pieceInfo[pawnPromMove.piece].figure = pawnPromMove.newFigure;
    pieceInfo[pawnPromMove.piece].space = pawnPromMove.to;
    pieceInfo[pawnPromMove.piece].previousSpace = pawnPromMove.from;

    // update the board
    board[pawnPromMove.from] = EMPTY;
    board[pawnPromMove.to] = pawnPromMove.piece;

    return;
}

void Game_c::reverseMove()
{
    int piece1 = pieceInfoLog[currentDepth].piece1.identifier;
    int piece2 = EMPTY;
    // update piece info and move log
    if (pieceInfoLog[currentDepth].piece2.identifier != EMPTY)
    {
        piece2 = pieceInfoLog[currentDepth].piece2.identifier;
        board[pieceInfo[piece2].space] = EMPTY;
        pieceInfo[piece2] = pieceInfoLog[currentDepth].piece2;
    }

    board[pieceInfo[piece1].space] = EMPTY;
    pieceInfo[piece1] = pieceInfoLog[currentDepth].piece1;
    pieceInfoLog[currentDepth].piece1.identifier = EMPTY;

    // update board
    if (piece2 != EMPTY)
        board[pieceInfo[piece2].space] = piece2;
    board[pieceInfo[piece1].space] = piece1;
}

void Game_c::clearPieceInfoLog(int depth)
{
    pieceInfoLog[depth].piece1 = clearedPieceInfo;
    pieceInfoLog[depth].piece2 = clearedPieceInfo;
}

bool Game_c::isInCheck(int friendlyColor)
{
    int kingPieceIdentifier = (friendlyColor == BLACK) ? 28 : 12;
    int kingPieceSpace = pieceInfo[kingPieceIdentifier].space;
    int checkLoc;

    // check for check by opposing king
    for (int directionOffset = 0; directionOffset < 8; directionOffset++)
    {
        checkLoc = pieceInfo[kingPieceIdentifier].space + (directionOffSets[directionOffset]);

        if (checkLoc < 0 || checkLoc > 63) continue;

        if (board[checkLoc] == EMPTY)
        {
            continue;
        }

        int pieceToCheck = board[checkLoc];
        int pieceToCheckFigure = GET_FIGURE(pieceInfo[pieceToCheck].figure);
        int pieceToCheckColor = GET_COLOR(pieceInfo[pieceToCheck].figure);

        if (pieceToCheckFigure == KING && pieceToCheckColor != friendlyColor)
        {
            return true;
        }
    }

    // check for check by opposing rook or queen
    for (int directionOffset = 0; directionOffset < 4; directionOffset++)
    {
        for (int i = 1; i < numSquaresToEdge[kingPieceSpace][directionOffset] + 1; i++)
        {
            checkLoc = kingPieceSpace + (i * directionOffSets[directionOffset]);

            if (checkLoc < 0 || checkLoc > 63) continue;

            if (board[checkLoc] == EMPTY)
            {
                continue;
            }

            int pieceToCheck = board[checkLoc];
            int pieceToCheckFigure = GET_FIGURE(pieceInfo[pieceToCheck].figure);
            int pieceToCheckColor = GET_COLOR(pieceInfo[pieceToCheck].figure);

            if (friendlyColor != pieceToCheckColor && 
                (pieceToCheckFigure == QUEEN || pieceToCheckFigure == ROOK))
            {
                return true;
            }
            break;
        }
    }

    // check for check by opposing bishop or queen
    for (int directionOffset = 4; directionOffset < 8; directionOffset++)
    {
        for (int i = 1; i < numSquaresToEdge[kingPieceSpace][directionOffset] + 1; i++)
        {
            checkLoc = kingPieceSpace + (i * directionOffSets[directionOffset]);

            if (checkLoc < 0 || checkLoc > 63) continue;

            if (board[checkLoc] == EMPTY)
            {
                continue;
            }

            int pieceToCheck = board[checkLoc];
            int pieceToCheckFigure = GET_FIGURE(pieceInfo[pieceToCheck].figure);
            int pieceToCheckColor = GET_COLOR(pieceInfo[pieceToCheck].figure);

            if (friendlyColor != pieceToCheckColor && 
                (pieceToCheckFigure == QUEEN || pieceToCheckFigure == BISHOP))
            {
                return true;
            }
            break;
        }
    }

    // check for check by opposing pawn
    // modify the direction offset variables to use with pawn movement
    int directionOffset = (friendlyColor == WHITE) ? -1 : 1;

    for (int i = -1; i <= 1; i += 2)
    {
        checkLoc = kingPieceSpace + (directionOffset * 8) - i;

        if (checkLoc < 0 || checkLoc > 63) continue;

        if (i < 0 && numSquaresToEdge[checkLoc][DirectionEast] > 0)
        {
            if (board[checkLoc] == EMPTY)
            {
                continue;
            }

            int pieceToCheck = board[checkLoc];
            int pieceToCheckFigure = GET_FIGURE(pieceInfo[pieceToCheck].figure);
            int pieceToCheckColor = GET_COLOR(pieceInfo[pieceToCheck].figure);

            if (pieceToCheckColor != friendlyColor && pieceToCheckFigure == PAWN)
            {
                return true;
            }
        }

        if (i > 0 && numSquaresToEdge[checkLoc][DirectionNorthWest] > 0)
        {
            if (board[checkLoc] == EMPTY)
            {
                continue;
            }

            int pieceToCheck = board[checkLoc];
            int pieceToCheckFigure = GET_FIGURE(pieceInfo[pieceToCheck].figure);
            int pieceToCheckColor = GET_COLOR(pieceInfo[pieceToCheck].figure);

            if (pieceToCheckColor != friendlyColor && pieceToCheckFigure == PAWN)
            {
                return true;
            }
        }
    }

    // check for check by opposing knight
        
    for (int i = 0; i < 8; i++)
    {
        checkLoc = kingPieceSpace + knightDirectionOffsets[i];

        if (checkLoc < 0 || checkLoc > 63) continue;

        if (numSquaresToEdge[kingPieceSpace][knightMaxSpacesToEdge[i][0]] >= knightMaxSpacesToEdge[i][1] &&
            numSquaresToEdge[kingPieceSpace][knightMaxSpacesToEdge[i][2]] >= knightMaxSpacesToEdge[i][3])
        {

            int pieceToCheck = board[checkLoc];
            int pieceToCheckFigure = GET_FIGURE(pieceInfo[pieceToCheck].figure);
            int pieceToCheckColor = GET_COLOR(pieceInfo[pieceToCheck].figure);

            if (pieceToCheckColor != friendlyColor && pieceToCheckFigure == KNIGHT)
            {
                return true;
            }
        }     
    }

    return false;
}

void Game_c::updateMoveLog(Move_s move)
{
    moveLog.piece1 = move.piece;
    moveLog.to1 = move.to;
    moveLog.from1 = move.from;
    moveLog.piece2 = EMPTY;
    moveLog.to2 = Captured;
    moveLog.from2 = Captured;
}

void Game_c::updateMoveLog(Special_Move_s specialMove)
{
    moveLog.piece1 = specialMove.piece1;
    moveLog.piece2 = specialMove.piece2;
    moveLog.to1 = specialMove.to1;
    moveLog.to2 = specialMove.to2;
    moveLog.from1 = specialMove.from1;
    moveLog.from2 = specialMove.from2;
}

void Game_c::clearPreviousPassant()
{
    if ((pieceInfo[moveLog.piece1].figure & FIGURE) == PAWN) 
        pieceInfo[moveLog.piece1].figure = CLEAR_PASSANT(pieceInfo[moveLog.piece1].figure);
}

void Game_c::clearPieceInfoLog()
{
    for (int i = 0; i < pieceInfoLog.size(); i++)
    {
        /* clear move log */
        pieceInfoLog[i].piece1.identifier = EMPTY;
        pieceInfoLog[i].piece2.identifier = EMPTY;
        pieceInfoLog[i].piece1.space = Captured;
        pieceInfoLog[i].piece2.space = Captured;
        pieceInfoLog[i].piece1.previousSpace = Captured;
        pieceInfoLog[i].piece2.previousSpace = Captured;
    }
}

void Game_c::initializePieceInfoLog(int depth) 
{
    for (int i = 0; i <= depth; i++)
    {
        PieceInfoLog_s log;
        pieceInfoLog.push_back(log);
    }
    clearPieceInfoLog();
}

/* CHECKMATE */
void Game_c::checkForCheckmate()
{
    clearPossibleMoves();
    clearPossibleSpecialMoves();
    clearPossiblePawnPromMoves();
    int start = (turn == WHITE) ? 0 : 16;
    int end = (turn == WHITE) ? 16 : 32;
    for (int piece = start; piece < end; piece++)
    {
        if (pieceInfo[piece].space != Captured)
            getPossibleMoves(piece);
    }
    if (possibleMoves[setDepth].size() == 0 && 
        possibleSpecialMoves[setDepth].size() == 0 &&
        possiblePawnPromMoves[setDepth].size() == 0)
        isInCheckmate = true;
    clearPossibleMoves();
    clearPossibleSpecialMoves();
    clearPossiblePawnPromMoves();
    }

/* PAWN PROMOTION */
void Game_c::updatePromotionStatus(int piece)
{
    int space = pieceInfo[piece].space;
    promotionPiece = piece;
    isPromotionPossible = true;
    int rectStartingX = boardSpaceTextureRectOriginx + (space % 8) * boardSpaceWidth;
    int color = ((pieceInfo[piece].figure & BLACK) == BLACK) ? BLACK : WHITE;
    int rectStartingYBlackPawn = boardSpaceTextureRectOriginy + 7 * boardSpaceHeight;
    int rectStartingYWhitePawn = boardSpaceTextureRectOriginy;
    int rectStartingY = (color == BLACK)
                        ? rectStartingYBlackPawn : rectStartingYWhitePawn;

    *promotionRectVector[0] = {rectStartingX, rectStartingY, 
        boardSpaceTextureRectWidth / 2, boardSpaceTextureRectHeight / 2};

    *promotionRectVector[1] = {rectStartingX + boardSpaceTextureRectWidth / 2, rectStartingY, 
        boardSpaceTextureRectWidth / 2, boardSpaceTextureRectHeight / 2};

    *promotionRectVector[2] = {rectStartingX, rectStartingY + 
        boardSpaceTextureRectHeight / 2, boardSpaceTextureRectWidth / 2, 
        boardSpaceTextureRectHeight / 2};

    *promotionRectVector[3] = {rectStartingX + boardSpaceTextureRectWidth / 2, 
        rectStartingY + boardSpaceTextureRectHeight / 2, 
        boardSpaceTextureRectWidth / 2, boardSpaceTextureRectHeight / 2};                            
}

void Game_c::clearPromotionStatus()
{
    promotionPiece = EMPTY;
    isPromotionPossible = false;
}

void Game_c::promotePawn(int piece)
{
    int iterator = 0;
    bool wasPieceChosen = false;
    for (auto& rect : promotionRectVector)
    {
        if (SDL_PointInRect(&mousePosition, rect))
        {
            wasPieceChosen = true;
            break;
        }
        else
        {
            iterator++;
        }
    }
    if (wasPieceChosen)
    {
        switch (iterator)
        {
        case 0:
            std::cout << "Previous figure: " << pieceInfo[piece].figure << std::endl;
            pieceInfo[piece].figure = CLEAR_FIGURE(pieceInfo[piece].figure);
            std::cout << "After clear figure: " << pieceInfo[piece].figure << std::endl;
            pieceInfo[piece].figure = pieceInfo[piece].figure | QUEEN;
            std::cout << "Final figure: " << pieceInfo[piece].figure << std::endl;
            break;

        case 1:
            pieceInfo[piece].figure = CLEAR_FIGURE(pieceInfo[piece].figure);
            pieceInfo[piece].figure = pieceInfo[piece].figure | ROOK;
            break;

        case 2:
            pieceInfo[piece].figure = CLEAR_FIGURE(pieceInfo[piece].figure);
            pieceInfo[piece].figure = pieceInfo[piece].figure | BISHOP;
            break;

        case 3:
            pieceInfo[piece].figure = CLEAR_FIGURE(pieceInfo[piece].figure);
            pieceInfo[piece].figure = pieceInfo[piece].figure | KNIGHT;
            break;
        
        default:
            break;
        }
        clearPromotionStatus();
    }
}

/* CLICK AND DRAG */
void Game_c::grabPiece()
{
    int iterator = 0;
    for (auto const& rect : boardSpaceRects)
    {
        if (SDL_PointInRect(&mousePosition, rect) && iterator != 64)
        {
            // std::cout << iterator << std::endl;
            if (board[iterator] != EMPTY)
            {
                int piece = board[iterator];
                if (turn == WHITE && ((pieceInfo[piece].figure & BLACK) == BLACK)
                    || turn == BLACK && ((pieceInfo[piece].figure & BLACK) == WHITE))
                {
                    std::cout << "It is not your turn!" << std::endl;
                    break;
                }
                getPossibleMoves(piece);
                grabbedPieceLog = pieceInfo[piece];
                pieceInfo[GRABBED_PIECE] = pieceInfo[piece];
                pieceInfo[GRABBED_PIECE].space = Grabbed;
                pieceInfo[piece].space = Captured;
            }
            break;
        }
        else
        {
            iterator++;
            continue;
        }
    }
}

void Game_c::dropPiece()
{
    int iterator = 0;
    bool isDroppedInSpace = false;
    for (auto const& rect : boardSpaceRects)
    {
        if (SDL_PointInRect(&mousePosition, rect) && iterator != 64 && 
            grabbedPieceLog.identifier != EMPTY)
        {
            int newPosition = iterator;
            bool isValidMove = false;

            /* check if the move is a possible regular move */
            for (auto const& move : possibleMoves[currentDepth])
            {
                if (move.to == newPosition) isValidMove = true;
                if (isValidMove)
                {
                    int piece = grabbedPieceLog.identifier;
                    pieceInfo[piece] = grabbedPieceLog;
                    makeMove(move);
                    clearPromotionStatus();
                    clearPreviousPassant();
                    updateMoveLog(move);
                    printMoveLog();
                    clearPieceInfoLog();
                    printBoard(board);
                    //printPieceInfo();
                    isDroppedInSpace = true;
                    clearGrabbedPieceLog();
                    clearGrabbedPiece();
                    turn ^= BLACK;
                    if ((pieceInfo[moveLog.piece1].figure & FIGURE) == PAWN && 
                        (moveLog.to1 / 8 == 0 || moveLog.to1 / 8 == 7))
                    {
                        updatePromotionStatus(moveLog.piece1);
                    }
                    std::cout << "Moved piece figure: " << 
                        pieceInfo[moveLog.piece1].figure << std::endl;
                    logUndo();
                    clearPossibleMoves();
                    clearPossibleSpecialMoves();
                    clearPossiblePawnPromMoves();
                    checkForCheckmate();
                    break;
                }
            }
            if (isValidMove) break;

            /* check if the move is a posible special move */
            for (auto const& specialMove : possibleSpecialMoves[currentDepth])
            {
                if (specialMove.to1 == newPosition) isValidMove = true;
                if (isValidMove)
                {
                    int piece = grabbedPieceLog.identifier;
                    pieceInfo[piece] = grabbedPieceLog;
                    makeSpecialMove(specialMove);
                    clearPreviousPassant();
                    updateMoveLog(specialMove);
                    printMoveLog();
                    clearPieceInfoLog();
                    printBoard(board);
                    isDroppedInSpace = true;
                    clearGrabbedPieceLog();
                    clearGrabbedPiece();
                    turn ^= BLACK;
                    logUndo();
                    clearPossibleMoves();
                    clearPossibleSpecialMoves();
                    clearPossiblePawnPromMoves();
                    checkForCheckmate();
                    break;
                }
            }
        }
        else
        {
            iterator++;
            continue;
        }
    }
    if (!isDroppedInSpace && grabbedPieceLog.identifier != EMPTY)
    {
        int piece = grabbedPieceLog.identifier;
        pieceInfo[piece] = grabbedPieceLog;
        clearGrabbedPieceLog();
        clearGrabbedPiece();
    }

    clearPossibleMoves();
    clearPossibleSpecialMoves();
    clearPossiblePawnPromMoves();
}

/* DEBUGGING */
void Game_c::toggleAI()
{
    if (aiPlayer == BLACK || aiPlayer == WHITE)
        // this will turn the AI off since it is neither black nor white
        aiPlayer = 1;                               
    else
    {
        // the ai can only be set back to black
        aiPlayer = BLACK;                           
    }
}
void Game_c::printMoveLog()
{
    // piece 1
    std::cout << "Piece 1: " << moveLog.piece1 << std::endl;
    std::cout << "To " << moveLog.to1 << std::endl;
    std::cout << "From " << moveLog.from1 << std::endl;

    // piece 2
    std::cout << "Piece 2: " << moveLog.piece2 << std::endl;
    std::cout << "To: " << moveLog.to2 << std::endl;
    std::cout << "From: " << moveLog.from2 << std::endl << std::endl;
}

/* UNDO FUNCTIONALITY */
void Game_c::logUndo()
{
    undoBoardStack.push(board);
    undoPieceInfoStack.push(pieceInfo);
    undoTurnStack.push(turn);
}

void Game_c::undo()
{
    board = undoBoardStack.top();
    undoBoardStack.pop();

    pieceInfo = undoPieceInfoStack.top();
    undoPieceInfoStack.pop();

    turn = undoTurnStack.top();
    undoTurnStack.pop();

    if (turn == BLACK)
        waitUntilPressContinue = true;
}

// /* DIFFICULTY SELECT */
// void Game_c::changeDifficulty(int newSetDepth)
// {
//     setDepth = newSetDepth;
//     possibleMoves.clear();
//     possibleSpecialMoves.clear();
//     pieceInfoLog.clear();
//     initializePossibleMoves(setDepth);
//     initializePossibleSpecialMoves(setDepth);
//     initializePieceInfoLog(setDepth);
// }

void Game_c::ruyLopez() 
{
}