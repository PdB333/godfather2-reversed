// FUNC_NAME: TNLConnection::removeReliablePacket(uint32_t packetId)

struct PacketSlot {
    uint32_t unknown0; // +0
    uint32_t unknown1; // +4
    uint32_t unknown2; // +8
    uint32_t unknown3; // +12
    uint8_t  hasData;  // +16
    uint8_t  pad[3];   // +17-19
    uint32_t packetId; // +20
};

void __thiscall TNLConnection::removeReliablePacket(uint32_t packetId)
{
    // Check if the packet matches the current active packet
    if (packetId == *(uint32_t*)(this + 0x6a4))
    {
        *(uint32_t*)(this + 0x6a4) = 0;    // clear current packet ID
        *(uint32_t*)(this + 0x6b8) = 0;    // clear associated data
        return;
    }

    // Search through the 32 reliable packet slots
    PacketSlot* slots = (PacketSlot*)(this + 0x6c0);
    for (int i = 0; i < 0x20; i++)
    {
        PacketSlot* slot = &slots[i];
        if (slot->packetId == packetId)
        {
            // Free packet data if it was allocated
            if (slot->hasData != 0)
            {
                releasePacketInfo(packetId); // FUN_006a54d0
            }

            // Clear the entire slot
            slot->packetId = 0;
            slot->hasData = 0;
            slot->unknown0 = 0;
            slot->unknown1 = 0;
            slot->unknown2 = 0;
            slot->unknown3 = 0;
        }
    }
}