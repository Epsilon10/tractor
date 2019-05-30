**Packet**

- ID -> maps to specific packet
- Payload -> map of values to be injected into a specific packet

**Example**: GamepadPacket

**MovementPacket**

- Topic -> "Robot/MovementCommand"

- Fields: 

- - double right_stick_x

  - double right_stick_y

    

- ID: cast to int_8
- Serialize to packet: inject id and map 

