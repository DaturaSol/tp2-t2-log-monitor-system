// src/core/LogParser.cpp
/**
 * @file LogParser.cpp
 * @brief Implementation of the LogParser utility for log file data extraction.
 */

#include <regex>
#include <string>

#include "monitor/core/LogParser.hpp"
#include "monitor/utils/DateUtils.hpp"
#include "monitor/utils/LogTypes.hpp"

namespace monitor {

/**
 * @details Parses a raw log line based on a strictly defined format:
 * [Date] [Time] [Message].
 *
 * The method employs a regular expression to extract components:
 * - Date: Matches formats such as DD/MM/YYYY or D/M/YYYY.
 * - Time: Matches HH:MM:SS.
 * - Message: Captures the remaining content of the line.
 *
 * Business Rules:
 * - If the message length exceeds 100 characters, it is truncated to 100
 * characters.
 * - The `isValid` flag is set to false if the line format does not match the
 *   expected pattern.
 * - Timestamp generation is delegated to @ref DateUtils.
 *
 * @param line The raw string to parse.
 * @return A populated LogEntry structure.
 */
LogEntry LogParser::parseLogLine(const std::string &line) {
  LogEntry entry;

  // Pattern: [Date] [Time] [Message]
  std::regex pattern(R"(^(\d{1,2}/\d{1,2}/\d{4}) (\d{2}:\d{2}:\d{2}) (.*)$)");
  std::smatch matches;

  // check if the entry matches the pattern
  if (std::regex_match(line, matches, pattern)) {
    entry.date = matches[1].str();
    entry.time = matches[2].str();
    entry.message = matches[3].str();

    // I have decided to truncate the message, if passes 100.
    if (entry.message.length() > 100) {
      entry.message.resize(100);
    }

    entry.timestamp = DateUtils::convertToTimestamp(entry.date, entry.time);
    entry.isValid = true;
  } else {
    entry.isValid = false;
  }
  return entry;
}
} // namespace monitor
