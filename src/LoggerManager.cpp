#include "LoggerManager.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include <sstream>
#include <chrono>
#include <iomanip>

LoggerManager& LoggerManager::getInstance() {
    static LoggerManager instance;
    return instance;
}

LoggerManager::LoggerManager() : m_minLevel(LogLevel::INFO), m_stopThread(false) {
    m_workerThread = std::thread(&LoggerManager::workerThreadFunc, this);
}

LoggerManager::~LoggerManager() {
    m_stopThread = true;
    m_queueCondVar.notify_one();
    if (m_workerThread.joinable()) {
        m_workerThread.join();
    }
}

void LoggerManager::addOutput(std::unique_ptr<ILogger> logger) {
    m_outputs.push_back(std::move(logger));
}

void LoggerManager::setMinimumLevel(LogLevel level) {
    m_minLevel = level;
}

void LoggerManager::log(LogLevel level, const std::string& message) {
    if (level < m_minLevel) {
        return;
    }

    // Prepare log message with timestamp
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << "[" << std::put_time(std::localtime(&time_t_now), "%Y-%m-%d %X") << "] ";
    ss << "[" << LogLevelToString(level) << "] " << message;

    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_messageQueue.push({level, ss.str()});
    } // Mutex is released here
    m_queueCondVar.notify_one();
}

void LoggerManager::workerThreadFunc() {
    while (true) {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_queueCondVar.wait(lock, [this] {
            return !m_messageQueue.empty() || m_stopThread;
        });

        // Loop to process all pending messages before potentially exiting
        while (!m_messageQueue.empty()) {
            LogMessage msg = m_messageQueue.front();
            m_messageQueue.pop();

            // Unlock while processing to allow other threads to add messages
            lock.unlock();

            // Write the message to all configured outputs
            for (const auto& output : m_outputs) {
                output->write(msg.message);
            }

            // Re-acquire lock to check queue for more messages and to wait again
            lock.lock();
        }
        
        if (m_stopThread) {
            break;
        }
    }
}