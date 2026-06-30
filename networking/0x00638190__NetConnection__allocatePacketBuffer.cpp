// FUNC_NAME: NetConnection::allocatePacketBuffer
// Address: 0x00638190
// Role: Allocates a packet buffer of specified size (including header) and links it into the connection's pending send queue.
// Fields of this (EDI):
//   +0x10 : pointer to a queue head structure (like a singly linked list sentinel)
//   +0x10 +0x0c: pointer to the current tail/head of the list (used for insertion)

void NetConnection::allocatePacketBuffer(int numPayloadDwords, uint32_t* payloadHeader) {
    uint32_t allocSize;
    uint8_t* newPacket;
    int32_t* listCount;
    uint32_t uVar2; // unused
    uint32_t uVar3; // temp copy of second dword from payloadHeader

    // Total size = header (0x18 bytes) + payload dwords * 4
    allocSize = numPayloadDwords * 4 + 0x18;

    newPacket = nullptr;
    if (allocSize == 0) {
        // Zero size not allowed – return null
        newPacket = nullptr;
    }
    else {
        if (allocSize < 0xfffffffd) { // valid size range
            // Use global memory allocator (likely from EARS memory manager)
            newPacket = (uint8_t*)(*DAT_012059dc)(0, allocSize);
            if (newPacket == nullptr) {
                // Allocation failed – handle error (may throw or log)
                if (this != nullptr) {
                    FUN_00635a80(); // e.g., onAllocationError()
                    return;
                }
                goto LAB_006381a4; // fallback to null
            }
        }
        else {
            // Size too large – call invalid-size handler (likely exception)
            FUN_00633920(); // onInvalidSize()
        }

        // Update allocation statistics in the queue sentinel (if this is valid)
        if (this != nullptr) {
            listCount = (int*)(*(int*)(this + 0x10) + 0x24);
            *listCount += allocSize; // track memory usage
        }
    }

LAB_006381a4:
    // Insert the new packet at the head of the linked list
    // first, store the old head pointer in the new packet's link field (offset 0)
    *(uint32_t*)newPacket = *(uint32_t*)(*(int*)(this + 0x10) + 0xc);
    // update the list head to point to this new packet
    *(uint32_t*)(*(int*)(this + 0x10) + 0xc) = (uint32_t)newPacket;

    // Initialize packet header fields:
    // Offset 4: packet type? (constant 6)
    newPacket[4] = 0;
    newPacket[5] = 6;   // packet type byte
    newPacket[6] = 0;
    // Offset 7: payload size in dwords (stored as a char – likely limited to 256)
    newPacket[7] = (uint8_t)numPayloadDwords;

    // Copy the caller-provided header dwords (e.g., sequence/ack numbers) into payload area
    *(uint32_t*)(newPacket + 16) = payloadHeader[0];
    uVar3 = payloadHeader[1];
    *(uint32_t*)(newPacket + 20) = uVar3;

    return;
}