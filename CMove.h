#pragma once

#include <iostream>
#include <string>

#include "EPiece.h"
#include "EColor.h"
#include "ETile.h"
#include "EConst.h"
#include "CConfig.h"

/**
 * Class CMove representing a move
 */
class CMove
{
private:
    // The side of the player making the move
    EColor Side = EColor::WHITE;

    // The starting position of the move
    int From = 0;

    // The destination position of the move
    int To = 0;

    // The piece being captured (if any)
    EPiece Capture = EPiece::EMPTY;

    // True if the move is a pawn two-square push
    bool PawnTwoPush = false;

    // True if the move is an en passant capture
    bool EnPassant = false;

    // The piece resulting from a pawn promotion (if any)
    EPiece Promotion = EPiece::EMPTY;

    // True if the move is a castling move
    bool Castle = false;

    // The score associated with the move
    int Score = 0;

public:
    CMove() = default;

    explicit CMove(EColor color, int from, int to, EPiece capture = EPiece::EMPTY, bool pawnStart = false,
                   bool enPassant = false, EPiece promotion = EPiece::EMPTY, bool castle = false, int score = 0);

    /**
     *  Prints the move to the output stream.
     *  @param os The output stream.
     *  @return The modified output stream.
     */
    std::ostream &print(std::ostream &os) const;

    /**
     *  Overloaded stream insertion operator for CMove class.
     *  @param os The output stream.
     *  @param self The CMove object to be inserted into the stream.
     *  @return The modified output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const CMove &self);

    /**
     *   Overloaded stream extraction operator for CMove class.
     *   @param is The input stream.
     *   @param self The CMove object to store the extracted move.
     *   @return The modified input stream.
     */
    friend std::istream &operator>>(std::istream &is, CMove &self);

    /**
     *   Checks if two moves are equal.
     *   @param other The other CMove object to compare with.
     *   @return True if the moves are equal, false otherwise.
     */
    bool operator==(const CMove &other) const;

    /**
     *   Checks if two moves have an exact match.
     *   @param other The other CMove object to compare with.
     *   @return True if the moves have an exact match, false otherwise.
     */
    bool exactMatch(const CMove &other) const;

    /**
     *  Checks if the move is an en passant capture.
     *  @return True if the move is an en passant capture, false otherwise.
     */
    bool isEnPassant() const;

    /**
     *  Checks if the move is a pawn two-square push.
     *  @return True if the move is a pawn two-square push, false otherwise.
     */
    bool isPawnTwoPush() const;

    /**
     *  Checks if the move is a castling move.
     *  @return True if the move is a castling move, false otherwise.
     */
    bool isCastling() const;

    /**
     *  Checks if the move is a white move.
     *  @return True if the move is a white move, false otherwise.
     */
    bool isWhiteMove() const;

    /**
     *  Sets the 'from' position of the move.
     *  @param from The 'from' position to be set.
     */
    void setFrom(int from);

    /**
     *  Sets the 'to' position of the move.
     *  @param to The 'to' position to be set.
     */
    void setTo(int to);

    /**
     *  Gets the 'from' position of the move.
     *  @return The 'from' position of the move.
     */
    int getFrom() const;

    /**
     *  Gets the 'to' position of the move.
     *  @return The 'to' position of the move.
     */
    int getTo() const;

    /**
     *  Gets the piece being captured (if any).
     *  @return The piece being captured.
     */
    EPiece getCapture() const;

    /**
     *  Gets the piece resulting from a pawn promotion (if any).
     *  @return The piece resulting from a pawn promotion.
     */
    EPiece getPromotion() const;

    /**
     *  Gets the color of the player making the move.
     *  @return The color of the player making the move.
     */
    EColor getColor() const;

    /**
     *  Sets the score associated with the move.
     *  @param score The score to be set.
     */
    void setScore(int score);

    /**
     *  Checks if the move is valid.
     *  @return True if the move is valid, false otherwise.
     */
    bool isValid() const;

    /**
     *  Checks if the move is a capture move.
     *  @return True if the move is a capture move, false otherwise.
     */
    bool isCapture() const;

    /**
     *  Checks if one move is less than another move.
     *  @param other The other CMove object to compare with.
     *  @return True if the first move is less than the second move, false otherwise.
     */
    bool operator<(const CMove &other) const;
};

/**
 *   Creates a push move (move without capture) with the specified parameters.
 *   @param color The color of the player making the move.
 *   @param from The starting position of the move.
 *   @param to The destination position of the move.
 *   @return The created CMove object representing the push move.
 */
CMove pushMove(EColor color, int from, int to);

/**
 *   Creates a capture move with the specified parameters.
 *   @param piece The piece making the capture.
 *   @param color The color of the player making the move.
 *   @param from The starting position of the move.
 *   @param to The destination position of the move.
 *   @param capture The piece being captured.
 *   @param enPassant True if the move is an en passant capture.
 *   @return The created CMove object representing the capture move.
 */
CMove captureMove(EPiece piece, EColor color, int from, int to, EPiece capture, bool enPassant = false);

/**
 *   Creates a move with a pawn two-square push.
 *   @param color The color of the player making the move.
 *   @param from The starting position of the move.
 *   @param to The destination position of the move.
 *   @return The created CMove object representing the pawn two-square push move.
 */
CMove pawnTwoForward(EColor color, int from, int to);

/**
 *   Creates a promotion move with the specified parameters.
 *   @param piece The piece making the promotion.
 *   @param color The color of the player making the move.
 *   @param from The starting position of the move.
 *   @param to The destination position of the move.
 *   @param capture The piece being captured (if any).
 *   @param promotion The piece resulting from the promotion.
 *   @return The created CMove object representing the promotion move.
 */
CMove promotionMove(EPiece piece, EColor color, int from, int to, EPiece capture, EPiece promotion);

/**
 *   Creates a castling move with the specified parameters.
 *   @param color The color of the player making the move.
 *   @param castling The castling type.
 *   @return The created CMove object representing the castling move.
 *   @throws std::logic_error If the castling move is not valid.
 */
CMove castleMove(EColor color, int castling);