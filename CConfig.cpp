#include "CConfig.h"

CConfig::CConfig()
{
    readConfig("C:\\Users\\Adam\\OneDrive\\PA1\\semestralka\\config.txt");
}

std::map<std::string, std::string> &CConfig::getConfig()
{
    return configMap;
}

std::string CConfig::getWhiteRook()
{
    auto it = configMap.find("White_Rook");
    return it->second;
}
std::string CConfig::getWhiteBishop()
{
    auto it = configMap.find("White_Bishop");
    return it->second;
}
std::string CConfig::getWhiteKing()
{
    auto it = configMap.find("White_King");
    return it->second;
}
std::string CConfig::getWhiteQueen()
{
    auto it = configMap.find("White_Queen");
    return it->second;
}
std::string CConfig::getWhitePawn()
{
    auto it = configMap.find("White_Pawn");
    return it->second;
}
std::string CConfig::getWhiteKnight()
{
    auto it = configMap.find("White_Knight");
    return it->second;
}
std::string CConfig::getBlackRook()
{
    auto it = configMap.find("Black_Rook");
    return it->second;
}
std::string CConfig::getBlackKing()
{
    auto it = configMap.find("Black_King");
    return it->second;
}
std::string CConfig::getBlackKnight()
{
    auto it = configMap.find("Black_Knight");
    return it->second;
}
std::string CConfig::getBlackBishop()
{
    auto it = configMap.find("Black_Bishop");
    return it->second;
}
std::string CConfig::getBlackPawn()
{
    auto it = configMap.find("Black_Pawn");
    return it->second;
}
std::string CConfig::getBlackQueen()
{
    auto it = configMap.find("Black_Queen");
    return it->second;
}
std::string CConfig::getPath()
{
    auto it = configMap.find("Saved_Games_Path");
    return it->second;
}

int CConfig::getOppening()
{
    auto it = configMap.find("AI_Oppening");
    return stoi(it->second);
}

int CConfig::getMMAB()
{
    auto it = configMap.find("MMABDif");
    return stoi(it->second);
}

int CConfig::getMM()
{
    auto it = configMap.find("MMDif");
    return stoi(it->second);
}

CConfig &CConfig::getInstance()
{
    static CConfig instance;
    return instance;
}

bool CConfig::checkPiece(const std::string &piece)
{
    auto it = configMap.find(piece);
    if (it == configMap.end() || it->second.length() != 1 || !std::isalnum(it->second[0]))
        return false;
    return true;
}
bool CConfig::checkText(const std::string &text)
{
    auto it = configMap.find(text);
    if (it == configMap.end() || it->second.length() == 0)
        return false;
    return true;
}

bool CConfig::checkNum(const std::string &num)
{
    auto it = configMap.find(num);
    if (it == configMap.end() || it->second.length() != 1 || !std::isdigit(it->second[0]))
        return false;
    if ((it->first == "MMABDif" || it->first == "MMDif") && (stoi(it->second) > 5 || stoi(it->second) < 1))
        return false;
    return true;
}

bool CConfig::setValues()
{
    if (!checkPiece("White_Rook") || !checkPiece("White_Knight") || !checkPiece("White_Bishop") ||
        !checkPiece("White_King") || !checkPiece("White_Queen") || !checkPiece("White_Pawn") ||
        !checkPiece("Black_Rook") || !checkPiece("Black_Knight") || !checkPiece("Black_Bishop") ||
        !checkPiece("Black_King") || !checkPiece("Black_Queen") || !checkPiece("Black_Pawn"))
        return false;

    std::set<std::string> encounteredValues;
    for (auto it = configMap.lower_bound("Black_Bishop"); it != configMap.upper_bound("Black_Rook"); it++)
    {
        if (encounteredValues.count(it->second) > 0)
        {
            return false;
        }
        encounteredValues.insert(it->second);
    }

    for (auto it = configMap.lower_bound("White_Bishop"); it != configMap.upper_bound("White_Rook"); it++)
    {
        if (encounteredValues.count(it->second) > 0)
        {
            return false;
        }
        encounteredValues.insert(it->second);
    }

    auto it = configMap.find("Saved_Games_Path");
    std::filesystem::directory_entry entry{it->second};
    if (it == configMap.end() || !entry.exists() || it->second.length() == 0)
        return false;

    if (!checkText("Tutorial_Move_King") || !checkText("Tutorial_Move_Queen") || !checkText("Tutorial_Move_Bishop") ||
        !checkText("Tutorial_Move_Knight") || !checkText("Tutorial_Move_Rook") || !checkText("Tutorial_Move_Pawn") ||
        !checkText("Tutorial_Perform_EnPassant") || !checkText("Tutorial_Perform_Castle") || !checkText("Tutorial_Perform_Promotion"))
        return false;

    if (!checkNum("AI_Oppening") || !checkNum("MMABDif") || !checkNum("MMDif"))
        return false;

    return true;
}

void CConfig::readConfig(const std::string &filename)
{
    std::ifstream configFile(filename);
    if (configFile.is_open())
    {
        std::string line;
        while (std::getline(configFile, line))
        {
            if (!line.empty() && line.back() == '\r')
            {

                line.pop_back(); // Remove carriage return character if present
            }
            if (!line.empty() && line.back() == '\n')
            {

                line.pop_back(); // Remove newline character if present
            }
            if (!line.empty() && line[0] != '#')
            { // Ignore empty lines and lines starting with '#'
                size_t equalPos = line.find('=');
                if (equalPos != std::string::npos)
                {
                    bool hasNonWhitespace = false;
                    for (size_t i = equalPos + 1; i < line.length(); i++)
                    {
                        if (!std::isspace(line[i]))
                        {
                            hasNonWhitespace = true;
                            break;
                        }
                    }

                    if (hasNonWhitespace)
                    {
                        std::string key = line.substr(0, equalPos - 1);
                        std::string value = line.substr(equalPos + 2);
                        configMap[key] = value;
                    }
                    else
                    {
                        throw std::runtime_error("Edit configuration file!");
                    }
                }
                else
                    throw std::runtime_error("Edit configuration file!");
            }
        }
        configFile.close();
    }
    else
    {
        throw std::runtime_error("Failed to open configuration file.");
    }
}
