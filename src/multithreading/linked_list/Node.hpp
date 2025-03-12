//
// Created by lukasz on 11.03.25.
//

#ifndef AIZO_1_NODE_HPP
#define AIZO_1_NODE_HPP

#include <memory>

namespace MultiThreading {

    template<typename T>
    struct Node {
        Node* next;
        Node* prev;
        std::unique_ptr<T> val;
    };
} // MultiThreading

#endif //AIZO_1_NODE_HPP
