#include "CBoard.h"

CBoard::CBoard()
{
    readFEN(START_FEN);
}

std::ostream &CBoard::print(std::ostream &os) const
{
    os << "   A B C D E F G H\n"
       << std::endl;
    for (int i = 7; i >= 0; i--)
    {
        os << i + 1 << "  ";
        for (int j = A1; j <= H1; j++)
        {
            os << *Board[j + i * 10] << ' ';
        }
        os << " " << i + 1 << std::endl;
    }
    os << "\n   A B C D E F G H" << std::endl;
    return os;
}

bool CBoard::readFEN(const std::string &fen)
{
    WhiteScore = 0;
    BlackScore = 0;
    HistoryIndex = 0;
    History = {};
    WhitePieces = {};
    BlackPieces = {};
    Plies = 0;
    Turns = 1;
    FiftyTurns = 0;
    WhiteKing = E1;
    BlackKing = E8;
    Side = EColor::WHITE;
    EnPassant = EMPTY;
    Castling = 0xF;

    for (int i = 0; i < 120; i++)
        Board[i] = std::make_shared<COffboard>(COffboard(*this, i));

    for (int i = 0; i < 13; i++)
        PiecesCount[i] = 0;

    std::istringstream iss(fen);
    std::string board;
    char whiteTurn;
    std::string castling;
    std::string enPassant;
    int ply;
    int turn;

    iss >> board >> whiteTurn >> castling >> enPassant >> ply >> turn;

    int position = A8;
    int rank = 8;
    int file = 0;

    for (auto i = board.cbegin(); i != board.cend() && rank > 0; i++)
    {
        if (*i == ' ')
            break;
        switch (*i)
        {
        case 'P':
            Board[position] = std::make_shared<CPawn>(CPawn(*this, position, EColor::WHITE));
            WhitePieces.push_back(Board[position]);
            if (++(PiecesCount[P]) > 10)
                return false;
            position++;
            file++;
            break;
        case 'N':
            Board[position] = std::make_shared<CKnight>(CKnight(*this, position, EColor::WHITE));
            WhitePieces.push_back(Board[position]);
            if (++(PiecesCount[N]) > 10)
                return false;
            position++;
            file++;
            break;
        case 'B':
            Board[position] = std::make_shared<CBishop>(CBishop(*this, position, EColor::WHITE));
            WhitePieces.push_back(Board[position]);
            if (++(PiecesCount[B]) > 10)
                return false;
            position++;
            file++;
            break;
        case 'R':
            Board[position] = std::make_shared<CRook>(CRook(*this, position, EColor::WHITE));
            WhitePieces.push_back(Board[position]);
            if (++(PiecesCount[R]) > 10)
                return false;
            position++;
            file++;
            break;
        case 'Q':
            Board[position] = std::make_shared<CQueen>(CQueen(*this, position, EColor::WHITE));
            WhitePieces.push_back(Board[position]);
            if (++(PiecesCount[Q]) > 10)
                return false;
            position++;
            file++;
            break;
        case 'K':
            Board[position] = std::make_shared<CKing>(CKing(*this, position, EColor::WHITE));
            WhitePieces.push_back(Board[position]);
            WhiteKing = position;
            if (++(PiecesCount[K]) > 1)
                return false;
            position++;
            file++;
            break;

        case 'p':
            Board[position] = std::make_shared<CPawn>(CPawn(*this, position, EColor::BLACK));
            BlackPieces.push_back(Board[position]);
            if (++(PiecesCount[p]) > 10)
                return false;
            position++;
            file++;
            break;
        case 'n':
            Board[position] = std::make_shared<CKnight>(CKnight(*this, position, EColor::BLACK));
            BlackPieces.push_back(Board[position]);
            if (++(PiecesCount[n]) > 10)
                return false;
            position++;
            file++;
            break;
        case 'b':
            Board[position] = std::make_shared<CBishop>(CBishop(*this, position, EColor::BLACK));
            BlackPieces.push_back(Board[position]);
            if (++(PiecesCount[b]) > 10)
                return false;
            position++;
            file++;
            break;
        case 'r':
            Board[position] = std::make_shared<CRook>(CRook(*this, position, EColor::BLACK));
            BlackPieces.push_back(Board[position]);
            if (++(PiecesCount[r]) > 10)
                return false;
            position++;
            file++;
            break;
        case 'q':
            Board[position] = std::make_shared<CQueen>(CQueen(*this, position, EColor::BLACK));
            BlackPieces.push_back(Board[position]);
            if (++(PiecesCount[q]) > 10)
                return false;
            position++;
            file++;
            break;
        case 'k':
            Board[position] = std::make_shared<CKing>(CKing(*this, position, EColor::BLACK));
            BlackPieces.push_back(Board[position]);
            BlackKing = position;
            if (++(PiecesCount[k]) > 10)
                return false;
            position++;
            file++;
            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            for (int j = 0; j < (*i - '0'); j++)
            {
                Board[position] = std::make_shared<CEmpty>(CEmpty(*this, position));
                position++;
                file++;
            }
            break;

        case '/':
            if (file != 8)
                return false;
            file = 0;
            position -= 18;
            rank--;
            break;

        default:
            return false;
        }
    }

    if (rank != 1 || file != 8)
        return false;

    if (whiteTurn == 'w')
        Side = EColor::WHITE;
    else if (whiteTurn == 'b')
        Side = EColor::BLACK;
    else
        return false;

    Castling = NO_CASTLE;
    for (char i : castling)
    {
        if (i == '-')
            break;
        switch (i)
        {
        case 'K':
            Castling |= WHITE_KING_CASTLE;
            break;
        case 'Q':
            Castling |= WHITE_QUEEN_CASTLE;
            break;
        case 'k':
            Castling |= BLACK_KING_CASTLE;
            break;
        case 'q':
            Castling |= BLACK_QUEEN_CASTLE;
            break;
        default:
            return false;
        }
    }

    if (enPassant == "-")
        EnPassant = EMPTY;
    else if ((EnPassant = tileToIndex(enPassant)) == OFFBOARD)
        return false;

    if (ply >= 0)
    {
        FiftyTurns = ply / 2;
        Plies = ply;
    }
    else
        return false;
    if (turn >= 1)
        Turns = turn;
    else
        return false;

    if (fen != createFEN())
        return false;
    initialScore();
    return true;
}

std::string CBoard::createFEN() const
{
    std::string fen;
    int code;
    int count = 0;
    for (int i = 7; i >= 0; i--)
    {
        for (int j = A1; j <= H1; j++)
        {
            code = Board[i * 10 + j]->getCode();
            if (code != EMPTY)
                fen.push_back(PIECE_CHAR_CODE[code]);
            else
            {
                for (; j <= H1 && Board[i * 10 + j]->getCode() == EMPTY; j++)
                    count++;
                j--;
                fen.push_back(count + '0');
                count = 0;
            }
        }
        fen.push_back('/');
    }
    fen.pop_back();

    fen.push_back(' ');
    fen.push_back(Side == EColor::WHITE ? 'w' : 'b');
    fen.push_back(' ');
    if (Castling & WHITE_KING_CASTLE)
        fen.push_back('K');
    if (Castling & WHITE_QUEEN_CASTLE)
        fen.push_back('Q');
    if (Castling & BLACK_KING_CASTLE)
        fen.push_back('k');
    if (Castling & BLACK_QUEEN_CASTLE)
        fen.push_back('q');
    if (!Castling)
        fen.push_back('-');

    fen.push_back(' ');
    if (EnPassant == EMPTY)
        fen.push_back('-');
    else
        fen += indexToTile(EnPassant);

    fen.push_back(' ');
    fen += std::to_string(Plies);

    fen.push_back(' ');
    fen += std::to_string(Turns);
    return fen;
}

bool CBoard::tileAttacked(EColor attacker, int tile) const
{

    if (attacker == EColor::WHITE)
    {
        if (Board[tile - 9]->getCode() == P || Board[tile - 11]->getCode() == P)
            return true;
    }
    else
    {
        if (Board[tile + 9]->getCode() == p || Board[tile + 11]->getCode() == p)
            return true;
    }

    for (int i : KNIGHT_ATTACKS)
    {
        if (Board[tile + i]->getPiece() == EPiece::KNIGHT && Board[tile + i]->getColor() == attacker)
            return true;
    }

    int tempTile;
    EPiece piece;
    EColor color;

    for (int i : ROOK_ATTACKS)
    {
        tempTile = tile + i;
        while (!isOffboard(tempTile))
        {
            piece = Board[tempTile]->getPiece();
            color = Board[tempTile]->getColor();
            if (piece != EPiece::EMPTY)
            {
                if ((piece == EPiece::ROOK || piece == EPiece::QUEEN) && color == attacker)
                    return true;
                break;
            }
            tempTile += i;
        }
    }

    for (int i : BISHOP_ATTACKS)
    {
        tempTile = tile + i;
        while (!isOffboard(tempTile))
        {
            piece = Board[tempTile]->getPiece();
            color = Board[tempTile]->getColor();
            if (piece != EPiece::EMPTY)
            {
                if ((piece == EPiece::BISHOP || piece == EPiece::QUEEN) && color == attacker)
                    return true;
                break;
            }
            tempTile += i;
        }
    }

    for (int i : KING_ATTACKS)
    {
        if (Board[tile + i]->getPiece() == EPiece::KING && Board[tile + i]->getColor() == attacker)
            return true;
    }

    return false;
}

bool CBoard::isEmpty(int index) const
{
    return Board[index]->getPiece() == EPiece::EMPTY;
}

bool CBoard::isOffboard(int index) const
{
    return Board[index]->getPiece() == EPiece::OFFBOARD;
}

const std::shared_ptr<CPiece> &CBoard::operator[](int index) const
{
    return Board[index];
}

std::shared_ptr<CPiece> &CBoard::operator[](int index)
{
    return Board[index];
}

bool CBoard::removePiece(int index)
{
    EColor targetColor = Board[index]->getColor();
    int targetCode = Board[index]->getCode();
    if (--(PiecesCount[targetCode]) < 0)
        throw std::logic_error("Cannot remove not existing piece");

    if (isOffboard(index) || isEmpty(index))
        throw std::logic_error("Cannot remove piece off board or empty piece");

    if (targetColor == EColor::WHITE)
    {
        WhitePieces.remove(Board[index]);
        WhiteScore -= PIECE_SCORE[targetCode];
    }
    else
    {
        BlackPieces.remove(Board[index]);
        BlackScore -= PIECE_SCORE[targetCode];
    }

    Board[index] = std::make_shared<CEmpty>(CEmpty(*this, index));
    return true;
}

bool CBoard::addPiece(int index, EPiece piece, EColor color)
{
    if (!(Board[index]->getPiece() == EPiece::EMPTY))
        throw std::runtime_error("Cannot add piece to occupied tile");

    std::shared_ptr<CPiece> target;
    if (piece == EPiece::PAWN)
        target = std::make_shared<CPawn>(CPawn(*this, index, color));
    else if (piece == EPiece::KNIGHT)
        target = std::make_shared<CKnight>(CKnight(*this, index, color));
    else if (piece == EPiece::ROOK)
        target = std::make_shared<CRook>(CRook(*this, index, color));
    else if (piece == EPiece::BISHOP)
        target = std::make_shared<CBishop>(CBishop(*this, index, color));
    else if (piece == EPiece::QUEEN)
        target = std::make_shared<CQueen>(CQueen(*this, index, color));
    else if (piece == EPiece::KING)
        target = std::make_shared<CKing>(CKing(*this, index, color));
    else
        throw std::logic_error("Cannot add empty or offboard piece");

    Board[index] = target;

    if (++(PiecesCount[target->getCode()]) > 10)
        throw std::logic_error("Cannot add more pieces");

    if (color == EColor::WHITE)
    {
        WhitePieces.push_back(target);
        WhiteScore += PIECE_SCORE[target->getCode()];
    }
    else
    {
        BlackPieces.push_back(target);
        BlackScore += PIECE_SCORE[target->getCode()];
    }
    return true;
}

bool CBoard::movePiece(int from, int to)
{
    if (isOffboard(from) || isOffboard(to) || !isEmpty(to))
        throw std::runtime_error("Cannot move from or to offboard piece");

    Board[from]->setCoord(to);
    Board[to] = Board[from];
    Board[from] = std::make_shared<CEmpty>(CEmpty(*this, from));

    return true;
}

bool CBoard::makeMove(const CMove &move)
{
    CHistory undo;
    History.push_back(undo);

    int from = move.getFrom();
    int to = move.getTo();

    // If the king is moved change king position
    if (Board[from]->getPiece() == EPiece::KING)
    {
        if (move.isWhiteMove())
        {
            WhiteKing = to;
        }
        else
        {
            BlackKing = to;
        }
    }

    // If the move is an en passant capture remove the pawn
    if (move.isEnPassant())
    {
        if (move.isWhiteMove())
            removePiece(to - 10);
        else
            removePiece(to + 10);
    }

    // If the move is castling move, move rook
    if (move.isCastling())
    {
        switch (to)
        {
        case C1:
            movePiece(A1, D1);
            break;
        case C8:
            movePiece(A8, D8);
            break;
        case G1:
            movePiece(H1, F1);
            break;
        case G8:
            movePiece(H8, F8);
            break;
        default:
            throw std::logic_error("Invalid castling move");
        }
    }

    // Store board state
    History[HistoryIndex].Move = move;
    History[HistoryIndex].FiftyTurns = FiftyTurns;
    History[HistoryIndex].EnPassant = EnPassant;
    History[HistoryIndex].Castling = Castling;

    // Change if castling permissions
    if (from == A1 || to == A1)
        Castling &= 0xBU;
    if (from == H1 || to == H1)
        Castling &= 0x7U;
    if (from == A8 || to == A8)
        Castling &= 0xEU;
    if (from == H8 || to == H8)
        Castling &= 0xDU;
    if (from == E1 || to == E1)
        Castling &= 0x3U;
    if (from == E8 || to == E8)
        Castling &= 0xCU;

    EnPassant = EMPTY;

    // If black increment turns;
    if (Side == EColor::BLACK)
    {
        Turns++;
        FiftyTurns++;
    }
    // Increment ply after move
    Plies++;
    HistoryIndex++;

    // If move was a capturing move
    if (move.getCapture() != EPiece::EMPTY && !move.isEnPassant())
    {
        removePiece(to);
        FiftyTurns = 0;
    }

    // If moved piece was pawn
    if (Board[from]->getPiece() == EPiece::PAWN)
    {
        FiftyTurns = 0;
        if (move.isPawnTwoPush())
        {
            if (move.isWhiteMove())
            {
                EnPassant = from + 10;
                //                assert(getRank(EnPassant) == RANK_3);
            }
            else
            {
                EnPassant = from - 10;
                //                assert(getRank(EnPassant) == RANK_6);
            }
        }
    }

    movePiece(from, to);

    // If it is a promotion move
    if (move.getPromotion() != EPiece::EMPTY)
    {
        removePiece(to);
        addPiece(to, move.getPromotion(), move.getColor());
    }

    // Used for checking if after the move player is in check (illegal move)
    int king;
    if (Side == EColor::WHITE)
        king = WhiteKing;
    else
        king = BlackKing;

    Side = OppositeSide(Side);

    // If the move is illegal undo it
    if (tileAttacked(Side, king))
    {
        undoMove();
        return false;
    }

    // If the game is in checkmate
    if (isInCheck() && generateMovesForSide().empty())
        Checkmate = true;

    StateKey = HashKeys.generateStateKey(Board);

    return true;
}

bool CBoard::undoMove()
{
    // Decrement turns and plies
    if (Side == EColor::WHITE)
    {
        Turns--;
        FiftyTurns--;
    }
    Plies--;
    HistoryIndex--;

    CHistory undo = History[HistoryIndex];
    // Move to be undone
    CMove undoMove = undo.Move;
    int from = undoMove.getFrom();
    int to = undoMove.getTo();

    Castling = undo.Castling;
    FiftyTurns = undo.FiftyTurns;
    EnPassant = undo.EnPassant;

    Side = OppositeSide(Side);

    // If the undo move is an en passant capture add the pawn back
    if (undoMove.isEnPassant())
    {
        if (undoMove.isWhiteMove())
            addPiece(to - 10, EPiece::PAWN, EColor::BLACK);
        else
            addPiece(to + 10, EPiece::PAWN, EColor::WHITE);
    }

    // If the move is an castling move, move back the rook
    if (undoMove.isCastling())
    {
        switch (to)
        {
        case C1:
            movePiece(D1, A1);
            break;
        case C8:
            movePiece(D8, A8);
            break;
        case G1:
            movePiece(F1, H1);
            break;
        case G8:
            movePiece(F8, H8);
            break;
        default:
            throw std::logic_error("Invalid castling move");
        }
    }

    movePiece(to, from);

    // If king was moved change king position
    if (Board[from]->getPiece() == EPiece::KING)
    {
        if (undoMove.isWhiteMove())
        {
            WhiteKing = from;
        }
        else
        {
            BlackKing = from;
        }
    }

    // If the move was a capture, add the captured piece back
    if (undoMove.getCapture() != EPiece::EMPTY && !undoMove.isEnPassant())
    {
        addPiece(to, undoMove.getCapture(), OppositeSide(Side));
    }

    // If the move was a promotion, remove promoted piece and add a pawn
    if (undoMove.getPromotion() != EPiece::EMPTY)
    {
        removePiece(from);
        addPiece(from, EPiece::PAWN, Side);
    }

    return true;
}

std::list<CMove> CBoard::generateMovesForSide()
{
    std::list<CMove> moveList;
    if (Side == EColor::WHITE)
        for (const auto &i : WhitePieces)
            moveList.splice(moveList.end(), i->moveList());
    else
        for (const auto &i : BlackPieces)
            moveList.splice(moveList.end(), i->moveList());

    return moveList;
}

std::list<CMove> CBoard::generateCaptureMovesForSide()
{
    std::list<CMove> moveList;
    if (Side == EColor::WHITE)
        for (const auto &i : WhitePieces)
            moveList.splice(moveList.end(), i->captureMoveList());
    else
        for (const auto &i : BlackPieces)
            moveList.splice(moveList.end(), i->captureMoveList());

    return moveList;
}

void CBoard::initialScore()
{
    WhiteScore = 0;
    BlackScore = 0;
    for (int i = 7; i >= 0; i--)
    {
        for (int j = A1; j <= H1; j++)
        {
            if (Board[j + i * 10]->getColor() == EColor::WHITE)
                WhiteScore += PIECE_SCORE[Board[j + i * 10]->getCode()];
            if (Board[j + i * 10]->getColor() == EColor::BLACK)
                BlackScore += PIECE_SCORE[Board[j + i * 10]->getCode()];
        }
    }
}

bool CBoard::isDraw()
{
    int totalPieces = WhitePieces.size() + BlackPieces.size();
    int whiteBishops = 0;
    int blackBishops = 0;
    int whiteKnights = 0;
    int blackKnights = 0;

    int king = Side == EColor::WHITE ? WhiteKing : BlackKing;

    for (const auto &i : WhitePieces)
    {
        if (i->getPiece() == EPiece::BISHOP)
            whiteBishops++;
        if (i->getPiece() == EPiece::KNIGHT)
            whiteKnights++;
    }

    for (const auto &i : BlackPieces)
    {
        if (i->getPiece() == EPiece::BISHOP)
            blackBishops++;
        if (i->getPiece() == EPiece::KNIGHT)
            blackKnights++;
    }

    if (FiftyTurns >= 50)
        return true;
    // Impossible checkmate
    else if (whiteBishops == 1 && blackBishops == 1 && totalPieces == 4)
        return true;
    else if ((whiteKnights == 1 || whiteBishops == 1 || blackKnights == 1 || blackBishops == 1) && totalPieces == 3)
        return true;
    else if (totalPieces == 2)
        return true;
    // Stalemate
    else if (generateMovesForSide().empty() && !tileAttacked(OppositeSide(Side), king))
        return true;
    else
        return false;
}

bool CBoard::noPossibleMoves()
{
    std::list<CMove> moveList = generateMovesForSide();
    for (const auto &i : moveList)
    {
        if (makeMove(i))
        {
            undoMove();
            return false;
        }
    }
    return true;
}

bool CBoard::isPossibleMove(const CMove &move)
{
    std::list<CMove> moveList = generateMovesForSide();
    for (const auto &i : moveList)
    {
        if (!makeMove(i))
            continue;
        undoMove();
        if (move.exactMatch(i))
            return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const CBoard &board)
{
    std::string fen = board.createFEN();
    os << fen << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, CBoard &board)
{
    std::string line;
    getline(is, line);
    if (is.fail())
        return is;

    if (!board.readFEN(line))
    {
        is.setstate(std::ios::failbit);
        return is;
    }
    return is;
}

void CBoard::restart()
{
    if (!readFEN(START_FEN))
        throw std::runtime_error("Error during restarting game.");
}

int CBoard::getPlies() const
{
    return Plies;
}

int CBoard::getWhiteKing() const
{
    return WhiteKing;
}

int CBoard::getBlackKing() const
{
    return BlackKing;
}

const std::list<std::shared_ptr<CPiece>> &CBoard::getWhitePieces() const
{
    return WhitePieces;
}

const std::list<std::shared_ptr<CPiece>> &CBoard::getBlackPieces() const
{
    return BlackPieces;
}

int CBoard::getWhiteScore() const
{
    return WhiteScore;
}

int CBoard::getBlackScore() const
{
    return BlackScore;
}

unsigned int CBoard::getCastling() const
{
    return Castling;
}

int CBoard::getEnPassant() const
{
    return EnPassant;
}

EColor CBoard::getSide() const
{
    return Side;
}

bool CBoard::isInCheck() const
{
    return tileAttacked(OppositeSide(Side), Side == EColor::WHITE ? WhiteKing : BlackKing);
}

uint64_t CBoard::getStateKey() const
{
    return StateKey;
}