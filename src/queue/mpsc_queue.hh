#pragma once

#include "queue.hh"
#include <iostream>

template<typename T>
class MpscQueue {
    public:
        MpscQueue() : _head(new QueueNode<T>()), _tail(_head.load(std::memory_order_relaxed)) {
            QueueNode<T>* front = _head.load(std::memory_order_relaxed);
            front->next.store(nullptr, std::memory_order_relaxed);
        } 
        ~MpscQueue() {
            T output;
            while (this->dequeue(output)) {}
            QueueNode<T>* front = _head.load(std::memory_order_relaxed);
            delete front;
        }

        void enqueue(const T& value) {
            QueueNode<T>* node = new QueueNode<T>(); // using new here cuz we want it to be persistent and not cleared
            node->value = value;
            node->next.store(nullptr, std::memory_order_relaxed);
            
            QueueNode<T>* prev_head = _head.exchange(node, std::memory_order_acq_rel);
            prev_head->next.store(node, std::memory_order_release);
        }

        bool dequeue(T& result) {
            QueueNode<T>* tail = _tail.load(std::memory_order_relaxed);
            QueueNode<T>* next = tail->next.load(std::memory_order_acquire);
            if (next == nullptr)
                return false;
            result = next->value;
            _tail.store(next, std::memory_order_release);
            delete tail;
            return true;    
        }

        bool empty() { return _tail->next.load(std::memory_order_acquire) == nullptr; }

    private:
        std::atomic<QueueNode<T>*> _head;
        std::atomic<QueueNode<T>*> _tail;
};

