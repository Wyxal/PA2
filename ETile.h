#pragma once

#include <string>


/**
 *  Enum used for indexing vector representing board for better readability
 */
enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, OFFBOARD
};

/**
 *  Enum used for indexing ranks on board for better readability
 */
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8};

/**
 *  Enum used for indexing files on board for better readability
 */
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};

/**
 *  Checks if a position is off the board.
 *  @param position The position on the board.
 *  @return true if the position is off the board, false otherwise.
*/
bool isOffBoard(int position);

/**
 *  Returns the rank of a position on the board.
 *  @param position The position on the board.
 *  @return The rank of the position.
*/
int getRank(int position);

/**
 *  Returns the file of a position on the board.
 *  @param position The position on the board.
 *  @return The file of the position.
*/
int getFile(int position);

/**
 *  Converts a tile position in algebraic notation to its corresponding index on the board.
 *  @param position The tile position in algebraic notation (e.g., "a1", "h8").
 *  @return The index on the board corresponding to the tile position, or OFFBOARD if the position is invalid.
*/
int tileToIndex(const std::string & position);

/**
 *  Converts an index on the board to its corresponding tile position in algebraic notation.
 *  @param index The index on the board.
 *  @return The tile position in algebraic notation, or "OFFBOARD" if the index is invalid.
*/
std::string indexToTile(int index);