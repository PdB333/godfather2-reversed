// FUNC_NAME: TNLConnection::processIncomingPacket
// Address: 0x004979c0, Role: Handles incoming packet validation and dual-queueing for transport
// Dependencies: isPacketValid(seq, flags) at 0x00497a60; queuePacket(transport, info) at 0x00498ca0; transportTick() at 0x00498350

void __thiscall TNLConnection::processIncomingPacket(int this, uint packetData, uint seqNum, uint flags)
{
    bool isValid;
    struct PacketInfo {
        uint data;
        uint seq;
        uint flags;
    } info;

    isValid = isPacketValid(seqNum, flags); // checks sequence/flags validity
    if (isValid == false) {
        // First queue: normal order (data, seq, flags)
        info.data = packetData;
        info.seq = seqNum;
        info.flags = flags;
        queuePacket(*(uint *)(this + 0x1c), &info); // +0x1c: transport handle/ID
        transportTick();

        // Second queue: swapped seq and flags (data, flags, seq)
        info.flags = seqNum;
        info.data = packetData;
        info.seq = flags;
        queuePacket(*(uint *)(this + 0x1c), &info);
        transportTick();
    }
}