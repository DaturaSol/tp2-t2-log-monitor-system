// src/main.cpp
/**
 * @file main.cpp
 * @brief Entry point for the Log Monitor CLI application.
 */

#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "monitor/core/LogManager.hpp"

/**
 * @brief Displays the application usage instructions to standard output.
 * @param programName The name of the executable (argv[0]).
 */
void printUsage(const char *programName) {
  std::cout << "Usage: " << programName << " [options]\n\n"
            << "Options:\n"
            << "  --masterFile <path>   Path to the master log file (default: "
               "logs.txt)\n"
            << "  --outdir <path>       Directory to save the merged output "
               "(default: current dir)\n"
            << "  --help                Show this help message\n";
}

/**
 * @enum CommandOption
 * @brief Maps command-line flags to internal identifiers.
 */
enum class CommandOption { Help, MasterFile, OutDir, Unknown };

/**
 * @brief Registry of supported command-line arguments.
 */
const std::unordered_map<std::string, CommandOption> optionMap = {
    {"--help", CommandOption::Help},
    {"-h", CommandOption::Help},
    {"--masterFile", CommandOption::MasterFile},
    {"--outdir", CommandOption::OutDir}};

int main(int argc, char *argv[]) {
  std::string masterFilePath = "logs.txt";
  std::string outputDir = std::filesystem::current_path().string();

  const std::vector<std::string> args(argv + 1, argv + argc);

  // Argument Parsing
  for (size_t i = 0; i < args.size(); ++i) {
    auto it = optionMap.find(args[i]);
    CommandOption opt =
        (it != optionMap.end()) ? it->second : CommandOption::Unknown;

    switch (opt) {
    case CommandOption::Help:
      printUsage(argv[0]);
      return 0;

    case CommandOption::MasterFile:
      if (i + 1 < args.size()) {
        masterFilePath = args[++i];
      } else {
        std::cerr << "Error: --masterFile requires a file path argument.\n";
        return 1;
      }
      break;

    case CommandOption::OutDir:
      if (i + 1 < args.size()) {
        outputDir = args[++i];
      } else {
        std::cerr << "Error: --outdir requires a directory path argument.\n";
        return 1;
      }
      break;

    default:
      std::cerr << "Warning: Unknown argument ignored: " << args[i] << "\n";
      break;
    }
  }

  // Validation
  if (!std::filesystem::exists(masterFilePath)) {
    std::cerr << "Error: Master log file not found at: " << masterFilePath
              << "\n";
    return 1;
  }

  try {
    if (!std::filesystem::exists(outputDir)) {
      std::filesystem::create_directories(outputDir);
    }
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error: Failed to create output directory: " << e.what()
              << "\n";
    return 1;
  }

  // Execution
  std::cout << "Starting Log Monitor...\n";
  monitor::LogManager manager;
  manager.processAllLogs(masterFilePath, outputDir);

  std::cout << "Processing completed successfully.\n";
  return 0;
}
