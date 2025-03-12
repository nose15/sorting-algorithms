#ifndef AIZO_1_LINKEDLIST_HPP
#define AIZO_1_LINKEDLIST_HPP

#include <cstddef>
#include <Node.hpp>

namespace MultiThreading {

    template<typename T>
    class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        size_t size;
    public:
        LinkedList();
        size_t getSize();
        void push_front(std::unique_ptr<T> elem);
        std::unique_ptr<T> pop_back();
        ~LinkedList();
    };

    template<typename T>
    size_t LinkedList<T>::getSize() {
        return size;
    }

    template<typename T>
    LinkedList<T>::LinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    template<typename T>
    LinkedList<T>::~LinkedList() {
        while (head) {
            Node<T>* prevHead = head;
            head = head->next;
            delete prevHead;
        }

        tail = nullptr;
    }

    template<typename T>
    void LinkedList<T>::push_front(std::unique_ptr<T> elem) {
        auto* newNode = new Node<T>();
        newNode->val = std::move(elem);
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (size > 0) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else {
            head = newNode;
            tail = newNode;
        }
        size++;
    }

    template<typename T>
    std::unique_ptr<T> LinkedList<T>::pop_back() {
        if (size == 0) {
            return nullptr;
        }

        std::unique_ptr<T> val = std::move(tail->val);

        Node<T>* prev = tail->prev;
        if (prev) {
            prev->next = nullptr;
        }

        delete tail;
        tail = prev;
        size--;

        if (size == 0) {
            head = nullptr;
            tail = nullptr;
        }

        return val;
    }
}

#endif // AIZO_1_LINKEDLIST_HPP
