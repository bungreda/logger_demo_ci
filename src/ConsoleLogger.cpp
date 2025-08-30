#include "ConsoleLogger.h"

void ConsoleLogger::write(const std::string& message) {
    std::cout << message << std::endl;
}