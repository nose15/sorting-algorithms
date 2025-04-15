//
// Created by lukasz on 15.04.25.
//

#ifndef AIZO_1_SRC_UTILS_INCLUDE_MEASUREMENTUTILS_HPP_
#define AIZO_1_SRC_UTILS_INCLUDE_MEASUREMENTUTILS_HPP_

#include <memory>
#include <random>
#include <string>
#include <algorithm>


template <typename T>
std::unique_ptr<T[]> generateArr(size_t len, int32_t conf) {
  std::unique_ptr<T[]> arr = std::make_unique<T[]>(len);

  std::random_device rd; // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> dist(0, 10000); // define the range

  for (uint32_t i = 0; i < len; i++) {
    arr[i] = dist(gen);
  }

  switch (conf) {
    case 2:
      std::sort(arr.get(), arr.get() + (len / 3));
      break;
    case 3:
      std::sort(arr.get(), arr.get() + (len / 3) * 2);
      break;
    case 4:
      std::sort(arr.get(), arr.get() + len - 1);
      break;
    case 5:
      std::sort(arr.get(), arr.get() + len - 1);
      std::reverse(arr.get(), arr.get() + len - 1);
      break;
    default:
      break;
  }

  return std::move(arr);
}

#endif //AIZO_1_SRC_UTILS_INCLUDE_MEASUREMENTUTILS_HPP_
