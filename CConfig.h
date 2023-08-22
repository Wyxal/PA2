#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <filesystem>

/**
 * Represents a configuration file reader.
 */
class CConfig
{
public:
    /**
     * @return the singleton instance of CConfig
     */
    static CConfig &getInstance();

    /**
     * Sets the values in the configuration map and validates them.
     * @return true if all values are set and valid, false otherwise
     */
    bool setValues();

    /**
     * @return the value for "White_Rook"
     */
    std::string getWhiteRook();

    /**
     * @return the value for "White_Bishop"
     */
    std::string getWhiteBishop();

    /**
     * @return the value for "White_King"
     */
    std::string getWhiteKing();

    /**
     * @return the value for "White_Queen"
     */
    std::string getWhiteQueen();

    /**
     * @return the value for "White_Pawn"
     */
    std::string getWhitePawn();

    /**
     * @return the value for "White_Knight"
     */
    std::string getWhiteKnight();

    /**
     * @return the value for "Black_Rook"
     */
    std::string getBlackRook();

    /**
     * @return the value for "Black_King"
     */
    std::string getBlackKing();

    /**
     * @return the value for "Black_Knight"
     */
    std::string getBlackKnight();

    /**
     * @return the value for "Black_Bishop"
     */
    std::string getBlackBishop();

    /**
     * @return the value for "Black_Pawn"
     */
    std::string getBlackPawn();

    /**
     * @return the value for "Black_Queen"
     */
    std::string getBlackQueen();

    /**
     * @return the value for "Saved_Games_Path"
     */
    std::string getPath();

    /**
     * @return the value for "AI_Oppening" as an integer
     */
    int getOppening();

    /**
     * @return the value for "MMABDif" as an integer
     */
    int getMMAB();

    /**
     * @return the value for "MMDif" as an integer
     */
    int getMM();

    /**
     * @return the configuration map
     */
    std::map<std::string, std::string> &getConfig();

private:
    std::map<std::string, std::string> configMap;

    CConfig();

    /**
     * Reads the configuration file and populates the configuration map.
     * @param filename the path of the configuration file
     * @throws IOException if there is an error reading the file
     */
    void readConfig(const std::string &filename);

    /**
     * Checks if the specified piece key exists in the configuration map and its value is valid.
     * @param piece the piece key to check
     * @return true if the piece key exists and its value is valid, false otherwise
     */
    bool checkPiece(const std::string &piece);

    /**
     * Checks if the specified text key exists in the configuration map and its value is valid.
     * @param text the text key to check
     * @return true if the text key exists and its value is valid, false otherwise
     */
    bool checkText(const std::string &text);

    /**
     * Checks if the specified numeric key exists in the configuration map and its value is valid.
     * @param num the numeric key to check
     * @return true if the numeric key exists and its value is valid, false otherwise
     */
    bool checkNum(const std::string &num);
};