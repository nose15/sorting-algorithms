//
// Created by lukasz on 14.04.25.
//

#include <FileUtils.hpp>

namespace FileUtils {
  std::vector<uint8_t> parseInts(const std::string& line) {
    auto nums = splitString(line, ',');

    std::vector<uint8_t> res;

    for (const auto & num : *nums) {
      if (num.find_first_of('-') == std::string::npos) {
        res.push_back(stoi(num));
        continue;
      }

      auto vec = splitString(num, '-');
      for (int i = stoi(vec->at(0)); i <= stoi(vec->at(1)); i++) {
        res.push_back(i);
      }
    }
    std::cout << std::endl;

    return res;
  }

  std::unique_ptr<std::vector<std::string>> splitString(const std::string& str, char splitter) {
    auto vec = std::make_unique<std::vector<std::string>>();
    std::string curr_substr;
    for (auto c : str) {
      if (!curr_substr.empty() && c == splitter) {
        vec->push_back(curr_substr);
        curr_substr.clear();
        continue;
      }

      curr_substr.push_back(c);
    }
    vec->push_back(curr_substr);

    return std::move(vec);
  }
}

