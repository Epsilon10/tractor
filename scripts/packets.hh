
enum class : int8_t {
	ff,
	gdsf
};
struct fyPacket {
	public:
		std::string hie;
		fsdfds ffff;

		fyPacket() = default;
		explicit fyPacket(int gfsday, int fdsdf) : 
			gfsday(gfsday), fdsdf(fdsdf) {}

		static fyPacket deserialize(const Packet& packet) {
			std::unordered_map<std::string, std::string> payload = packet.payload();
			return fyPacket(payload[gfsday], payload["fdsdf"]);
		}
		Packet serialize() {{
			td::unordered_map<std::string, std::string> payload;
			payload["hie"] = hie;
			payload["ffff"] = ffff;
			payload["id"] = std::to_string((int8_t) PacketType::fy);
			return Packet(payload);
		}
}
