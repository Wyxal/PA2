#include "CInterface.h"

CInterface::CInterface(std::ostream &out, std::istream &in)
    : Out(out), In(in)
{
}

std::ostream &CInterface::getOstream() const
{
    return Out;
}
std::istream &CInterface::getIstream() const
{
    return In;
}

std::string CInterface::promptCommand(const std::function<bool(const std::string &)> &valid)
{
    std::cout << "Enter a command, for help enter the command 'help':" << std::endl;
    std::string command;
    while (true)
    {
        In >> command;

        if (In.eof())
            return "quit";
        else if (In.fail())
            throw std::runtime_error("Error during inputting command");
        else if (!valid(command))
        {
            std::cout << "Non-existing command, Enter a valid command, for help enter the command 'help':" << std::endl;
            clear();
        }
        else
            return command;
    }
}

void CInterface::clear()
{
    In.clear();
    In.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void CInterface::promptMessage(const char *message)
{
    if (!(Out << message))
        throw std::runtime_error("Error during outputting message");
}

void CInterface::promptMessage(const std::string &message)
{
    if (!(Out << message))
        throw std::runtime_error("Error during outputting message");
}