#pragma once

#include <iostream>

/**
 *  Enum class representing each element of board
 */
enum class EPiece : char
{
    KING = 'K',
    QUEEN = 'Q',
    ROOK = 'R',
    BISHOP = 'B',
    KNIGHT = 'N',
    PAWN = 'P',
    EMPTY = '.',
    OFFBOARD = ' '
};

/**
 *  Converts the EPiece enum value to its corresponding code.
 *  @param piece The EPiece value to convert.
 *  @return The code corresponding to the EPiece value.
 *  @throws std::logic_error if the EPiece value is EMPTY or OFFBOARD.
 */
int EPieceToCode(EPiece piece);

/**
 *  Writes the string representation of the EPiece enum to the output stream.
 *  @param os The output stream to write to.
 *  @param self The EPiece value to write.
 *  @return The modified output stream.
 */
std::ostream &operator<<(std::ostream &os, const EPiece &self);