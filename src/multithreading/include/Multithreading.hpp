//
// Created by lukasz on 14.04.25.
//

#ifndef AIZO_1_SRC_UTILS_INCLUDE_MULTITHREADINGUTILS_HPP_
#define AIZO_1_SRC_UTILS_INCLUDE_MULTITHREADINGUTILS_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <BlockingQueue.hpp>
#include <LinkedList.hpp>
#include <SpinningLock.hpp>

namespace Multithreading {
  std::vector<uint8_t> getIsolatedCpus();
}

#endif //AIZO_1_SRC_UTILS_INCLUDE_MULTITHREADINGUTILS_HPP_
