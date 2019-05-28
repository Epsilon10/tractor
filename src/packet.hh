#include <string>
#include <unordered_map>

class Packet {
    public:
        explicit Packet::Packet(const std::unordered_map<std::string, std::string> payload) 
            : _payload(payload), topic(_payload["topic"]), id((int8_t) std::atoi(_payload["id"].c_str())) {}
        std::string topic; 
        int8_t id;
    private:
        std::unordered_map<std::string, std::string> _payload;
};