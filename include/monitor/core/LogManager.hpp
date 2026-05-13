// include/monitor/core/LogManager.hpp
/**
 * @file LogManager.hpp
 * @brief Definition of the LogManager class for orchestrating log processing.
 * @author @DaturaSol
 */

#ifndef INCLUDE_MONITOR_CORE_LOGMANAGER_HPP_
#define INCLUDE_MONITOR_CORE_LOGMANAGER_HPP_

#include <string>

namespace monitor {

/**
 * @class LogManager
 * @brief Orchestrates the extraction, sorting, and aggregation of log data.
 *
 * This class acts as the primary interface for managing the log processing
 * workflow, handling both individual log files and master configuration lists.
 */
class LogManager {
public:
  /** @brief Initializes a new instance of the LogManager. */
  LogManager() = default;

  /** @brief Cleans up resources used by the LogManager. */
  ~LogManager() = default;

  /**
   * @brief Reads a single log file, sorts its contents, and writes to a total_
   * file.
   * @param sourceFilePath e.g. "c:\logs\log1.txt"
   * @param outputDirectory Where to save "total_log1.txt"
   * @return true if successful
   */
  bool processSingleLogFile(const std::string &sourceFilePath,
                            const std::string &outputDirectory);

  /**
   * @brief Reads the master file and processes all logs listed inside it.
   * @param masterFilePath e.g. "logs.txt"
   * @param outputDirectory Where to save the merged files
   */
  void processAllLogs(const std::string &masterFilePath,
                      const std::string &outputDirectory);
};
} // namespace monitor

#endif // INCLUDE_MONITOR_CORE_LOGMANAGER_HPP_
