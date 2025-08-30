#include "LoggerManager.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include <iostream>
#include <vector>
#include <thread>

void worker(int id) {
    LoggerManager::getInstance().log(LogLevel::INFO, "Thread " + std::to_string(id) + " starting work.");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    LoggerManager::getInstance().log(LogLevel::DEBUG, "Thread " + std::to_string(id) + " processing data.");
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    LoggerManager::getInstance().log(LogLevel::WARN, "Thread " + std::to_string(id) + " finished.");
}

int main() {
    // Configure logger outputs and level
    LoggerManager::getInstance().addOutput(std::make_unique<ConsoleLogger>());
    LoggerManager::getInstance().addOutput(std::make_unique<FileLogger>("app.log"));
    LoggerManager::getInstance().setMinimumLevel(LogLevel::INFO); // Only INFO, WARN, ERROR, FATAL logs will be processed

    LoggerManager::getInstance().log(LogLevel::INFO, "Application started.");
    
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    LoggerManager::getInstance().log(LogLevel::INFO, "Application finished.");

    return 0;
}