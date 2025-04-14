//
// Created by lukasz on 14.04.25.
//

#include <FileUtils.hpp>

namespace FileUtils {
  std::vector<uint8_t> parseInts(const std::string& line) {
    std::vector<std::string> nums;
    std::stringstream stream(line);
    std::string segment;

    while (std::getline(stream, segment, ',')) {
      nums.push_back(segment);
    }

    for (const auto & num : nums) {
      std::cout << num << " ";
    }
    std::cout << std::endl;

    return {};
  }
}

