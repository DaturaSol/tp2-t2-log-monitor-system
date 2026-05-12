// tests/TestMonitor.cpp

#include <gtest/gtest.h>

#include <monitor/LogParser.hpp>
#include <monitor/LogTypes.hpp>

/**
 * The idea of this test is just to check if the parser is working properly
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