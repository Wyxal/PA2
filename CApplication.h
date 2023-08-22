#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <csignal>

#include "CInterface.h"
#include "CGame.h"
#include "Commands/CCommand.h"
#include "Commands/CHelp.h"
#include "Commands/CQuit.h"
#include "Commands/CMoves.h"
#include "Commands/CPlay.h"
#include "Commands/CSave.h"
#include "Commands/CLoad.h"
#include "Commands/CRestart.h"
#include "Commands/CBoards.h"
#include "Commands/CTutorial.h"

/**
 * Represents the main application for the chess game.
 */
class CApplication
{
private:
    std::map<std::string, std::unique_ptr<CCommand>> Commands;

    CInterface Interface;

    CGame Game;

public:
    /**
     * Constructs a new CApplication with the given interface.
     * @param interface the interface for the application
     */
    explicit CApplication(const CInterface &interface);

    ~CApplication() = default;

    CApplication(const CApplication &) = delete;

    CApplication &operator=(const CApplication &) = delete;

    /**
     * Runs the chess game application.
     * @return the exit code of the application
     */
    int run();
};