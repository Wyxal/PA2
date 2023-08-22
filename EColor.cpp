#include "EColor.h"

EColor OppositeSide(EColor self)
{
    switch (self)
    {
    case EColor::WHITE:
        return EColor::BLACK;
    case EColor::BLACK:
        return EColor::WHITE;
    default:
        throw std::logic_error("NONE is not color");
    }
}

std::ostream &operator<<(std::ostream &os, EColor color)
{
    if (color == EColor::WHITE)
        return os << "WHITE";
    else
        return os << "BLACK";
}