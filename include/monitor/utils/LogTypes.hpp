// include/monitor/utils/LogTypes.hpp
/**
 * @file LogTypes.hpp
 * @brief Defines shared data structures for the log monitoring system.
 * @author @DaturaSol
 */

#ifndef INCLUDE_MONITOR_UTILS_LOGTYPES_HPP_
#define INCLUDE_MONITOR_UTILS_LOGTYPES_HPP_

#include <cstdint>
#include <string>

namespace monitor {

/**
 * @struct LogEntry
 * @brief Represents a single parsed log record.
 */
struct LogEntry {
  std::string date;      ///< Date string (e.g., DD/MM/YYYY)
  std::string time;      ///< Time string (e.g., HH:MM:SS)
  std::string message;   ///< The log content or message body
  int64_t timestamp = 0; ///< UNIX epoch timestamp for chronological sorting
  bool isValid = false;  ///< Indicates if the entry was parsed successfully

  /**
   * @brief Equality comparison operator.
   * @return True if all primary fields match.
   */
  bool operator==(const LogEntry &other) const {
    return timestamp == other.timestamp && message == other.message;
  }

  /**
   * @brief Less-than operator for sorting based on timestamp.
   * @return True if this entry precedes the other chronologically.
   */
  bool operator<(const LogEntry &other) const {
    if (timestamp != other.timestamp)
      return timestamp < other.timestamp;
    return message < other.message;
  }
};
} // namespace monitor

#endif // INCLUDE_MONITOR_UTILS_LOGTYPES_HPP_
