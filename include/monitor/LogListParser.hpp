// include/monitor/LogListParser.hpp

#pragma once

#include <istream>
#include <string>
#include <vector>

namespace monitor {
class LogListParser {
 public:
  /**
   * @brief Reads an input stream from a master log file and returns a list of
   * target log file paths.
   * @param inStream Input Stream from the logs.txt file
   * @return A vector of strings containing the paths to monitor.
   */
  static std::vector<std::string> getLogPaths(std::istream& inStream);

  /**
   * @brief Reads a master log file and returns a list of target log file paths.
   * @param masterFilePath The path to the logs.txt file.
   * @return A vector of strings containing the paths to monitor.
   */
  static std::vector<std::string> getLogPaths(
      const std::string& masterFilePath);
};
}  // namespace monitor