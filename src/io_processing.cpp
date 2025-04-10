/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/io_processing.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "src/logger.hpp"

DoublyLL<int> *IO_Processing::readAnnFromFile(const std::string filename) {
  std::ifstream file(filename);

  if (!file) {
    Logger::getInstance()->log("unable to open the file " + filename,
                               Logger::LogLevel::HIGH);
    return nullptr;
  }

  DoublyLL<int> *ind = new DoublyLL<int>();
  std::string line;

  while (std::getline(file, line)) {
    int ind_num = std::stoi(line);
    ind->push_back(ind_num);
  }

  file.close();
  Logger::getInstance()->log("File read: " + filename, Logger::LogLevel::HIGH);
  return ind;
}

Signal *IO_Processing::readFromFile(std::string filename) {
  std::ifstream file(filename);

  if (!file) {
    Logger::getInstance()->log("unable to open the file " + filename,
                               Logger::LogLevel::HIGH);
    return nullptr;
  }

  Signal *sig = new Signal();
  std::string line;
  if (!std::getline(file, line)) {
    file.close();
    return nullptr;
  }
  sig->fs = std::stoi(line);

  while (std::getline(file, line)) {
    float f_num = std::stof(line);
    sig->signal->push_back(f_num);
  }

  file.close();
  Logger::getInstance()->log("File read: " + filename, Logger::LogLevel::HIGH);
  return sig;
}

void IO_Processing::writeToFile(std::string filename, DoublyLL<int> *x) {
  std::ofstream file(filename);

  if (!file) {
    Logger::getInstance()->log("unable to open the file " + filename,
                               Logger::LogLevel::HIGH);
    return;
  }

  for (auto it = x->begin(); it != x->end(); ++it) {
    file << (*it) << std::endl;
  }

  file.close();
  Logger::getInstance()->log("File written: " + filename,
                             Logger::LogLevel::HIGH);
  return;
}

void IO_Processing::writeToFile(std::string filename, Signal *x) {
  std::ofstream file(filename);

  if (!file) {
    Logger::getInstance()->log("unable to open the file " + filename,
                               Logger::LogLevel::HIGH);
    return;
  }

  file << x->fs << std::endl;

  for (auto it = x->signal->begin(); it != x->signal->end(); ++it) {
    file << (*it) << std::endl;
  }

  file.close();
  Logger::getInstance()->log("File written: " + filename,
                             Logger::LogLevel::HIGH);
  return;
}
