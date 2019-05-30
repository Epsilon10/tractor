#pragma once
#include <string>
#include <unordered_map>
#include "packet.hh"

enum class PacketType : int8_t {
	test1,
	test2
};

struct test1Packet {
	public:
		int f1;
		std::string f2;

		test1Packet() = default;
		explicit test1Packet(int f1, std::string f2) : 
			f1(f1), f2(f2) {}

		static test1Packet deserialize(const Packet& packet) {
			std::unordered_map<std::string, std::string> payload = packet.payload();
			return test1Packet(payload["f1"], payload["f2"]);
		}
		Packet serialize() {{
			std::unordered_map<std::string, std::string> payload;
			payload["f1"] = f1;
			payload["f2"] = f2;
			payload["id"] = std::to_string((int8_t) PacketType::test1);
			return Packet(payload);
		}
}
