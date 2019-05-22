#pragma once

#include <atomic>
#include <assert.h>

template<typename T>
struct QueueNode {
    public:
        QueueNode() {
            next.store(NULL, std::memory_order_relaxed);
        }
        std::atomic<QueueNode*> next;
        T value;
};
