#include "FileLogger.h"
#include <iostream>

FileLogger::FileLogger(const std::string& filename) {
    m_fileStream.open(filename, std::ios_base::app);
    if (!m_fileStream.is_open()) {
        std::cerr << "Error: Could not open log file " << filename << std::endl;
    }
}

FileLogger::~FileLogger() {
    if (m_fileStream.is_open()) {
        m_fileStream.close();
    }
}

void FileLogger::write(const std::string& message) {
    if (m_fileStream.is_open()) {
        m_fileStream << message << std::endl;
    }
}