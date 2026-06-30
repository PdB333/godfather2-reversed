// FUN_00415370: NetConnection::processFlagsMessage
void __thiscall NetConnection::processFlagsMessage(uint32_t messageId, uint64_t* messageData) {
    // Check for the specific message identifier (hash of "SetFlags" or similar)
    if (messageId != 0x20e5862) {
        return;
    }
    if (messageData == nullptr) {
        return;
    }

    uint64_t value = *messageData;
    uint32_t curFlags = *(uint32_t*)(this + 0x2C); // mFlags
    uint32_t highPart = (uint32_t)(value >> 32);
    uint32_t lowPart = (uint32_t)(value);
    
    // byte at offset 8 indicates whether to apply a mask
    if (*(char*)(messageData + 1) == '\0') { // messageData+1 skips 8 bytes
        uint32_t mask = *(uint32_t*)(this + 0x28); // mFlagsMask
        lowPart = lowPart & mask;
        highPart = highPart & mask;
    }
    
    // Update flags: set bits from lowPart, clear bits from highPart
    uint32_t newFlags = (curFlags | lowPart) & ~highPart;
    *(uint32_t*)(this + 0x2C) = newFlags;
    
    if (curFlags != newFlags) {
        void* delegate = *(void**)(this + 0x20); // mDelegate (e.g., a callback handler)
        if (delegate != nullptr) {
            uint32_t timestamp = getTickCount(); // FUN_004151d0
            *(uint32_t*)((char*)delegate + 0x84) = timestamp; // mLastFlagsChangeTime
        }
    }
}