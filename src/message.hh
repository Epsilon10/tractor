#pragma once

#include <vector>
#include <string>

struct Message {
    public:
        Message() {}
        const std::string topic;
        const std::string payload;        
};