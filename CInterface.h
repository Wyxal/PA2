#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include <functional>

#include "CMove.h"

/**
 * Class CInterface for CApplication to interact with the user
 */
class CInterface
{
private:
    // The output stream to be used
    std::ostream &Out;

    // The input stream to be used
    std::istream &In;

public:
    explicit CInterface(std::ostream &out, std::istream &in);

    /**
     * Prompts the user with a message to be displayed on the output stream.
     * @param message The message to be displayed.
     * @throws std::runtime_error if there is an error during outputting the message.
     */
    void promptMessage(const char *message);

    /**
     * Prompts the user with a message to be displayed on the output stream.
     * @param message The message to be displayed.
     * @throws std::runtime_error if there is an error during outputting the message.
     */
    void promptMessage(const std::string &message);

    /**
     *  Returns the output stream associated with the interface.
     *  @return The output stream.
     */
    std::ostream &getOstream() const;

    /**
     *  Returns the input stream associated with the interface.
     *  @return The input stream.
     */
    std::istream &getIstream() const;

    /**
     * Prompts the user for a command and returns it after validating with the provided function.
     * @param valid A function that validates the command.
     * @return The validated command entered by the user.
     * @throws std::runtime_error if there is an error during inputting the command.
     */
    std::string promptCommand(const std::function<bool(const std::string &)> &valid);

    /**
     * Clears the input stream.
     */
    void clear();
};