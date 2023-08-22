#pragma once

#include <memory>

#include "CInterface.h"
#include "CBoard.h"
#include "Players/CPlayer.h"
#include "Players/CHuman.h"
#include "Players/CAI.h"

/**
 * Represents a chess game.
 */
class CGame
{
private:
    CInterface &Interface;

    CBoard Board;

    std::unique_ptr<CPlayer> White = nullptr;

    std::unique_ptr<CPlayer> Black = nullptr;

    // If the game is initialized
    bool Initialized = false;

    // If the game has ended
    bool End = false;

    // If the game is saved
    bool Saved = false;

public:
    explicit CGame(CInterface &Interface);

    /**
     * Initializes a player vs player game.
     * @return true if the game was successfully initialized, false otherwise
     */
    bool initializePlayerVsPlayer();

    /**
     * Initializes a player vs computer game.
     * @param computerSide the side of the computer player
     * @param difficulty the difficulty level of the computer player
     * @return true if the game was successfully initialized, false otherwise
     */
    bool initializePlayerVsComputer(EColor computerSide, std::string difficulty);

    /**
     * Makes a turn in the game.
     * @return true if the turn was successfully made, false otherwise
     */
    bool makeTurn();

    /**
     * Sets the initialization state of the game.
     * @param init the initialization state to set
     */
    void setInitialized(bool init);

    /**
     * Sets the saved state of the game.
     * @param save the saved state to set
     */
    void setSaved(bool save);

    /**
     * Restarts the game.
     */
    void restart();

    /**
     * Checks if the game is over.
     * @return true if the game is over, false otherwise
     */
    bool isOver() const;

    /**
     * Checks if the game is saved.
     * @return true if the game is saved, false otherwise
     */
    bool isSaved() const;

    /**
     * Returns the game board.
     * @return the game board
     */
    CBoard &getBoard();

    /**
     * Returns the game board.
     * @return the game board
     */
    const CBoard &getBoard() const;

    /**
     * Checks if the game is initialized.
     * @return true if the game is initialized, false otherwise
     */
    bool isInitialized() const;

    /**
     * Prints the game state.
     * @param os the output stream to print the game state
     * @return the output stream after printing the game state
     */
    std::ostream &print(std::ostream &os);

    /**
     * Overrides the toString method to print the game state.
     * @param os the output stream to print the game state
     * @param self the CGame object
     * @return the output stream after printing the game state
     */
    friend std::ostream &operator<<(std::ostream &os, const CGame &self);

    /**
     * Overrides the input stream operator to read the game state.
     * @param is the input stream to read the game state from
     * @param self the CGame object
     * @return the input stream after reading the game state
     */
    friend std::istream &operator>>(std::istream &is, CGame &self);
};