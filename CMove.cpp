#include "CMove.h"

CMove::CMove(EColor color, int from, int to, EPiece capture, bool pawnStart, bool enPassant, EPiece promotion, bool castle, int score)
    : Side(color), From(from), To(to), Capture(capture), PawnTwoPush(pawnStart), EnPassant(enPassant), Promotion(promotion), Castle(castle), Score(score) {}

std::ostream &CMove::print(std::ostream &os) const
{
    os << indexToTile(From) << indexToTile(To);
    if (Promotion != EPiece::EMPTY)
        os << Promotion;
    return os;
}

std::ostream &operator<<(std::ostream &os, const CMove &self)
{
    self.print(os);
    return os;
}

std::istream &operator>>(std::istream &is, CMove &self)
{
    std::string in;
    is >> in;

    if (is.eof() || is.fail())
        return is;
    if (in.length() > 5 || in.length() < 4)
    {
        is.setstate((std::ios::failbit));
        return is;
    }

    std::string fromFR = "", toFR = "";
    fromFR += in[0];
    fromFR += in[1];
    toFR += in[2];
    toFR += in[3];

    in.push_back('\n');

    std::string prom = "";
    prom += in[4];

    int fromI = tileToIndex(fromFR), toI = tileToIndex(toFR);

    if (fromI == OFFBOARD || toI == OFFBOARD)
    {
        is.setstate(std::ios::failbit);
        return is;
    }

    self.From = fromI;
    self.To = toI;

    if (prom[0] == '\n')
        return is;

    CConfig &config = CConfig::getInstance();

    if (prom != config.getBlackQueen() && prom != config.getWhiteQueen() && prom != config.getBlackRook() &&
        prom != config.getWhiteRook() && prom != config.getBlackBishop() && prom != config.getWhiteBishop() &&
        prom != config.getWhiteKnight() && prom != config.getBlackKnight())
    {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (prom == config.getBlackQueen() || prom == config.getWhiteQueen())
        self.Promotion = EPiece::QUEEN;
    else if (prom == config.getBlackRook() || prom == config.getWhiteRook())
        self.Promotion = EPiece::ROOK;
    else if (prom == config.getBlackBishop() || prom == config.getWhiteBishop())
        self.Promotion = EPiece::BISHOP;
    else
        self.Promotion = EPiece::KNIGHT;

    return is;
}

bool CMove::operator==(const CMove &other) const
{
    if (From != other.From || To != other.To || Promotion != other.Promotion)
        return false;
    else
        return true;
}

bool CMove::exactMatch(const CMove &other) const
{
    if (Side != other.Side || From != other.From || To != other.To ||
        Promotion != other.Promotion || Capture != other.Capture ||
        PawnTwoPush != other.PawnTwoPush || EnPassant != other.EnPassant ||
        Castle != other.Castle)
        return false;
    else
        return true;
}

void CMove::setFrom(int from)
{
    From = from;
}

void CMove::setTo(int to)
{
    To = to;
}

bool CMove::isEnPassant() const
{
    return EnPassant;
}

bool CMove::isPawnTwoPush() const
{
    return PawnTwoPush;
}

bool CMove::isCastling() const
{
    return Castle;
}

bool CMove::isWhiteMove() const
{
    return Side == EColor::WHITE;
}

int CMove::getFrom() const
{
    return From;
}

int CMove::getTo() const
{
    return To;
}

EPiece CMove::getCapture() const
{
    return Capture;
}

EPiece CMove::getPromotion() const
{
    return Promotion;
}

EColor CMove::getColor() const
{
    return Side;
}

void CMove::setScore(int score)
{
    Score = score;
}

bool CMove::isValid() const
{
    return From != OFFBOARD && To != OFFBOARD;
}

bool CMove::isCapture() const
{
    return Capture != EPiece::EMPTY;
}

bool CMove::operator<(const CMove &other) const
{
    return other.Score < Score;
}

CMove pushMove(EColor color, int from, int to)
{
    return CMove(color, from, to, EPiece::EMPTY, false, false, EPiece::EMPTY, false, 0);
}

CMove captureMove(EPiece piece, EColor color, int from, int to, EPiece capture, bool enPassant)
{
    return CMove(color, from, to, capture, false, enPassant, EPiece::EMPTY, false,
                 CAPTURE_SCORE[EPieceToCode(capture)] + 6 - (CAPTURE_SCORE[EPieceToCode(piece)] / 100) + 1000000);
}

CMove pawnTwoForward(EColor color, int from, int to)
{
    return CMove(color, from, to, EPiece::EMPTY, true, false, EPiece::EMPTY, false, 0);
}

CMove promotionMove(EPiece piece, EColor color, int from, int to, EPiece capture, EPiece promotion)
{
    int scr = 0;
    if (capture != EPiece::EMPTY)
        scr = CAPTURE_SCORE[EPieceToCode(capture)] + 6 - (CAPTURE_SCORE[EPieceToCode(piece)] / 100) + 1000000;
    return CMove(color, from, to, capture, false, false, promotion, false, scr);
}

CMove castleMove(EColor color, int castling)
{
    if (castling & WHITE_KING_CASTLE)
        return CMove(color, E1, G1, EPiece::EMPTY, false, false, EPiece::EMPTY, true, 0);
    else if (castling & WHITE_QUEEN_CASTLE)
        return CMove(color, E1, C1, EPiece::EMPTY, false, false, EPiece::EMPTY, true, 0);
    else if (castling & BLACK_KING_CASTLE)
        return CMove(color, E8, G8, EPiece::EMPTY, false, false, EPiece::EMPTY, true, 0);
    else if (castling & BLACK_QUEEN_CASTLE)
        return CMove(color, E8, C8, EPiece::EMPTY, false, false, EPiece::EMPTY, true, 0);
    else
        throw std::logic_error("Cannot castle");
}
