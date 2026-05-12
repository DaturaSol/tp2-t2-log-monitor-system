// tests/TestMonitor.cpp

#include <gtest/gtest.h>

#include <monitor/LogListParser.hpp>
#include <monitor/LogParser.hpp>
#include <monitor/LogTypes.hpp>
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