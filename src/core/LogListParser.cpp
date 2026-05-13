// src/core/LogListParser.cpp
/**
 * @file LogListParser.cpp
 * @brief Implementation of LogListParser utility methods for master log file
 * ingestion.
 */

#include <fstream>
#include <istream>
#include <string>
#include <vector>

#include "monitor/core/LogListParser.hpp"

namespace monitor {

/**
 * @details Iterates through the provided input stream, extracting non-empty
 * lines as valid file paths. This implementation acts as a filter for malformed
 * lines or excess whitespace commonly found in master log configuration files.
 */
std::vector<std::string> LogListParser::getLogPaths(std::istream &inStream) {
  std::vector<std::string> paths;
  std::string line;

  // Extract lines sequentially; skip empty lines to handle trailing newlines
  // or inconsistent formatting in the master file.
  while (std::getline(inStream, line)) {
    // skip empty lines
    if (line.empty()) {
      continue;
    }
    paths.push_back(line);
  }

  return paths;
}

/**
 * @details Opens a file handle to the specified system path and delegates the
 * stream parsing to getLogPaths(std::istream&).
 *
 * If the file is inaccessible or does not exist, the method returns an empty
 * vector rather than throwing an exception. This design assumes that an empty
 * list is a valid, manageable state for the caller.
 */
std::vector<std::string>
LogListParser::getLogPaths(const std::string &masterFilePath) {
  std::ifstream file(masterFilePath);

  // If the file fails to open, return an empty set rather than throwing an
  // exception, allowing the caller to decide how to handle missing
  // configuration files.
  if (!file.is_open()) {
    return {};
  }

  return getLogPaths(file);
}

} // namespace monitor
