# Log Monitoring System (TP2)

> **Author:** Gabriel M.S.O.
> **Registration:** 190042656

> [!NOTE]
> This documentation is provided in English to ensure consistency throughout the project.

## Overview
This project provides a robust and scalable log monitoring system. The architecture is designed to handle growing project requirements efficiently while adhering to modern C++ development standards.

## Prerequisites
To set up the development environment, ensure you have the following installed:
* [Docker Desktop](https://docs.docker.com/desktop/setup/install/windows-install/)
* [VS Code](https://code.visualstudio.com/download)
* **VS Code Extension:** `ms-vscode-remote.remote-containers` (Remote - Containers)

## Environment Setup
You can work within a containerized environment using one of the following methods:

### Method 1: VS Code Remote Containers
1. Install the `Remote - Containers` extension.
2. Reopen the project folder inside the container when prompted by VS Code.

### Method 2: Manual Container Launch
If you prefer the command line, run the following from the root directory:
```bash
docker-compose -f .devcontainer/docker-compose.yml up -d dev
docker-compose -f .devcontainer/docker-compose.yml exec dev /bin/bash
```

## Build Instructions
This project utilizes **CMake** for build configuration and integrates **clangd** for real-time code analysis and style enforcement.

### Build the Project
1. Ensure all dependencies listed in `.devcontainer/Dockerfile` are installed.
2. Configure the build:
   ```bash
   cmake -B build -S . -DENABLE_COVERAGE=OFF -DCMAKE_BUILD_TYPE=Release
   ```
3. Compile the source:
   ```bash
   cmake --build build
   ```

## Usage
### Running Tests
```bash
./build/tests/log_test
```

### Running the Application
```bash
./build/src/log_app --masterFile ./test_logs/logs.txt --outdir ./test_logs/out
```

## Quality Assurance & Tools
The project includes automated targets for code quality and documentation.

> **Note on `cpplint`:** Some rules enforced by `cpplint` are based on legacy 2006 standards (such as specific header inclusion orders). These may occasionally trigger warnings despite modern C++ best practices.

Use the following commands to execute quality assurance tasks:
```bash
# Run memory check
cmake --build build --target valgrind

# Run style and static analysis
cmake --build build --target cpplint
cmake --build build --target cppcheck
cmake --build build --target format

# Generate documentation
cmake --build build --target doxygen
```

## Code Coverage
To generate coverage reports, configure the build with debug symbols enabled:
```bash
cmake -B build -S . -DENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target coverage
```
