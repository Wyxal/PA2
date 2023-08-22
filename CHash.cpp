#include "CHash.h"

CHash::CHash()
{
    initiateHashKeys();
}

void CHash::initiateHashKeys()
{
    std::random_device seed;
    std::mt19937_64 gen(seed());
    std::uniform_int_distribution<uint64_t> dist;

    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 120; j++)
            PiecesKeys[i][j] = dist(gen);
}

uint64_t CHash::generateStateKey(const std::shared_ptr<CPiece> *board)
{
    // xor state key with piece key at its position
    uint64_t stateKey = 0;
    for (int i = 0; i < 8; i++)
        for (int j = A1; j <= H1; j++)
            if (board[i * 10 + j]->getCode() != EMPTY)
                stateKey ^= PiecesKeys[board[i * 10 + j]->getCode()][i * 10 + j];

    return stateKey;
}