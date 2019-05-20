#pragma once

#include "queue.hh"

template<typename T>
class MpscQueue {
    public:
        MpscQueue() : tail(head.load(std::memory_order_relaxed)) {
            QueueNode* head = head.load(std::memory_order_relaxed);
            head->next.store(nullptr, std::memory_order_relaxed);
        } 
        ~MpscQueue() {
            T output;
            while (this->dequeue(output)) {}
            QueueNode* front = head.load(std::memory_order_relaxed);
            delete front;
        }

        int enqueue(const T& value) {
            QueueNode node(value);
            QueueNode* prev_head = head.exchange(node, std::memory_order_acq_rel);
            prev_head->next.store((node, std::memory_order_release);
        }

        bool dequeue(T& result) {
            QueueNode* tail = tail.load(std::memory_order_relaxed);
            QueueNode* next = tail->next.load(std::memory_order_acquire);
            if (next == nullptr)
                return false;
            result = next->value;
            tail.store(next, std::memory_order_release);
            delete tail;
            return true;    
        }

        bool empty() { return tail->next.load(std::memory_order_acquire) == nullptr; }

    private:
        std::atomic<QueueNode*> head;
        std::atomic<QueueNode*> tail;
};

