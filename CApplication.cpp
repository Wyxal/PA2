#include "CApplication.h"

CApplication::CApplication(const CInterface &interface)
    : Interface(interface), Game(Interface)
{
    Commands.emplace("play", std::make_unique<CPlay>(Interface,
                                                     " [p|c][p|c] [easy|medium|hard] : initialize the game - first letter is the white player, second black player (all must be lowercase), if a game against computer is initialized a difficulty is needed (example: 'play pc easy' for game as white against black computer with difficulty easy)", Game));
    Commands.emplace("restart", std::make_unique<CRestart>(Interface, " : restarts the game", Game));
    Commands.emplace("save", std::make_unique<CSave>(Interface, " [filename] : saves game to 'filename', filenames cannot contain white space", Game));
    Commands.emplace("load", std::make_unique<CLoad>(Interface, " [filename] : loads 'filename', filenames cannot contain white space space", Game));
    Commands.emplace("move", std::make_unique<CMoves>(CMoves(Interface,
                                                             " [a|b|c|d|e|f|g|h][1|2|3|4|5|6|7|8][a|b|c|d|e|f|g|h][1|2|3|4|5|6|7|8][piece symbol from configuration file] : make a move - first two letters is the position of a piece to be move, following two letters is the position of the destination. If a pawn is going to promote, a piece is needed for a pawn to promote to queen, bishop, rook or knight. (all must be lowercase) (example: move a1b2)", Game)));
    Commands.emplace("board", std::make_unique<CBoards>(CBoards(Interface, " : shows the state of the chess board", Game)));
    Commands.emplace("help", std::make_unique<CHelp>(CHelp(Interface, " : shows s used by this program", Commands)));
    Commands.emplace("quit", std::make_unique<CQuit>(CQuit(Interface, " : quits this program", Game)));
    Commands.emplace("tutorial", std::make_unique<CTutorial>(CTutorial(Interface, " : shows tutorial to chess piece moves and other actions")));
}

int CApplication::run()
{
    while (true)
    {
        std::string command = Interface.promptCommand([this](const std::string &command)
                                                      { return Commands.find(command) != Commands.end(); });
        if (!Commands[command]->execute())
            break;
    }
    return 0;
}