// FUNC_NAME: NetConnection::prepareReliablePacket
// Function at 0x0063e790: Prepares a reliable data packet for send, updating sequence numbers and state.
// This is likely part of the EA EARS network layer (modified TNL) for managing reliable packet transmission.

void __thiscall NetConnection::prepareReliablePacket(void* thisPtr) {
    // thisPtr points to NetConnection structure
    // Offsets (relative to thisPtr):
    // +0x04: currentSendSequence (int)
    // +0x08: lastAckedSequence (int)
    // +0x0C: pendingSequence (int) // used for packet ordering
    // +0x10: pendingPayloadSize (int)
    // +0x14: packetType (int) // 0x11F = empty/slot available
    // +0x18: nextPayloadSize (int)
    // +0x1C: sendWindowManager (void*) - pointer to send window state

    int* sendWindow = *(int**)((int)thisPtr + 0x1C); // send window manager pointer

    // Step 1: Get current packet buffer (likely a segment or pending packet)
    int* packetBuffer = (int*)getCurrentPacketBuffer(); // FUN_00642b00 - returns pointer to packet struct
    // packetBuffer fields: [0]=type, [1]=sequence, [2]=checksum, [3]=prevSequenceOut, [4]=prevSequenceIn?

    if (*packetBuffer == 0xB) { // packet type 0xB = control/ack packet
        if (packetBuffer[3] != packetBuffer[4]) { // sequence mismatch?
            if (*(int*)(sendWindow + 0x34) <= packetBuffer[1]) { // check window capacity
                finalizePacket(packetBuffer[1]); // FUN_00642d90 - likely acks or discards old packet
                goto afterHandle;
            }
        }
    }
    handlePacketAcknowledgment(); // FUN_00642ec0 - processes ack info

afterHandle:
    // Update sequence state: copy current send sequence to last acked
    *(int*)((int)thisPtr + 0x8) = *(int*)((int)thisPtr + 0x4);

    // Manage packet type / payload state
    if (*(int*)((int)thisPtr + 0x14) == 0x11F) { // slot empty?
        int copied = copyPacketHeader((void*)((int)thisPtr + 0x10)); // FUN_00639c70
        *(int*)((int)thisPtr + 0xC) = copied;
    } else {
        // Shift pending fields
        *(int*)((int)thisPtr + 0xC) = *(int*)((int)thisPtr + 0x14);
        *(int*)((int)thisPtr + 0x10) = *(int*)((int)thisPtr + 0x18);
        *(int*)((int)thisPtr + 0x14) = 0x11F; // mark as empty
    }

    // Prepare checksum computation input
    int tickCount = getTickCount(); // FUN_0063dd40
    struct ChecksumInput {
        int size1;   // = 4 (type indicator)
        int time;    // tickCount
        int size2;   // = 4 (payload size?)
        int reserved; // output of checksum function, uninitialized input
        int pad1;    // = -1
        int pad2;    // = -1
    } input;
    input.size1 = 4;
    input.time = tickCount;
    input.size2 = 4;
    input.pad1 = -1;
    input.pad2 = -1;
    // input.reserved is left uninitialized but will be overwritten by the call
    int checksumResult = computeChecksum(sendWindow, &input); // FUN_00642970 - returns checksum value
    // input.reserved is now the checksum? Actually the function returns a value, not via the buffer.
    // The buffer may be used as additional parameter; we keep the return.

    int packetChecksum = generatePacketChecksum(); // FUN_00642fc0 - returns final checksum to store

    // Update packet buffer
    packetBuffer[2] = packetChecksum;
    packetBuffer[0] = 8; // packet type 8 = reliable data
}