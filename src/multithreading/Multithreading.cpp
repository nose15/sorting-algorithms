//
// Created by lukasz on 14.04.25.
//

#include <Multithreading.hpp>
#include <FileUtils.hpp>

// utils
namespace Multithreading {
  std::vector<uint8_t> getIsolatedCpus() {
    std::ifstream file("/sys/devices/system/cpu/isolated");

    if (file) {
      std::string line;
      std::getline(file, line);
      return FileUtils::parseInts(line);
    }

    return {};
  }
}