#pragma once

#include <random>
#include <memory>

#include "Pieces/CPiece.h"
#include "EPiece.h"
#include "EColor.h"

/**
 * Class enconding state
 * source: https://www.chessprogramming.org/Zobrist_Hashing
 */
class CHash
{
private:
    // Hash keys for each piece for each position
    uint64_t PiecesKeys[12][120];

    // Initialize hash keys
    void initiateHashKeys();

public:
    CHash();

    /**
     * Generates state key
     * @param board array representing the board
     * @return state key
     */
    uint64_t generateStateKey(const std::shared_ptr<CPiece> *board);
};