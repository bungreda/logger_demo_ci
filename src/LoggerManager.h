#ifndef LOGGER_MANAGER_H
#define LOGGER_MANAGER_H

#include "ILogger.h"
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

struct LogMessage {
    LogLevel level;
    std::string message;
};

class LoggerManager {
public:
    static LoggerManager& getInstance();

    // Delete copy and move constructors/assignments
    LoggerManager(const LoggerManager&) = delete;
    LoggerManager& operator=(const LoggerManager&) = delete;

    void addOutput(std::unique_ptr<ILogger> logger);
    void setMinimumLevel(LogLevel level);
    void log(LogLevel level, const std::string& message);

private:
    LoggerManager();
    ~LoggerManager();

    void workerThreadFunc();

    std::vector<std::unique_ptr<ILogger>> m_outputs;
    LogLevel m_minLevel;

    std::queue<LogMessage> m_messageQueue;
    std::mutex m_queueMutex;
    std::condition_variable m_queueCondVar;
    
    std::thread m_workerThread;
    bool m_stopThread;
};

#endif // LOGGER_MANAGER_H