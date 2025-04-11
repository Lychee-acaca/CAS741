/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/logger.hpp"

#include <gtest/gtest.h>

TEST(LoggerTest, outputTest) {
  Logger::getInstance()->setLogPath("testlog.txt");

  Logger::getInstance()->setLogLevel(Logger::LogLevel::LOW);
  Logger::getInstance()->log("111", Logger::LogLevel::HIGH);
  Logger::getInstance()->log("222", Logger::LogLevel::MEDIUM);
  Logger::getInstance()->log("333", Logger::LogLevel::LOW);

  Logger::getInstance()->setLogLevel(Logger::LogLevel::MEDIUM);
  Logger::getInstance()->log("444", Logger::LogLevel::HIGH);
  Logger::getInstance()->log("555", Logger::LogLevel::MEDIUM);
  Logger::getInstance()->log("666", Logger::LogLevel::LOW);

  Logger::getInstance()->setLogLevel(Logger::LogLevel::HIGH);
  Logger::getInstance()->log("777", Logger::LogLevel::HIGH);
  Logger::getInstance()->log("888", Logger::LogLevel::MEDIUM);
  Logger::getInstance()->log("999", Logger::LogLevel::LOW);
}
