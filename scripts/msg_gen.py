ending = "hh"

def write_packet_struct(
    output_dir, packet_name, ctor_types, ctor_names, member_types, member_names, member_vals = None
):
    """Write the packet struct

    Keyword arguments:
    output_dir -- output dir to write the struct source
    packet_name -- name of the message
    ctor_types -- data types of the ctor args
    ctor_names -- names of the ctor args
    member_types -- data types of the member vars
    [member_vals] -- defaults to intialize the struct members to

    """
    with open(f"Packets.{ending}") as output:
        output.write(f"struct {packet_name}Packet {{\n")
        output.write(f"\tpublic:\n")
        for type, name in zip(member_types, member_names):
            output.write(f"\t\t{type} {name};\n")
        output.write("\n")
        output.write(f"\t\t{packet_name}Packet() = default;\n")
        output.write(f"\t\texplicit {packet_name}Packet(")
        num_args_idx = len(ctor_types) - 1
        for i in range(num_args_idx):
            output.write(f"{ctor_types[i]} {ctor_names[i]}, ")
        output.write(f"{ctor_types[num_args_idx]} {ctor_names[num_args_idx]}) : \n\t\t\t")
        for i in range(num_args_idx):
            output.write(f"{ctor_names[i]}({ctor_names[i]}), ")
        output.write(f"{ctor_names[num_args_idx]}({ctor_names[num_args_idx]}) {{}}")
        output.write("\n\n")
        output.write(f"\t\tstatic {packet_name}Packet deserialize(const Packet& packet) {{\n")
        output.write(f"\t\t\tstd::unordered_map<std::string, std::string> payload = packet.payload();\n")
        output.write(f"\t\t\treturn {packet_name}Packet(")
        for i in range(num_args_idx):
            output.write(f"payload[{ctor_names[i]}], ")
        output.write(f"payload[{ctor_names[num_args_idx]}]);\n")
        output.write("\t\t}")
        output.write("\n")
        output.write("\t\tPacket serialize() {{\n")
        output.write("\t\t\ttd::unordered_map<std::string, std::string> payload;\n")
        for name in member_names:
            output.write(f"\t\t\tpayload[\"{name}\"] = {name};\n")
        output.write(f"return Packet(payload")



