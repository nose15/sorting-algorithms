//
// Created by lukasz on 14.04.25.
//

#include <MultithreadingUtils.hpp>
#include <FileUtils.hpp>

// utils
std::vector<uint8_t> getIsolatedCpus() {
  std::ifstream file("/sys/devices/system/cpu/isolated");

  if (file) {
    std::string line;
    std::getline(file, line);
    return FileUtils::parseInts(line);
  }

  return {};
}
