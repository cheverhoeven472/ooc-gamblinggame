#include <fstream>
#include <iostream>

int Main() {
    std::ofstream logFile("game_log.txt", std::ios::trunc);

    if (logFile.is_open()) {
        logFile.close();
        std::cout << "Log file cleared!" << std::endl;
    }
    else {
        std::cout << "Could not open log file." << std::endl;
    }

    return 0;
}