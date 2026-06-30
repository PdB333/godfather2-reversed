// FUNC_NAME: Connection::processReliablePacket
// Address: 0x00579450
// Processes an incoming reliable packet, updates sequence numbers, copies payload data,
// and invokes a callback. Returns 1 on success, 0 if packet is rejected (e.g., duplicate).

struct PacketHeader {
    int* objectPtr;          // param_2[0] - pointer to associated object (e.g., SimObject)
    uint8_t* payloadData;    // param_2[1] - pointer to packet payload
    int sequence;            // param_2[2] - packet sequence number
    int ackSequence;         // param_2[3] - acknowledgment sequence
    int ackFlags;            // param_2[4] - acknowledgment flags (or -1 for none)
    uint8_t isNotDuplicating; // param_2[5] - non-zero if not a duplicate
    int type;                // param_2[6] - packet type (3=?, 4=?)
};

void Connection::processTimerDecrement(float deltaTime)
{
    // Decrement timer array at +0xC0 (16 timers) by deltaTime, clamping to zero.
    for (int i = 0; i < 16; ++i)
    {
        if (timers[i] < deltaTime)
            timers[i] = 0.0f;
        else
            timers[i] -= deltaTime;
    }
    deltaTime = 0.0f; // Reset the delta after use
}

int FUN_00579450(int param_1, int* param_2) {
    // param_1: this pointer (Connection*)
    // param_2: PacketHeader as integer array
    
    Connection* conn = reinterpret_cast<Connection*>(param_1);
    PacketHeader* pkt = reinterpret_cast<PacketHeader*>(param_2);
    
    // Calculate new sequence index (ring buffer)
    int windowSize = conn->mWindowSize;             // +0x2E4
    int currentSeq = conn->mSequence;               // +0x2E8
    int newSeq = (currentSeq + 1) % windowSize;
    
    uint8_t* payload = reinterpret_cast<uint8_t*>(pkt->payloadData); // param_2[1]
    int payloadOffset = newSeq * 0xE0;             // +0x2EC is base of buffer
    uint8_t* bufferEntry = conn->mPacketBuffer + payloadOffset;
    
    // Check if this packet slot is already used (duplicate detection)
    uint8_t slotUsed = FUN_005890e0(reinterpret_cast<int>(bufferEntry), reinterpret_cast<int*>(payload));
    
    // Timer update (decrement 16 timers)
    float deltaTime = conn->mDeltaTime;             // +0x78
    conn->processTimerDecrement(deltaTime);
    conn->mDeltaTime = 0.0f;
    
    int ackSeq;
    if (pkt->ackFlags == -1) {
        ackSeq = pkt->ackSequence;
    } else {
        ackSeq = pkt->ackFlags; // Treat ackFlags as sequence when not -1? Actually code uses param_2[3] then param_2[4]
    }
    
    // Validate packet order
    uint8_t allowed = FUN_00581b30(param_1, ackSeq);
    if (!allowed) {
        return 0;
    }
    
    // Accept packet: update last acknowledged sequence
    conn->mLastAcknowledged = conn->mSomeState;     // +0x2E0 = +0x18
    
    if (pkt->ackFlags == -1) {
        if (pkt->type == 4 || pkt->type == 3) {
            ackSeq = pkt->sequence;                 // param_2[2]
        } else {
            ackSeq = *(int*)(*pkt->objectPtr + 0x18); // *param_2 + 0x18
        }
    } else {
        ackSeq = pkt->ackSequence;
    }
    conn->mSomeState = ackSeq;                     // +0x18
    
    // Get local time stamp
    float localTime = *(float*)&conn->field_0x1c;  // +0x1c (treated as float via FUN_00586a30)
    float time = FUN_00586a30(conn->field_0x1c);   // Convert to float10? Actually returns float10?
    
    // Check if packet is flagged for special handling (bit 0 of +0xB)
    if ((payload[0xB] & 1) != 0) {
        conn->mFlags |= 0x8000000;                 // +0x10
    }
    
    conn->field_0x1c = conn->field_0x24;           // Copy time stamp
    conn->field_0x20 = conn->field_0x24;
    
    if (pkt->isNotDuplicating == 0) {
        // Mark entry as used if not a duplicate
        if (slotUsed) {
            bufferEntry[0x70] = 1;                 // Some flag at offset 0x70 in buffer entry
        }
        conn->mSequence = newSeq;                  // +0x2E8
    }
    
    // Copy packet payload to local buffer (0x14 * 4 = 80 bytes)
    int* src = reinterpret_cast<int*>(payload);
    int* dst = conn->mPayloadCopy;                 // +0x2F4
    for (int i = 0; i < 20; ++i) {
        dst[i] = src[i];
    }
    conn->mPayloadCopyPtr = conn->mPayloadCopy;    // +0x2F0 points to +0x2F4
    
    // Invoke callback if present
    if (conn->mCallback != nullptr) {              // +0x3A4
        (conn->mCallback)(conn->mCallbackData, reinterpret_cast<int*>(payload), time, pkt->type);
    }
    
    // Additional processing if packet type indicates ghost update (bit 5 of +0xB) and sequence > 2 and certain field non-zero
    if ((payload[0xB] & 0x20) != 0 && pkt->sequence > 2 && payload[0xF] != 0) {
        FUN_00586c00(payload[0xF] * 4, param_1, reinterpret_cast<int*>(payload)); // Or pass as int
    }
    
    return 1;
}