// src/core/LogManager.cpp

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "monitor/core/LogListParser.hpp"
#include "monitor/core/LogManager.hpp"
#include "monitor/core/LogParser.hpp"
#include "monitor/utils/LogTypes.hpp"

namespace monitor {
std::string LogManager::getStatus() const {
  return "LogManager is initializing and ready to process.";
}

bool LogManager::processSingleLogFile(const std::string &sourceFilePath,
                                      const std::string &outputDirectory) {
  std::ifstream inFile(sourceFilePath);
  if (!inFile.is_open()) {
    return false;
  }
  std::vector<LogEntry> logs;
  std::string line;

  while (std::getline(inFile, line)) {
    LogEntry entry = LogParser::parseLogLine(line);
    if (!entry.isValid) {
      continue;
    }
    logs.push_back(entry);
  }
  inFile.close();

  std::sort(logs.begin(), logs.end());

  std::filesystem::path srcPath(sourceFilePath);
  std::string filename = srcPath.filename().string();

  std::filesystem::path outPath =
      std::filesystem::path(outputDirectory) / ("total_" + filename);

  std::ofstream outFile(outPath);
  if (!outFile.is_open()) {
    return false;
  }

  for (const LogEntry &log : logs) {
    outFile << log.date << " " << log.time << " " << log.message << "\n";
  }
  outFile.close();

  return true;
}

void LogManager::processAllLogs(const std::string &masterFilePath,
                                const std::string &outputDirectory) {
  std::vector<std::string> targetFiles =
      LogListParser::getLogPaths(masterFilePath);

  for (const std::string &targetFile : targetFiles) {
    processSingleLogFile(targetFile, outputDirectory);
  }
}
} // namespace monitor
