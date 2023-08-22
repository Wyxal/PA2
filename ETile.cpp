#include "ETile.h"

/**
 * Board is represented as 1D array where indexes 0 - 19 and 100 - 119 are OFFBOARD
 */

int getRank(int position)
{
    // Rank is first digit of position and we have first 20 positions OFFBOARD
    // so we subtract 2 to get number from 0 - 7
    return position / 10 - 2;
}

int getFile(int position)
{
    // Rank is second digit of position and we have positions where second number
    // so we subtract 1 to get number from 0 - 7 is 0 or 9 as OFFBOARD
    return position % 10 - 1;
}

int tileToIndex(const std::string &position)
{
    if (position.length() != 2)
        return OFFBOARD;

    if ('a' > position[0] || position[0] > 'h' || '1' > position[1] || position[1] > '8')
        return OFFBOARD;

    int file = position[0] - 'a';
    int rank = position[1] - '1';

    return 21 + file + rank * 10;
}

std::string indexToTile(int index)
{
    std::string res;

    int file = index % 10;

    int rank = index / 10;

    if (1 > file || file > 8 || 2 > rank || rank > 9)
        return "OFFBOARD";

    res.push_back(file - 1 + 'a');
    res.push_back(rank - 2 + '1');

    return res;
}

bool isOffBoard(int position)
{
    if (position % 10 == 0 || position % 10 == 9)
        return true;
    if (0 <= position && position <= 19)
        return true;
    if (100 <= position && position <= 119)
        return true;
    return false;
}