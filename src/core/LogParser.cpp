// src/core/LogParser.cpp

#include <monitor/LogParser.hpp>
#include <monitor/LogTypes.hpp>
#include <regex>

namespace monitor {
LogEntry LogParser::parseLogLine(const std::string &line) {
  LogEntry entry;
  /** R for raw string;
   * Date:
   *  - type: 01/01/2004 or 1/1/2004
   *  - expr: (\d{1,2}/\d{1,2}/\d{4})
   *
   * Time:
   *  - type: 01:01:46
   *  - expr: (\d{2}:\d{2}:\d{2})
   *
   * Message:
   *  - type: anything
   *  - expr: (.*)
   *
   * Final pattern: 01/01/2004 01:01:46 anything
   */
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
    entry.isValid = true;
  } else {
    entry.isValid = false;
  }
  return entry;
}
}  // namespace monitor