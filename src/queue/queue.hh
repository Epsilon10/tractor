#pragma once

#include <atomic>
#include <assert.h>

template<typename T>
struct QueueNode {
    public:
        QueueNode() : value(value) {
            next.store(NULL, std::memory_order_relaxed);
        }
    private:
        T value;
        std::atomic<QueueNode*> next;

};
