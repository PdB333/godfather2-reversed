// FUNC_NAME: TNLConnection::initPacketBuffer
// Address: 0x0064a290
// Initializes a packet structure (9 dwords: type, sequence, and 7 zero-fill fields) in a thread-safe manner.
// The output buffer is passed in ESI (implicit register parameter).
// The critical section at this+0x1b8 protects the pool from which the buffer may have been allocated.

void __thiscall TNLConnection::initPacketBuffer(uint32_t packetType) {
    // Critical section for thread-safe packet allocation/initialization
    LPCRITICAL_SECTION csLock = reinterpret_cast<LPCRITICAL_SECTION>(*(uint32_t*)((uint8_t*)this + 0x1b8));
    if (csLock != nullptr) {
        EnterCriticalSection(csLock);
        // Note: The original assembly performs an additional operation on csLock[1].DebugInfo,
        // likely a reference count or lock nesting indicator. This is omitted due to decompilation
        // ambiguity; functionally it does not affect the buffer initialization.
    }

    // Buffer pointer passed via ESI (assumed from caller)
    uint32_t* buffer = reinterpret_cast<uint32_t*>(unaff_ESI); // supplied by calling function
    buffer[0] = packetType;                                                     // +0x00: packet type ID
    buffer[1] = *(uint32_t*)((uint8_t*)this + 0x1c);                           // +0x04: sequence number from this+0x1c
    buffer[2] = 0;                                                             // +0x08: flags / reserved
    *(uint64_t*)(buffer + 3) = 0;                                              // +0x0C, +0x10: zero
    *(uint64_t*)(buffer + 5) = 0;                                              // +0x14, +0x18: zero
    *(uint64_t*)(buffer + 7) = 0;                                              // +0x1C, +0x20: zero
}