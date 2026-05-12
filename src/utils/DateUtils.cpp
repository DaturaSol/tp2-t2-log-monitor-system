// src/core/utils/DateUtils.cpp

#include <cstdint>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

#include "monitor/utils/DateUtils.hpp"

namespace monitor {
int64_t DateUtils::convertToTimestamp(const std::string &date,
                                      const std::string &time) {
  std::tm tm = {};

  std::string combined = date + " " + time;
  std::istringstream ss(combined);
  ss >> std::get_time(&tm, "%d/%m/%Y %H:%M:%S");

  if (ss.fail()) {
    return 0;
  }

  std::time_t timestamp = std::mktime(&tm);

  return static_cast<int64_t>(timestamp);
}
} // namespace monitor
