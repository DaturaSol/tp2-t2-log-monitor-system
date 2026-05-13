// include/monitor/core/LogParser.hpp
/**
 * @file LogParser.hpp
 * @brief Definition of the LogParser utility class.
 * @author @DaturaSol
 */

#ifndef INCLUDE_MONITOR_CORE_LOGPARSER_HPP_
#define INCLUDE_MONITOR_CORE_LOGPARSER_HPP_

#include <string>

#include "monitor/utils/LogTypes.hpp"

namespace monitor {

/**
 * @class LogParser
 * @brief Provides functionality to parse and transform raw log data.
 *
 * This class acts as a stateless parser responsible for converting raw string
 * input into structured LogEntry objects.
 */
class LogParser {
public:
  /**
   * @brief Parses a single line from a log file.
   * @param line A string containing date, time, and message.
   * @return LogEntry struct containing the parsed data.
   * @note If line is over 100 chars long it will be truncated.
   */
  static LogEntry parseLogLine(const std::string &line);
};
} // namespace monitor

#endif // INCLUDE_MONITOR_CORE_LOGPARSER_HPP_
