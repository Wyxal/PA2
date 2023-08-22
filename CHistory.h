#pragma once

#include "CMove.h"
#include "EConst.h"

/**
 * Structure for saving state of the CBoard
 */
struct CHistory
{

    CHistory() = default;

    // Move made in this state of CBoard
    CMove Move;

    // Castling permission
    unsigned int Castling = NO_CASTLE;

    // En Passant square
    int EnPassant = OFFBOARD;

    // Fifty moves counter
    int FiftyTurns = 0;

    // State key of the CBoard
    uint64_t m_StateKey = 0;
};
