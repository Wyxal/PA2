#pragma once

#include <iostream>

/**
 * Enum class for representing color of the piece
 */
enum EColor
{
    WHITE = 1,
    BLACK = -1,
    NONE = 0
};

/**
 *  Returns the opposite side color of the given color.
 *  @param self The color for which to find the opposite side color.
 *  @return The opposite side color of the given color.
 *  @throws std::logic_error If the given color is not valid (neither white nor black).
 */
EColor OppositeSide(EColor self);

/**
 *  Writes the string representation of the given color to the output stream.
 *  @param os The output stream to write to.
 *  @param color The color to be written to the output stream.
 *  @return The reference to the output stream after writing the color.
 */
std::ostream &operator<<(std::ostream &os, EColor color);