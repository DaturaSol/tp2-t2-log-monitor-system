// include/monitor/core/LogManager.hpp

#include <string>

namespace monitor {
class LogManager {
 public:
  LogManager() = default;
  ~LogManager() = default;

  std::string getStatus() const;
  /**
   * @brief Reads a single log file, sorts its contents, and writes to a total_
   * file.
   * @param sourceFilePath e.g. "c:\logs\log1.txt"
   * @param outputDirectory Where to save "total_log1.txt"
   * @return true if successful
   */
  bool processSingleLogFile(const std::string& sourceFilePath,
                            const std::string& outputDirectory);

  /**
   * @brief Reads the master file and processes all logs listed inside it.
   * @param masterFilePath e.g. "logs.txt"
   * @param outputDirectory Where to save the merged files
   */
  void processAllLogs(const std::string& masterFilePath,
                      const std::string& outputDirectory);
};
}  // namespace monitor