// FUNC_NAME: NetSession::processIncomingPacket
// Function address: 0x0055de60
// Role: Handles incoming network packet or event data, processes through packet manager and triggers state-dependent action.

void NetSession::processIncomingPacket(void* packetData)
{
    // Initialize session or get singleton
    initSession();

    // Retrieve packet manager from this session
    int* packetManager = *(int**)(this + 0x18); // +0x18: pointer to PacketManager

    // Begin critical section or context push
    enterCriticalSection();

    // Call virtual method at vtable offset 0x40 on the transport object (from packetManager +0xd0)
    (**(code**)(*(int*)(packetManager + 0xd0) + 0x40))(&DAT_01139820); // DAT_01139820 = global NetSession singleton

    // End critical section or context pop
    exitCriticalSection();

    // Call virtual method at vtable offset 0x44
    (**(code**)(*(int*)(packetManager + 0xd0) + 0x44))(&DAT_01139820);

    // Parse or decode the incoming packet data
    decodePacket(packetData);

    // Extract sequence/ack field from packet header (at offset +8)
    int sequenceField = *(int*)(packetData + 8); // packetData +0x8: sequence or acknowledgment number

    // Re-fetch packet manager (should be same)
    packetManager = *(int**)(this + 0x18);

    // Enter critical section again
    enterCriticalSection();

    // Call virtual method at vtable offset 0x58, passing sequence field and a local result buffer
    int resultBuffer; // local stack variable
    (**(code**)(*(int*)(packetManager + 0xd0) + 0x58))(sequenceField, &resultBuffer);

    // If session is in a specific state (e.g., ready to send reply)
    if (*(int*)(this + 0x10c) == 1) { // +0x10c: state flag (1 = connected/active)
        triggerReplyEvent(); // Notify or schedule further processing
    }
}