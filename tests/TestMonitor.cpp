// tests/TestMonitor.cpp

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <monitor/core/LogListParser.hpp>
#include <monitor/core/LogManager.hpp>
#include <monitor/core/LogParser.hpp>
#include <monitor/utils/DateUtils.hpp>
#include <monitor/utils/LogTypes.hpp>
#include <sstream>

/*
 * Test 1:
 * Idea is to check if the parser can validate a correct log
 */
TEST(LogParserTest, ParsesValidLogLine) {
  std::string validLine = "16/1/2026 13:27:46 This is a valid Log format.";

  monitor::LogEntry expected;
  expected.date = "16/1/2026";
  expected.time = "13:27:46";
  expected.message = "This is a valid Log format.";
  expected.isValid = true;

  monitor::LogEntry result = monitor::LogParser::parseLogLine(validLine);

  EXPECT_EQ(result, expected);
}

/*
 * Test 2.
 * Idea is to check if the parsen can notice an invalid log.
 */
TEST(LogParserTest, RejectsInvalidLogFormat) {
  std::string invalidLine = "This is not a valid log format";

  monitor::LogEntry result = monitor::LogParser::parseLogLine(invalidLine);
  EXPECT_FALSE(result.isValid);
  EXPECT_EQ(result.date, "");
}

/*
 * Test 3.
 * Idea is to check if parser can read a valid stream.
 */
TEST(LogListParserTest, ReadsPathsFromStream) {
  // in memory simulated file
  std::stringstream mockMemoryFile(
      "c:\\logs\\log1.txt\n"
      "f:\\logs\\log2.txt\n");

  std::vector<std::string> paths =
      monitor::LogListParser::getLogPaths(mockMemoryFile);

  ASSERT_EQ(paths.size(), 2);
  EXPECT_EQ(paths[0], "c:\\logs\\log1.txt");
  EXPECT_EQ(paths[1], "f:\\logs\\log2.txt");
}

/*
 * Test 4.
 * Idea is to check if the program can read from a mock file.
 */
TEST(LogListParserIntegrationTest, ReadsRealFileFromMocks) {
  std::filesystem::path projectRoot(PROJECT_ROOT);
  std::filesystem::path mockDirPath = projectRoot / "tests" / "mocks";
  std::filesystem::create_directories(mockDirPath);

  std::filesystem::path mockFilePath = mockDirPath / "logs.txt";

  std::ofstream out(mockFilePath);
  out << "c:\\logs\\log1.txt\n";
  out << "f:\\logs\\log2.txt";
  out.close();

  std::vector<std::string> paths =
      monitor::LogListParser::getLogPaths(mockFilePath.string());

  ASSERT_EQ(paths.size(), 2);
  EXPECT_EQ(paths[0], "c:\\logs\\log1.txt");
  EXPECT_EQ(paths[1], "f:\\logs\\log2.txt");

  std::filesystem::remove_all(mockDirPath);
}

/*
 * Test 5
 * Idea is to check if the program returns an empty array of paths if missing
 * file
 */
TEST(LogListParserIntegrationTest, ReturnsEmptyWhenFileMissing) {
  std::filesystem::path projectRoot(PROJECT_ROOT);
  std::filesystem::path mockDirPath = projectRoot / "tests" / "mocks";
  std::filesystem::create_directories(mockDirPath);

  std::filesystem::path missingFilePath = mockDirPath / "master_logs.txt";

  std::vector<std::string> paths =
      monitor::LogListParser::getLogPaths(missingFilePath.string());

  EXPECT_TRUE(paths.empty());
  std::filesystem::remove_all(mockDirPath);
}

/*
 * Test 6
 * Idea is to check if convert is going well
 */
TEST(DateUtilsTest, ConvertsStringsToSortableTimestamps) {
  std::string date1 = "16/1/2026";
  std::string time1 = "13:27:46";

  std::string date2 = "17/1/2026";
  std::string time2 = "14:17:46";

  long timestamp1 = monitor::DateUtils::convertToTimestamp(date1, time1);
  long timestamp2 = monitor::DateUtils::convertToTimestamp(date2, time2);

  EXPECT_GT(timestamp2, timestamp1);

  EXPECT_NE(timestamp1, 0);
}

/*
 * Test 7
 * Idea tests a single master file
 */
TEST(LogManagerTest, ProcessesAndSortsSingleFile) {
  std::filesystem::path projectRoot(PROJECT_ROOT);
  std::filesystem::path outDir = projectRoot / "tests" / "mocks" / "output";
  std::filesystem::create_directories(outDir);

  std::filesystem::path mockLog = outDir / "log1.txt";
  std::ofstream out(mockLog);
  out << "20/1/2026 17:45:38 Log entry B\n";
  out << "16/1/2026 13:27:46 Log entry A\n";
  out.close();

  monitor::LogManager manager;
  bool success =
      manager.processSingleLogFile(mockLog.string(), outDir.string());

  EXPECT_TRUE(success);

  std::filesystem::path totalLogPath = outDir / "total_log1.txt";
  ASSERT_TRUE(std::filesystem::exists(totalLogPath));

  std::ifstream in(totalLogPath);
  std::string line1, line2;
  std::getline(in, line1);
  std::getline(in, line2);

  EXPECT_EQ(line1, "16/1/2026 13:27:46 Log entry A");
  EXPECT_EQ(line2, "20/1/2026 17:45:38 Log entry B");

  std::filesystem::remove_all(outDir);
}

/*
 * Test 8.
 * A complete test from the pipeline
 */
TEST(LogManagerTest, ProcessesAllLogsFromMasterFile) {
  std::filesystem::path projectRoot(PROJECT_ROOT);
  std::filesystem::path testDir =
      projectRoot / "tests" / "mocks" / "integration_test";
  std::filesystem::create_directories(testDir);

  std::filesystem::path log1 = testDir / "log1.txt";
  std::ofstream out1(log1);
  out1 << "20/1/2026 10:00:00 Entry 2\n";
  out1 << "16/1/2026 10:00:00 Entry 1\n";
  out1.close();

  std::filesystem::path masterLog = testDir / "logs.txt";
  std::ofstream masterOut(masterLog);
  masterOut << log1.string() << "\n";
  masterOut.close();

  monitor::LogManager manager;
  manager.processAllLogs(masterLog.string(), testDir.string());

  std::filesystem::path totalLog1 = testDir / "total_log1.txt";
  EXPECT_TRUE(std::filesystem::exists(totalLog1));

  std::filesystem::remove_all(testDir);
}