// FUNC_NAME: NetSession::initializePacketWindowSlots
void initializePacketWindowSlots()
{
    // Initialize 32 packet slots (0x18-byte stride in default source data)
    // g_packetSlotFlags: flags per slot (cleared)
    // g_packetSlotSequence: default sequence numbers per slot (copied from offset 0 of each default struct)
    // g_packetSlotData: additional slot data (cleared)
    for (int i = 0; i < 32; i++)
    {
        g_packetSlotFlags[i] = 0;                                                   // +0x0 per slot (uint32)
        g_packetSlotSequence[i] = *(uint32_t*)((uint8_t*)g_packetSlotDefaults + i * 0x18); // offset 0 of default struct
        g_packetSlotData[i] = 0;                                                    // +0x0 per slot (uint32)
    }
}