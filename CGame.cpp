#include "CGame.h"

CGame::CGame(CInterface &interface)
    : Interface(interface)
{
}

bool CGame::makeTurn()
{
    // If game has ended
    if (End)
    {
        return false;
    }

    // If game has ended after this turn
    if (!(Board.getSide() == EColor::WHITE ? White->takeTurn() : Black->takeTurn()))
    {
        End = true;
        return false;
    }

    // If other player is computer, make its turn
    if (Board.getSide() == EColor::WHITE ? White->isComputer() : Black->isComputer())
    {
        if (!(Board.getSide() == EColor::WHITE ? White->takeTurn() : Black->takeTurn()))
        {
            End = true;
            return false;
        }
    }
    return true;
}

bool CGame::initializePlayerVsPlayer()
{
    White = std::make_unique<CHuman>(Interface, Board, EColor::WHITE);
    Black = std::make_unique<CHuman>(Interface, Board, EColor::BLACK);

    Initialized = true;
    return true;
}

bool CGame::initializePlayerVsComputer(EColor computerSide, std::string difficulty)
{
    if (computerSide == EColor::WHITE)
    {
        White = std::make_unique<CAI>(Interface, Board, EColor::WHITE, difficulty);
        Black = std::make_unique<CHuman>(Interface, Board, EColor::BLACK);
    }
    else if (computerSide == EColor::BLACK)
    {
        White = std::make_unique<CHuman>(Interface, Board, EColor::WHITE);
        Black = std::make_unique<CAI>(Interface, Board, EColor::BLACK, difficulty);
    }
    else
        throw std::runtime_error("Error during creating a game.");

    if (Board.getSide() == EColor::WHITE ? White->isComputer() : Black->isComputer())
    {
        if (!(Board.getSide() == EColor::WHITE ? White->takeTurn() : Black->takeTurn()))
        {
            End = true;
            return false;
        }
    }

    Initialized = true;
    return true;
}

std::ostream &CGame::print(std::ostream &os)
{
    if (Board.getSide() == EColor::WHITE)
        Interface.promptMessage("Side to move: WHITE\n");
    else
        Interface.promptMessage("Side to move: BLACK\n");
    Board.print(Interface.getOstream());
    return os;
}

std::ostream &operator<<(std::ostream &os, const CGame &self)
{
    os << self.Board;
    std::string difficulty = "";
    if (self.White->isComputer())
    {
        os << 'c';
        difficulty = self.White->getDifficulty();
    }
    else
        os << 'p';
    if (self.Black->isComputer())
    {
        os << 'c';
        difficulty = self.Black->getDifficulty();
    }
    else
        os << 'p';

    if (self.White->isComputer() || self.Black->isComputer())
        os << " " << difficulty << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, CGame &self)
{
    self.restart();
    if (!(is >> self.Board))
    {
        self.Initialized = false;
        return is;
    }

    std::string difficulty = "";
    char playerOne;
    char playerTwo;

    if (!(is >> playerOne >> playerTwo))
    {
        self.Initialized = false;
        return is;
    }

    if (playerOne == 'c' || playerTwo == 'c')
    {
        if (!(is >> difficulty))
        {
            std::cout << difficulty << std::endl;
            self.Initialized = false;
            return is;
        }
    }

    if (playerOne != 'p' && playerTwo != 'p')
    {
        if (((playerOne == 'c' || playerTwo == 'c') && difficulty != "easy" && difficulty != "medium" && difficulty != "hard"))
        {
            is.setstate(std::ios::failbit);
            self.Initialized = false;
            return is;
        }
    }

    if (playerOne == 'c' && playerTwo == 'c')
    {
        is.setstate(std::ios::failbit);
        self.Initialized = false;
        return is;
    }

    if (playerOne == 'p' && playerTwo == 'p' && difficulty != "")
    {
        is.setstate(std::ios::failbit);
        self.Initialized = false;
        return is;
    }

    if (playerOne == 'p')
        self.White = std::make_unique<CHuman>(self.Interface, self.Board, EColor::WHITE);
    else if (playerOne == 'c')
    {
        self.White = std::make_unique<CAI>(self.Interface, self.Board, EColor::WHITE, difficulty);
    }
    else
    {
        self.Initialized = false;
        is.setstate(std::ios::failbit);
        return is;
    }
    if (playerTwo == 'p')
        self.Black = std::make_unique<CHuman>(self.Interface, self.Board, EColor::BLACK);
    else if (playerTwo == 'c')
    {
        self.Black = std::make_unique<CAI>(self.Interface, self.Board, EColor::BLACK, difficulty);
    }
    else
    {
        self.Initialized = false;
        is.setstate(std::ios::failbit);
        return is;
    }

    if (self.Board.getSide() == EColor::WHITE && self.White->isComputer())
    {
        self.Initialized = false;
        is.setstate(std::ios::failbit);
        return is;
    }

    if (self.Board.getSide() == EColor::BLACK && self.Black->isComputer())
    {
        self.Initialized = false;
        is.setstate(std::ios::failbit);
        return is;
    }

    self.Initialized = true;
    return is;
}

void CGame::restart()
{
    White = nullptr;
    Black = nullptr;
    Initialized = false;
    End = false;
    Board.restart();
}

void CGame::setInitialized(bool init)
{
    Initialized = init;
}

bool CGame::isOver() const
{
    return End;
}

CBoard &CGame::getBoard()
{
    return Board;
}

const CBoard &CGame::getBoard() const
{
    return Board;
}

bool CGame::isInitialized() const
{
    return Initialized;
}

bool CGame::isSaved() const
{
    return Saved;
}

void CGame::setSaved(bool save)
{
    Saved = save;
}