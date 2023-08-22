#include "EPiece.h"

std::ostream &operator<<(std::ostream &os, const EPiece &self)
{
    switch (self)
    {
    case EPiece::PAWN:
        return os << 'p';
    case EPiece::KNIGHT:
        return os << 'n';
    case EPiece::ROOK:
        return os << 'r';
    case EPiece::BISHOP:
        return os << 'b';
    case EPiece::QUEEN:
        return os << 'q';
    case EPiece::KING:
        return os << 'k';
    case EPiece::EMPTY:
        return os << '.';
    default:
        return os << '-';
    }
}

int EPieceToCode(EPiece piece)
{
    switch (piece)
    {
    case EPiece::PAWN:
        return 0;
    case EPiece::KNIGHT:
        return 1;
    case EPiece::BISHOP:
        return 2;
    case EPiece::ROOK:
        return 3;
    case EPiece::QUEEN:
        return 4;
    case EPiece::KING:
        return 5;
    default:
        throw std::logic_error("No code for EMPTY or OFFBOARD");
    }
}