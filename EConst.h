#pragma once

/**
 * Starting board of chess
 */
const char *const START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

/**
 * Enum representing each piece on board
 */
enum
{
    p, n, b, r, q, k, P, N, B, R, Q, K, EMPTY
};

/**
 * Array of chars representing each piece on board
 */
const char PIECE_CHAR_CODE[13] = {'p', 'n', 'b', 'r', 'q', 'k', 'P', 'N', 'B', 'R', 'Q', 'K', ' '};

/**
 * Score for each piece on board
 * source: https://www.chessprogramming.org/Point_Value
 */
const int PIECE_SCORE[13] = {100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000, 0};

/**
 * Score for white pawn positioning
 * encourages AI to develop pawns to the middle and moving pawns at D2, E2, D7, E7
 * used for evaluation of the board
 * source: https://www.chessprogramming.org/Simplified_Evaluation_Function
 */
const int PAWN_SCORE[120] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 10, 10, 0, -10, -10, 0, 10, 10, 0,
    0, 5, 0, 0, 5, 5, 0, 0, 5, 0,
    0, 0, 0, 10, 20, 20, 10, 0, 0, 0,
    0, 5, 5, 5, 10, 10, 5, 5, 5, 0,
    0, 10, 10, 10, 20, 20, 10, 10, 10, 0,
    0, 20, 20, 20, 30, 30, 20, 20, 20, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0

};

/**
 * Score for white knight positioning,
 * encourages AI to develop knights to the middle, moving them from their starting positions
 * used for evaluation of the board
 * source: https://www.chessprogramming.org/Simplified_Evaluation_Function
 */
const int KNIGHT_SCORE[120] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -10, 0, 0, 0, 0, -10, 0, 0,
    0, 0, 0, 0, 5, 5, 0, 0, 0, 0,
    0, 0, 0, 10, 10, 10, 10, 0, 0, 0,
    0, 0, 0, 10, 20, 20, 10, 5, 0, 0,
    0, 5, 10, 15, 20, 20, 15, 10, 5, 0,
    0, 5, 10, 10, 20, 20, 10, 10, 5, 0,
    0, 0, 0, 5, 10, 10, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * Score for white bishop positioning,
 * encourages AI to develop bishops to the middle, moving them from their starting positions
 * used for evaluation of the board
 * source: https://www.chessprogramming.org/Simplified_Evaluation_Function
 */
const int BISHOP_SCORE[120] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -10, 0, 0, -10, 0, 0, 0,
    0, 0, 0, 0, 10, 10, 0, 0, 0, 0,
    0, 0, 0, 10, 15, 15, 10, 0, 0, 0,
    0, 0, 10, 15, 20, 20, 15, 10, 0, 0,
    0, 0, 10, 15, 20, 20, 15, 10, 0, 0,
    0, 0, 0, 10, 15, 15, 10, 0, 0, 0,
    0, 0, 0, 0, 10, 10, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * Score for white bishop positioning,
 * encourages AI to develop bishops to the files D, E and ranks 2, for black 7
 * used for evaluation of the board
 * source: https://www.chessprogramming.org/Simplified_Evaluation_Function
 */
const int ROOK_SCORE[120] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 5, 10, 10, 5, 0, 0, 0,
    0, 0, 0, 5, 10, 10, 5, 0, 0, 0,
    0, 0, 0, 5, 10, 10, 5, 0, 0, 0,
    0, 0, 0, 5, 10, 10, 5, 0, 0, 0,
    0, 0, 0, 5, 10, 10, 5, 0, 0, 0,
    0, 0, 0, 5, 10, 10, 5, 0, 0, 0,
    0, 25, 25, 25, 25, 25, 25, 25, 25, 0,
    0, 0, 0, 5, 10, 10, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * Mirror array used for evaluation of black pieces,
 * for reusing evaluation arrays for white
 */
const int MIRROR[120] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 91, 92, 93, 94, 95, 96, 97, 98, 0,
    0, 81, 82, 83, 84, 85, 86, 87, 88, 0,
    0, 71, 72, 73, 74, 75, 76, 77, 78, 0,
    0, 61, 62, 63, 64, 65, 66, 67, 68, 0,
    0, 51, 52, 53, 54, 55, 56, 57, 58, 0,
    0, 41, 42, 43, 44, 45, 46, 47, 48, 0,
    0, 31, 32, 33, 34, 35, 36, 37, 38, 0,
    0, 21, 22, 23, 24, 25, 26, 27, 28, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * Capture score for evaluation of capture moves
 * encourages AI to capture high cost pieces (e.g. QUEEN, ROOK) with low cost pieces (e.g. PAWN)
 * formula: CAPTURE_SCORE[EPieceToCode(capture)] + 6 - ( CAPTURE_SCORE[EPieceToCode(piece)] / 100) + 1000000
 * helps with speed of NegaMax algorithm (source: https://www.chessprogramming.org/Negamax)
 */
const int CAPTURE_SCORE[13] = {100, 200, 300, 400, 500, 600};

/**
 * Representing infinity for 32bit int numbers
 */
const int INFINITE = INT32_MAX;

/**
 * Moves for knights
 * adding the each number to current position will result in position after move
 * source: https://www.chessprogramming.org/10x12_Board
 */
const int KNIGHT_ATTACKS[8] = {-21, -19, -12, -8, 8, 12, 19, 21};

/**
 * Moves for rooks
 * adding the each number to current position will result in position after move
 * source: https://www.chessprogramming.org/10x12_Board
 */
const int ROOK_ATTACKS[4] = {-10, -1, 1, 10};

/**
 * Moves for bishops
 * adding the each number to current position will result in position after move
 * source: https://www.chessprogramming.org/10x12_Board
 */
const int BISHOP_ATTACKS[4] = {-11, -9, 9, 11};

/**
 * Moves for king
 * adding the each number to current position will result in position after move
 * source: https://www.chessprogramming.org/10x12_Board
 */
const int KING_ATTACKS[8] = {-11, -10, -9, -1, 1, 9, 10, 11};

/**
 * Representing permission for white king to castle king side
 */
const unsigned int WHITE_KING_CASTLE = 0x8U;

/**
 * Representing permission for white king to castle queen side
 */
const unsigned int WHITE_QUEEN_CASTLE = 0x4U;

/**
 * Representing permission for black king to castle king side
 */
const unsigned int BLACK_KING_CASTLE = 0x2U;

/**
 * Representing permission for black king to castle queen side
 */
const unsigned int BLACK_QUEEN_CASTLE = 0x1U;

/**
 * Representing no castle permission
 */
const unsigned int NO_CASTLE = 0x0U;