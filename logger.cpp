#include "logger.h"
#include <fstream>
#include <ctime>
#include <iostream>

namespace Logger {

const std::string LOG_FILE = "activity_log.txt";

void log(const std::string& activity) {
    std::ofstream logFile(LOG_FILE, std::ios::app);
    if (logFile.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        logFile << dt << " - " << activity << std::endl;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
}

}  // namespace Logger

