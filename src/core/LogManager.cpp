// src/core/LogManager.cpp
/**
 * @file LogManager.cpp
 * @brief Implementation of the LogManager class for orchestrating log
 * processing workflows.
 */

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "monitor/core/LogListParser.hpp"
#include "monitor/core/LogManager.hpp"
#include "monitor/core/LogParser.hpp"
#include "monitor/utils/LogTypes.hpp"

namespace monitor {

/**
 * @details Performs the following operations:
 * 1. Opens and validates the source log file.
 * 2. Parses individual lines into LogEntry structures.
 * 3. Sorts entries chronologically using the overloaded operator< in LogEntry.
 * 4. Writes the processed entries to a new file prefixed with "total_".
 *
 * @return True if the file was processed and written successfully; false
 * otherwise.
 */
bool LogManager::processSingleLogFile(const std::string &sourceFilePath,
                                      const std::string &outputDirectory) {
  assert(!sourceFilePath.empty() && "WARNING: SourceFilePath cannot be empty!");
  assert(!outputDirectory.empty() &&
         "WARNING: outputDirectory cannot be empty!");

  std::filesystem::path srcPath(sourceFilePath);
  std::string filename = srcPath.filename().string();
  std::filesystem::path outPath =
      std::filesystem::path(outputDirectory) / ("total_" + filename);

  std::vector<LogEntry> logs;
  std::string line;

  // merge with old log file
  if (std::filesystem::exists(outPath)) {
    std::ifstream existingTotal(outPath);
    while (std::getline(existingTotal, line)) {
      LogEntry entry = LogParser::parseLogLine(line);
      if (entry.isValid) {
        logs.push_back(entry);
      }
    }
    existingTotal.close();
  }

  std::ifstream inFile(sourceFilePath);
  if (!inFile.is_open()) {
    return false;
  }
  while (std::getline(inFile, line)) {
    LogEntry entry = LogParser::parseLogLine(line);
    if (entry.isValid) {
      logs.push_back(entry);
    }
  }
  inFile.close();

  std::sort(logs.begin(), logs.end());

  std::vector<LogEntry>::iterator it = std::unique(logs.begin(), logs.end());
  logs.erase(it, logs.end());

  std::ofstream outFile(outPath);
  if (!outFile.is_open()) {
    return false;
  }

  for (const LogEntry &log : logs) {
    outFile << log.date << " " << log.time << " " << log.message << "\n";
  }
  outFile.close();

  assert(std::filesystem::exists(outPath) && "WARNING: No file was generated!");
  return true;
}

/**
 * @details Orchestrates batch processing by retrieving a list of paths from the
 * provided master configuration file and delegating each path to
 * processSingleLogFile.
 */
void LogManager::processAllLogs(const std::string &masterFilePath,
                                const std::string &outputDirectory) {
  assert(!masterFilePath.empty() && "Master file path cannot be empty!");

  std::vector<std::string> targetFiles =
      LogListParser::getLogPaths(masterFilePath);

  for (const std::string &targetFile : targetFiles) {
    processSingleLogFile(targetFile, outputDirectory);
  }
}
} // namespace monitor
