//
// Created by lukasz on 14.04.25.
//

#ifndef AIZO_1_SRC_UTILS_INCLUDE_FILEUTILS_HPP_
#define AIZO_1_SRC_UTILS_INCLUDE_FILEUTILS_HPP_

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <filesystem>
#include <fstream>
#include <algorithm>

namespace FileUtils {
std::vector<uint32_t> parseInts(const std::string &line);
std::unique_ptr<std::vector<std::string>> splitString(const std::string &str, char splitter);

// file utils
template<typename T>
size_t readArr(const std::filesystem::path &f, std::shared_ptr<T[]> &ref) {
  std::fstream file;
  file.open(f);

  size_t len;
  std::string line;
  if (getline(file, line)) {
    len = std::stoi(line);
  } else {
    throw std::length_error("File is empty");
  }

  ref = std::shared_ptr<T[]>(new T[len]);
  for (int i = 0; i < len; i++) {
    if (!getline(file, line)) {
      throw std::range_error("wrong file format");
    }

    if (typeid(T) == typeid(int)) {
      ref[i] = std::stoi(line);
    } else if (typeid(T) == typeid(double)) {
      std::replace(line.begin(), line.end(), ',', '.');
      ref[i] = std::stod(line);
    }
  }

  return len;
}
}

#endif //AIZO_1_SRC_UTILS_INCLUDE_FILEUTILS_HPP_
