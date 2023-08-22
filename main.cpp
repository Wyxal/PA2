#include <iostream>
#include "CApplication.h"
#include "CInterface.h"
#include "CConfig.h"

void handler (int param)
{
  exit(param);
}

int main()
{
    std::signal(SIGABRT, handler);
    std::signal(SIGINT, handler);

    CConfig &config = CConfig::getInstance();
    if (!config.setValues())
    {
        std::cout << "Please change configuration file!\n";
        return 0;
    }
    return CApplication(CInterface(std::cout, std::cin)).run();
}