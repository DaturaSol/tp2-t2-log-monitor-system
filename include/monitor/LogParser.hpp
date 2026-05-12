// include/monitor/LogParser.hpp

#pragma once

#include <monitor/LogTypes.hpp>
#include <string>

namespace monitor {
class LogParser {
 public:
  /**
   * @brief Parses a single line from a log file.
   * @param line A string containing date, time, and message.
   * @return LogEntry struct containing the parsed data.
   */
  static LogEntry parseLogLine(const std::string& line);
};
}  // namespace monitor