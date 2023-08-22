#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <map>
#include <climits>
#include <iomanip>
#include <vector>
#include <memory>
#include <sstream>
#include <climits>
#include <fstream>

#include "Pieces/CPiece.h"
#include "EColor.h"
#include "Pieces/CKing.h"
#include "Pieces/CQueen.h"
#include "Pieces/CBishop.h"
#include "Pieces/CKnight.h"
#include "Pieces/CRook.h"
#include "Pieces/CPawn.h"
#include "Pieces/COffboard.h"
#include "Pieces/CEmpty.h"
#include "CMove.h"
#include "ETile.h"
#include "CHistory.h"
#include "CHash.h"

class CPiece;

/**
 * Class representing a board
 */
class CBoard
{
private:
    std::shared_ptr<CPiece> Board[120];

    // Castling permissions
    unsigned int Castling = 0xF;

    // Number of plies
    int Plies = 0;

    // Number of turns
    int Turns = 1;

    // Number of turns without capture or pawn moving
    int FiftyTurns = 0;

    // Positions kings
    int WhiteKing = E1;
    int BlackKing = E8;

    // En passant square
    int EnPassant = EMPTY;
    bool Checkmate = false;
    EColor Side = EColor::WHITE;

    // list of piece ordered by color
    std::list<std::shared_ptr<CPiece>> WhitePieces;
    std::list<std::shared_ptr<CPiece>> BlackPieces;

    // White score
    int WhiteScore = 0;
    int BlackScore = 0;

    CHash HashKeys;
    uint64_t StateKey;

    // Used for indexing in History
    int HistoryIndex = 0;
    std::vector<CHistory> History;

    // Count of each pieces
    int PiecesCount[13] = {};

public:
    CBoard();

    /**
     * Prints the current state of the board.
     * @param os the output stream to print the board
     * @return the output stream after printing the board
     */
    std::ostream &print(std::ostream &os) const;

    /**
     * Reads the given FEN (Forsyth–Edwards Notation) and sets up the board accordingly.
     * @param fen the FEN string representing the board position
     * @return true if the FEN was successfully parsed and the board was set up, false otherwise
     */
    bool readFEN(const std::string &fen);

    /**
     * Creates a FEN (Forsyth–Edwards Notation) string representing the current board position.
     * @return the FEN string representing the board position
     */
    std::string createFEN() const;

    /**
     * Checks if a tile is attacked by a certain color.
     * @param attacker the color of the attacking pieces
     * @param tile the tile to check for attack
     * @return true if the tile is attacked by the given color, false otherwise
     */
    bool tileAttacked(EColor attack, int tile) const;

    /**
     * Removes a piece from the board at the specified index.
     *
     * @param index the index of the square where the piece is located
     * @return true if the piece was successfully removed, false otherwise
     * @throws LogicException if the piece to be removed does not exist or if the index is off the board or empty
     */
    bool removePiece(int index);

    /**
     * Adds a piece to the board at the specified index with the given piece type and color.
     *
     * @param index the index of the tile where the piece will be added
     * @param piece the type of piece to be added
     * @param color the color of the piece to be added
     * @return true if the piece was successfully added, false otherwise
     * @throws RuntimeException if the tile is already occupied
     * @throws LogicException if an empty or offboard piece is attempted to be added
     * @throws LogicException if the maximum number of pieces for a specific type is exceeded
     */
    bool addPiece(int index, EPiece piece, EColor color);

    /**
     * Moves a chess piece from one square to another on the board.
     *
     * @param from the starting square of the piece to be moved
     * @param to the destination square where the piece will be moved
     * @return true if the piece was successfully moved, false otherwise
     * @throws std::runtime_error if either the starting or destination square is offboard or not empty
     */
    bool movePiece(int from, int to);

    /**
     * Makes a move on the chess board.
     * @param move the move to be made
     * @return true if the move was successfully made, false if the move was illegal
     * @throws std::logic_error if the move is an invalid castling move
     */
    bool makeMove(const CMove &move);

    /**
     * Undoes the last move on the board.
     * @return true if the move was successfully undone, false otherwise
     */
    bool undoMove();

    /**
     * Retrieves the piece at the specified index on the chess board.
     * @param index the index of the board square
     * @return the piece at the specified index
     */
    const std::shared_ptr<CPiece> &operator[](int index) const;

    /**
     * Retrieves the reference to the chess piece at the specified index on the board.
     * @param index the index of the board square to retrieve the chess piece from
     * @return the reference to the chess piece at the specified index
     */
    std::shared_ptr<CPiece> &operator[](int index);

    /**
     * Generates a list of all possible moves for the current side (White or Black).
     * @return a list of all possible moves for the current side
     */
    std::list<CMove> generateMovesForSide();

    /**
     * Generates a list of capture moves for the current side (White or Black).
     * @return a list of capture moves for the current side
     */
    std::list<CMove> generateCaptureMovesForSide();

    /**
     * Checks if the given move is possible on the current board.
     *
     * @param move the move to be checked
     * @return true if the move is possible, false otherwise
     */
    bool isPossibleMove(const CMove &move);

    /**
     *  Checks if the specified index on the board is empty.
     *  @param index the index of the square to check
     *  @return true if the square is empty, false otherwise
     */
    bool isEmpty(int index) const;

    /**
     *  Gets the 'StateKey' of the move.
     *  @return The 'StateKey' of the move.
     */
    uint64_t getStateKey() const;

    /**
     *  Checks if the specified index is offboard.
     *  @param index the index to check
     *  @return true if the index is offboard, false otherwise
     */
    bool isOffboard(int index) const;

    /**
     * Calculates the initial score of the board based on the current piece positions.
     * The score is calculated separately for white and black pieces.
     * Each piece is assigned a specific score value defined in the PIECE_SCORE array.
     * @see PIECE_SCORE
     */
    void initialScore();

    /**
     * Determines whether the current board position is a draw.
     * @return true if the position is a draw, false otherwise
     */
    bool isDraw();

    /**
     * Returns the number of plies (half-moves) made on the board.
     * @return the number of plies made on the board
     */
    int getPlies() const;

    /**
     * Returns the square index of the white king on the board.
     * @return the square index of the white king
     */
    int getWhiteKing() const;

    /**
     * Returns the square index of the black king on the board.
     * @return the square index of the black king
     */
    int getBlackKing() const;

    /**
     * Returns the list of white pieces on the board.
     * @return the list of white pieces
     */
    const std::list<std::shared_ptr<CPiece>> &getWhitePieces() const;

    /**
     * Returns the list of black pieces on the board.
     * @return the list of black pieces
     */
    const std::list<std::shared_ptr<CPiece>> &getBlackPieces() const;

    /**
     * Returns the score of the white side on the board.
     * @return the score of the white side
     */
    int getWhiteScore() const;

    /**
     * Returns the score of the black side on the board.
     * @return the score of the black side
     */
    int getBlackScore() const;

    /**
     * Returns the castling rights bitmask on the board.
     * @return the castling rights bitmask
     */
    unsigned int getCastling() const;

    /**
     * Returns the en passant square index on the board.
     * @return the en passant square index
     */
    int getEnPassant() const;

    /**
     * Returns the current side to move on the board.
     * @return the current side to move
     */
    EColor getSide() const;

    /**
     * Checks if the current side is in check on the board.
     * @return true if the current side is in check, false otherwise
     */
    bool isInCheck() const;

    /**
     * Checks if the current side to move has any possible moves available.
     * @return true if there are no possible moves for the current side, false otherwise
     */
    bool noPossibleMoves();

    /**
     * Writes the FEN (Forsyth–Edwards Notation) representation of the board to the output stream.
     * @param os the output stream to write the FEN representation
     * @param board the board object to be written
     * @return the output stream after writing the FEN representation
     */
    friend std::ostream &operator<<(std::ostream &os, const CBoard &board);

    /**
     * Reads the FEN (Forsyth–Edwards Notation) representation of the board from the input stream and updates the board accordingly.
     * @param is the input stream to read the FEN representation from
     * @param board the board object to be updated
     * @return the input stream after reading the FEN representation
     */
    friend std::istream &operator>>(std::istream &is, CBoard &board);

    /**
     * Restarts the game by setting up the board with the starting FEN position.
     * @throws std::runtime_error if an error occurs during restarting the game
     */
    void restart();
};