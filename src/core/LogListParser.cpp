// src/core/LogListParser.cpp

#include <fstream>
#include <istream>
#include <monitor/core/LogListParser.hpp>
#include <string>

namespace monitor {
std::vector<std::string> LogListParser::getLogPaths(std::istream& inStream) {
  std::vector<std::string> paths;
  std::string line;

  // This will quit once finds the end of the file.
  while (std::getline(inStream, line)) {
    // skip empty lines
    if (line.empty()) {
      continue;
    }
    paths.push_back(line);
  }

  return paths;
}

std::vector<std::string> LogListParser::getLogPaths(
    const std::string& masterFilePath) {
  std::ifstream file(masterFilePath);

  // empty vector if no file
  if (!file.is_open()) {
    return {};
  }

  return getLogPaths(file);
}

}  // namespace monitor