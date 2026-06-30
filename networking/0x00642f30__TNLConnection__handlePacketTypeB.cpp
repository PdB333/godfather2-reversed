// FUNC_NAME: TNLConnection::handlePacketTypeB
int __thiscall TNLConnection::handlePacketTypeB(PacketHeader* packet) {
    int sequence;
    
    checkPacketIntegrity(); // FUN_00642b00
    if (packet->type == 0xB) {
        sequence = packet->sequence; // packet[1] at +0x04
        if (packet->field3 == packet->field4) { // packet[3] at +0x0C vs packet[4] at +0x10
            return sequence;
        }
        if (this->nextExpectedSequence <= sequence) { // this +0x34
            acknowledgePacket(sequence); // FUN_00642d90
            return packet->sequence;
        }
    }
    discardPacket(); // FUN_00642ec0
    return packet->sequence;
}