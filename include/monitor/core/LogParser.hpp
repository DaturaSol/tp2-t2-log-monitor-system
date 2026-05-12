// include/monitor/core/LogParser.hpp

#ifndef INCLUDE_MONITOR_CORE_LOGPARSER_HPP_
#define INCLUDE_MONITOR_CORE_LOGPARSER_HPP_

#include <string>

#include "monitor/utils/LogTypes.hpp"

namespace monitor {
class LogParser {
public:
  /**
   * @brief Parses a single line from a log file.
   * @param line A string containing date, time, and message.
   * @return LogEntry struct containing the parsed data.
   */
  static LogEntry parseLogLine(const std::string &line);
};
} // namespace monitor

#endif // INCLUDE_MONITOR_CORE_LOGPARSER_HPP_
