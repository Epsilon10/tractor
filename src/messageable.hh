#pragma once

#include <string>
#include "queue/mpsc_queue.hh"
#include "message.hh"
#include <thread>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <sched.h>

class Messageble;
class Messageable {
    public:
        explicit Messageable(const std::string& name);
        ~Messageable();
        void subscribe(const Messageable& target);
        void unsubscribe(const Messageable& target);
        void run_periodic();
        const std::string name;
        virtual void process_message(const Message& msg);
    private:
        bool is_running;
        std::unordered_map<const std::string, Messageable> subscriptions;
        std::thread execution_thread;
        MpscQueue<Message> mailbox;


        
}; 