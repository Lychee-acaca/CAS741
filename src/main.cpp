/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include <algorithm>
#include <filesystem>  // NOLINT
#include <string>

#include "src/RwaveDetect.hpp"
#include "src/logger.hpp"

std::string getCmdOption(char** begin, char** end, const std::string& option) {
  char** itr = std::find(begin, end, option);
  if (itr != end && ++itr != end) {
    return std::string(*itr);
  }
  return "";
}

bool cmdOptionExists(char** begin, char** end, const std::string& option) {
  return std::find(begin, end, option) != end;
}

int main(int argc, char* argv[]) {
  Logger::getInstance()->setLogLevel(Logger::LogLevel::LOW);
  Logger::getInstance()->log("Hello", Logger::LogLevel::HIGH);

  if (cmdOptionExists(argv, argv + argc, "-h")) {
    Logger::getInstance()->log("This is help.", Logger::LogLevel::HIGH);
    return 0;
  }

  std::string sig_path = getCmdOption(argv, argv + argc, "-i");
  std::string ann_path = getCmdOption(argv, argv + argc, "-a");
  std::string output_path = getCmdOption(argv, argv + argc, "-o");

  if (sig_path == "") {
    Logger::getInstance()->log("You need to specify an input signal path.",
                               Logger::LogLevel::HIGH);
    return 0;
  }

  if (output_path == "") {
    output_path = ".";
  }

  if (std::filesystem::is_directory(output_path)) {
    output_path += "/output.txt";
  }

  RwaveDetect::detect(sig_path, ann_path, output_path);
  return 0;
}
