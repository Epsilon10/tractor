#include "messageable.hh"

Messageable::Messageable(const std::string& name) 
    : name(name), execution_thread(&Messageable::run_periodic, this) , is_running(true) {}

Messageable::~Messageable() {
    is_running = false;
    execution_thread.join();
} 

void Messageable::subscribe(const Messageable& target) {
    auto it = 
        std::find(subscriptions.cbegin(), subscriptions.cend(), this);
    if (it == subscriptions.cend())
        subscriptions.insert({target.name, target});
}

void Messageable::unsubscribe(const Messageable& target) {
    auto it = 
        std::find(subscriptions.cbegin(), subscriptions.cend(), this);
    if (it != subscriptions.cend())
        subscriptions.erase(it);
}

void Messageable::run_periodic() {
    while (is_running) {
        while (mailbox.empty())
            sched_yield(); // reschedule
        Message msg;
        if (mailbox.dequeue(msg))
            process_message(msg);
        else
            continue; // uhh log something maybe
    }
}