#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "ILogger.h"
#include <fstream>

class FileLogger : public ILogger {
public:
    explicit FileLogger(const std::string& filename);
    ~FileLogger();
    void write(const std::string& message) override;

private:
    std::ofstream m_fileStream;
};

#endif // FILELOGGER_H