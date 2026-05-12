// include/monitor/utils/DateUtils.hpp

#ifndef INCLUDE_MONITOR_UTILS_DATEUTILS_HPP_
#define INCLUDE_MONITOR_UTILS_DATEUTILS_HPP_

#include <cstdint>
#include <string>

namespace monitor {
class DateUtils {
public:
  /**
   * @brief Converts a Date/Time string into a numeric UNIX timestamp.
   * @param date e.g., "16/1/2026"
   * @param time e.g., "13:27:46"
   * @return long integer representing seconds since Epoch (easy to sort)
   */
  static int64_t convertToTimestamp(const std::string &date,
                                    const std::string &time);
};
} // namespace monitor

#endif // INCLUDE_MONITOR_UTILS_DATEUTILS_HPP_
