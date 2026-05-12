// include/monitor/LogTypes.hpp

#pragma once

#include <string>

namespace monitor {
/**
 *
 */
struct LogEntry {
  std::string date;
  std::string time;
  std::string message;
  bool isValid = false;

  // Overloads comparisson.
  bool operator==(const LogEntry& other) const {
    return date == other.date && time == other.time &&
           message == other.message && isValid == other.isValid;
  }
};
}  // namespace monitor