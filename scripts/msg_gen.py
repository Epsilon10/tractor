ending = "hh"

def write_packet_struct(
    packet_name, member_types, member_names, member_vals = None
):
    """Write the packet struct

    Keyword arguments:
    output_dir -- output dir to write the struct source
    packet_name -- name of the message
    member_types -- data types of the member vars
    [member_vals] -- defaults to intialize the struct members to

    """
    with open(f"packets.{ending}", "a") as output:
        output.write(f"struct {packet_name}Packet {{\n")
        output.write(f"\tpublic:\n")
        for type, name in zip(member_types, member_names):
            output.write(f"\t\t{type} {name};\n")
        output.write("\n")

        # Write constructors
        output.write(f"\t\t{packet_name}Packet() = default;\n")
        output.write(f"\t\texplicit {packet_name}Packet(")
        num_args_idx = len(member_types) - 1
        for i in range(num_args_idx):
            output.write(f"{member_types[i]} {member_names[i]}, ")
        output.write(f"{member_types[num_args_idx]} {member_names[num_args_idx]}) : \n\t\t\t")
        for i in range(num_args_idx):
            output.write(f"{member_names[i]}({member_names[i]}), ")
        output.write(f"{member_names[num_args_idx]}({member_names[num_args_idx]}) {{}}")
        output.write("\n\n")

        # Deserialize from map to struct
        output.write(f"\t\tstatic {packet_name}Packet deserialize(const Packet& packet) {{\n")
        output.write(f"\t\t\tstd::unordered_map<std::string, std::string> payload = packet.payload();\n")
        output.write(f"\t\t\treturn {packet_name}Packet(")
        for i in range(num_args_idx):
            output.write(f"payload[\"{member_names[i]}\"], ")
        output.write(f"payload[\"{member_names[num_args_idx]}\"]);\n")
        output.write("\t\t}")
        output.write("\n")

        # Serialize to map from struct and return a packet instance
        output.write("\t\tPacket serialize() {{\n")
        output.write("\t\t\tstd::unordered_map<std::string, std::string> payload;\n")
        for name in member_names:
            output.write(f"\t\t\tpayload[\"{name}\"] = {name};\n")
        output.write(f"\t\t\tpayload[\"id\"] = std::to_string((int8_t) PacketType::{packet_name});\n")
        output.write(f"\t\t\treturn Packet(payload);\n\t\t}}")
        output.write("\n}\n")

def write_packet_type_enum(*packet_names):
    enum_header = 'enum class PacketType : int8_t {\n'
    body_string = ''
    for i in range(len(packet_names) - 1):
        body_string+='\t' + packet_names[i] + ',\n'
    body_string+='\t' + packet_names[len(packet_names) - 1] + '\n'
    footer = '};'
    with open(f"packets.{ending}", "a") as output:
        output.write('\n')
        output.write(enum_header)
        output.write(body_string)
        output.write(footer + '\n\n')

    

def write_packet_file_base():
    with open(f"packets.{ending}", "w") as output:
        output.write("#pragma once\n")
        output.write("#include <string>\n")
        output.write("#include <unordered_map>\n")
        output.write("#include \"packet.hh\"\n")

write_packet_file_base()
write_packet_type_enum('test1', 'test2')
write_packet_struct('test1', ['int', 'std::string'], ['f1', 'f2'])
