// include/monitor/utils/DateUtils.hpp
/**
 * @file DateUtils.hpp
 * @brief Utility functions for temporal data manipulation and conversion.
 * @author @DaturaSol
 */

#ifndef INCLUDE_MONITOR_UTILS_DATEUTILS_HPP_
#define INCLUDE_MONITOR_UTILS_DATEUTILS_HPP_

#include <cstdint>
#include <string>

namespace monitor {

/**
 * @class DateUtils
 * @brief Stateless utility class for time and date processing.
 */
class DateUtils {
public:
  /**
   * @brief Converts a Date/Time string into a numeric UNIX timestamp.
   * @param date e.g., "16/1/2026"
   * @param time e.g., "13:27:46"
   * @return int64_t The total number of seconds elapsed since the UNIX Epoch
   * (1970-01-01).
   */
  static int64_t convertToTimestamp(const std::string &date,
                                    const std::string &time);
};
} // namespace monitor

#endif // INCLUDE_MONITOR_UTILS_DATEUTILS_HPP_
