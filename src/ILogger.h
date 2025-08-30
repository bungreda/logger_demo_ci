#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>
#include "LoggerLevels.h"

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void write(const std::string& message) = 0;
};

#endif // ILOGGER_H