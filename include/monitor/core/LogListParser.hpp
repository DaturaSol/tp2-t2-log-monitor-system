// include/monitor/core/LogListParser.hpp
/**
 * @file LogListParser.hpp
 * @brief Definition of the LogListParser utility class.
 *
 * Provides functionality to parse a master log configuration file and extract
 * a collection of individual log file paths.
 *
 * @author @DaturaSol
 */

#ifndef INCLUDE_MONITOR_CORE_LOGLISTPARSER_HPP_
#define INCLUDE_MONITOR_CORE_LOGLISTPARSER_HPP_

#include <istream>
#include <string>
#include <vector>

namespace monitor {

/**
 * @class LogListParser
 * @brief Utility class for parsing master log configuration files.
 *
 * This class provides static methods to extract paths from master log files
 * represented as either an input stream or a file path string.
 */
class LogListParser {
public:
  /**
   * @brief Reads an input stream from a master log file and returns a list of
   * target log file paths.
   * @param inStream Input Stream from the logs.txt file
   * @return A vector of strings containing the paths to monitor.
   */
  static std::vector<std::string> getLogPaths(std::istream &inStream);

  /**
   * @brief Reads a master log file and returns a list of target log file paths.
   * @param masterFilePath The path to the logs.txt file.
   * @return A vector of strings containing the paths to monitor.
   */
  static std::vector<std::string>
  getLogPaths(const std::string &masterFilePath);
};
} // namespace monitor

#endif // INCLUDE_MONITOR_CORE_LOGLISTPARSER_HPP_
