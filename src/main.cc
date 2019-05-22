#include "queue/mpsc_queue.hh"
#include <iostream>
#include <thread>

void func(MpscQueue<int>& queue, int a, int b);

int main() {
    MpscQueue<int> queue;
    std::thread t1(func, std::ref(queue), 1, 2);
    std::thread t2(func, std::ref(queue), 3, 4);
    t1.join();
    t2.join();
}

void func(MpscQueue<int>& queue, int a, int b) {
    queue.enqueue(a);
    queue.enqueue(b);
    int value;
    while (queue.dequeue(value))
        std::cout << value << std::endl;
}