// include/monitor/utils/LogTypes.hpp

#ifndef INCLUDE_MONITOR_UTILS_LOGTYPES_HPP_
#define INCLUDE_MONITOR_UTILS_LOGTYPES_HPP_

#include <cstdint>
#include <string>

namespace monitor {
/**
 *
 */
struct LogEntry {
  std::string date;
  std::string time;
  std::string message;
  int64_t timestamp = 0;
  bool isValid = false;

  // Overloads comparisson.
  bool operator==(const LogEntry &other) const {
    return date == other.date && time == other.time &&
           message == other.message && isValid == other.isValid;
  }

  // overloads for sorting
  bool operator<(const LogEntry &other) const {
    return timestamp < other.timestamp;
  }
};
} // namespace monitor

#endif // INCLUDE_MONITOR_UTILS_LOGTYPES_HPP_
