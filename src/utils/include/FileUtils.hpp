//
// Created by lukasz on 14.04.25.
//

#ifndef AIZO_1_SRC_UTILS_INCLUDE_FILEUTILS_HPP_
#define AIZO_1_SRC_UTILS_INCLUDE_FILEUTILS_HPP_

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

namespace FileUtils {
  std::vector<uint8_t> parseInts(const std::string& line);
}

#endif //AIZO_1_SRC_UTILS_INCLUDE_FILEUTILS_HPP_
