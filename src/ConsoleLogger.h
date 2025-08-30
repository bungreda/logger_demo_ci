#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "ILogger.h"
#include <iostream>

class ConsoleLogger : public ILogger {
public:
    void write(const std::string& message) override;
};

#endif // CONSOLELOGGER_H