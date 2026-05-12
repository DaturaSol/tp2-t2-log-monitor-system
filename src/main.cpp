// src/main.cpp

#include <filesystem>
#include <iostream>
#include <monitor/core/LogManager.hpp>
#include <unordered_map>
#include <vector>

void printUsage(const char* programName) {
  std::cout << "Usage: " << programName << " [options]\n\n"
            << "Options:\n"
            << "  --masterFile <path>   Path to the master log file (default: "
               "logs.txt)\n"
            << "  --outdir <path>       Directory to save the merged output "
               "(default: current dir)\n"
            << "  --help                Show this help message\n";
}

enum class CommandOption { Help, MasterFile, OutDir, Unknown };

std::unordered_map<std::string, CommandOption> optionMap = {
    {"--help", CommandOption::Help},
    {"-h", CommandOption::Help},
    {"--masterFile", CommandOption::MasterFile},
    {"--outdir", CommandOption::OutDir}};

int main(int argc, char* argv[]) {
  std::cout << "Log Monitor starting...\n"
            << "For help pass the flag --help or --h. \n";

  std::string masterFilePath = "logs.txt";
  std::string outputDir = std::filesystem::current_path().string();

  bool masterFileProvided = false;
  bool outputDirProvided = false;

  std::vector<std::string> args(argv + 1, argv + argc);

  for (size_t i = 0; i < args.size(); ++i) {
    CommandOption opt =
        optionMap.count(args[i]) ? optionMap[args[i]] : CommandOption::Unknown;

    switch (opt) {
      case CommandOption::Help:
        printUsage(argv[0]);
        return 0;

      case CommandOption::MasterFile:
        if (i + 1 < args.size()) {
          masterFilePath = args[++i];
          masterFileProvided = true;
        } else {
          std::cerr << "ERROR: --masterFile requires a file path argument.\n";
          return 1;
        }
        break;

      case CommandOption::OutDir:
        if (i + 1 < args.size()) {
          outputDir = args[++i];
          outputDirProvided = true;
        } else {
          std::cerr << "ERROR: --outdir requires a directory path argument.\n";
          return 1;
        }
        break;

      case CommandOption::Unknown:
      default:
        std::cerr << "WARNING: Unknown argument ignored: " << args[i] << "\n";
        break;
    }
  }

  if (!masterFileProvided) {
    std::cout << "No --masterFile was passed. Using default: " << masterFilePath
              << "\n";
  }
  if (!outputDirProvided) {
    std::cout << "No --outdir specified. Using default: " << outputDir << "\n";
  }

  if (!std::filesystem::exists(masterFilePath)) {
    std::cerr << "ERROR: FilePath " << masterFilePath << " was not found!\n";
    return 1;
  }

  if (!std::filesystem::exists(outputDir)) {
    std::cout << "Output directory does not exist. Creating: " << outputDir
              << "\n";
    std::filesystem::create_directories(outputDir);
  }

  std::cout << "Reading files in: " << masterFilePath << "\n";
  std::cout << "Saving merges in: " << outputDir << "\n";

  monitor::LogManager manager;
  manager.processAllLogs(masterFilePath, outputDir);

  std::cout << "Processing finished with status code 0\n";

  return 0;
}