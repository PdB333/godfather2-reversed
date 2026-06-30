// FUNC_NAME: NetConnection::processPacket
void __thiscall NetConnection::processPacket(void) {
    // param_1 is this pointer
    int* packetBuffer; // in_EAX - pointer to received packet data
    int* internalPtr; // pointer to internal connection state at this+0x1c
    uint newTimestamp;
    uint newSequence;
    uint temp;

    internalPtr = *(int**)((char*)this + 0x1c);

    // Update internal time/state
    FUN_00642b00();

    // Check packet type
    if (*packetBuffer == 0xB) { // Data packet type (11)
        // If acknowledgement sequence numbers match, skip normal processing
        if (packetBuffer[3] != packetBuffer[4]) {
            // Check if remote sequence is within valid window
            if (*(int*)(internalPtr + 0x34) <= packetBuffer[1]) {
                // Acknowledge this sequence
                FUN_00642d90(packetBuffer[1]);
                goto process_ack;
            }
        } else {
            goto process_ack;
        }
    }

    // Normal packet processing
    FUN_00642ec0();

process_ack:
    // Copy timestamp from field at +0x04 to +0x08
    *(int*)((char*)this + 0x08) = *(int*)((char*)this + 0x04);

    // Handle acknowledge packet type (0x11F = 287)
    if (*(int*)((char*)this + 0x14) == 0x11F) {
        // Get timestamp from the incoming packet
        newTimestamp = FUN_00639c70((int)((char*)this + 0x10));
        *(int*)((char*)this + 0x0C) = newTimestamp;
    } else {
        // Shift acknowledge state
        *(int*)((char*)this + 0x0C) = *(int*)((char*)this + 0x14);
        *(int*)((char*)this + 0x10) = *(int*)((char*)this + 0x18);
        *(int*)((char*)this + 0x14) = 0x11F;
    }

    // Get current local time for the outgoing packet
    local_18 = FUN_0063dd40();

    // Prepare packet header fields
    uint packetSize = 4;
    uint seqFlags = 4;
    uint reserved = 0xFFFFFFFF;
    uint reserved2 = 0xFFFFFFFF;

    // Allocate an outgoing acknowledge packet via the connection manager
    int* outPacket = (int*)FUN_00642970(*(int*)((char*)this + 0x1C), &packetSize);

    // Get next outgoing sequence number
    newSequence = FUN_00642fc0();
    packetBuffer[2] = newSequence; // Set packet sequence
    *packetBuffer = 8;             // Set packet type to Acknowledge (8)
    return;
}