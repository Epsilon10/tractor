#pragma once

#include <vector>
#include <string>
#include <unordered_map>

struct Message {
    public:
        Message() {}
        virtual const std::string topic();
        virtual std::unordered_map<const std::string, const std::string> payload();        
};

struct ButtonMessage {
    const std::string topic() {
        return "ButttonMessage";
    }


}; 
