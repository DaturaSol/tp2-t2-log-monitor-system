// src/core/utils/DateUtils.cpp
/**
 * @file DateUtils.cpp
 * @brief Implementation of utility functions for temporal conversion.
 */

#include <cstdint>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

#include "monitor/utils/DateUtils.hpp"

namespace monitor {

/**
 * @details Concatenates date and time strings and transforms them into a
 * standard UNIX timestamp.
 *
 * Parsing is performed using the format mask "%d/%m/%Y %H:%M:%S".
 *
 * @note This method utilizes `std::mktime`, which interprets the input
 * based on the system's local timezone settings.
 *
 * @param date The date string in DD/MM/YYYY format.
 * @param time The time string in HH:MM:SS format.
 * @return The calculated UNIX timestamp, or 0 if parsing fails.
 */
int64_t DateUtils::convertToTimestamp(const std::string &date,
                                      const std::string &time) {
  std::tm tm = {};

  std::string combined = date + " " + time;
  std::istringstream ss(combined);
  ss >> std::get_time(&tm, "%d/%m/%Y %H:%M:%S");

  if (ss.fail()) {
    return 0;
  }

  // Convert broken-down time to a time_t (seconds since Epoch)
  std::time_t timestamp = std::mktime(&tm);

  return static_cast<int64_t>(timestamp);
}
} // namespace monitor
