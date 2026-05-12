// tests/TestMonitor.cpp

#include <gtest/gtest.h>

#include <monitor/core/LogListParser.hpp>
#include <monitor/core/LogParser.hpp>
#include <monitor/utils/DateUtils.hpp>
#include <monitor/utils/LogTypes.hpp>
#include <sstream>

/*
 * Test 1:
 * Idea is to check if the parser can validate a correct log
 */
TEST(LogParserTest, ParsesValidLogLine) {
  std::string validLine = "16/1/2026 13:27:46 Este é um exemplo de log";

  monitor::LogEntry expected;
  expected.date = "16/1/2026";
  expected.time = "13:27:46";
  expected.message = "Este é um exemplo de log";
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
  std::string mockFilePath = "mocks/master_logs.txt";

  std::vector<std::string> paths =
      monitor::LogListParser::getLogPaths(mockFilePath);

  ASSERT_EQ(paths.size(), 2);
  EXPECT_EQ(paths[0], "c:\\logs\\log1.txt");
  EXPECT_EQ(paths[1], "f:\\logs\\log2.txt");
}

/*
 * Test 5
 * Idea is to check if the program returns an empty array of paths if missing
 * file
 */
TEST(LogListParserIntegrationTest, ReturnsEmptyWhenFileMissing) {
  std::string missingFilePath = "mocks/does_not_exist.txt";

  std::vector<std::string> paths =
      monitor::LogListParser::getLogPaths(missingFilePath);

  EXPECT_TRUE(paths.empty());
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