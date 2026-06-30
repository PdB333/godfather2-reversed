// FUNC_NAME: TNLConnection::sendPacket
void __thiscall TNLConnection::sendPacket(int initMode, void* payload, int hasSequence, uint channelIndex, uint dataSize)
{
    // this is in ESI, payload in EDI (param_2)
    // Offset 0x10 (dword) - pointer to reference-counted payload (likely PacketData)
    void** ppCurrentPayload = (void**)((char*)this + 0x40); // +0x10*4
    void* pCurrent = *ppCurrentPayload;
    void* pNew = payload;

    // Reference counting: release old, retain new
    if (pCurrent != pNew) {
        if (pCurrent != NULL && *(short*)((char*)pCurrent + 4) != 0) { // offset +4: ref count
            // Decrement ref count at offset +6
            short* refCount = (short*)((char*)pCurrent + 6);
            *refCount = *refCount - 1;
            if (*refCount == 0) {
                // Destroy/release payload
                (**(void (__stdcall **)(int))pCurrent)(1); // vtable[0] with arg 1
            }
        }
        *ppCurrentPayload = pNew;
        if (pNew != NULL && *(short*)((char*)pNew + 4) != 0) {
            short* refCount = (short*)((char*)pNew + 6);
            *refCount = *refCount + 1;
        }
    }

    // Offset 0x11 (dword) - store hasSequence
    *(int*)((char*)this + 0x44) = hasSequence;

    // Initialize fields based on initMode
    if (initMode == 0) {
        // New allocation
        allocatePacketMemory(); // FUN_0045cbe0
        // Set default values from global DAT_00e2b1a4 (likely some base structure)
        int* base = (int*)0x00e2b1a4;
        *(int*)((char*)this + 0x00) = *base;       // offset 0
        *(int*)((char*)this + 0x14) = *base;       // offset 5*4 = 0x14
        *(int*)((char*)this + 0x28) = *base;       // offset 10*4 = 0x28
        *(int*)((char*)this + 0x3C) = 0;           // offset 0xF*4 = 0x3C
        *(int*)((char*)this + 0x38) = 0;           // offset 0xE*4 = 0x38
        *(int*)((char*)this + 0x34) = 0;           // offset 0xD*4 = 0x34
        *(int*)((char*)this + 0x30) = 0;           // offset 0xC*4 = 0x30
    } else {
        // Reuse existing packet
        releasePacket((void*)((char*)initMode + 0xE0)); // FUN_005420c0, initMode used as base pointer
        if (hasSequence != 0) {
            initPacketPayload(initMode);       // FUN_00556fd0
            setPayloadRefCount(this, payload); // FUN_00556f70
        }
    }

    // Generate sequence/time value
    uint sequenceValue = 0;
    if (hasSequence != 0) {
        sequenceValue = getNextSequence(); // FUN_0043b490 - likely returns a timestamp or sequence
    }

    // Build 64-bit header at offset 0x13 (dword index) -> actual byte offset 0x4C
    uint32_t headerLow = (sequenceValue & 0xfff) << 0x10 | (channelIndex & 0x1f);
    headerLow |= 0x3e0; // Set bits 9-5

    // Upper 32 bits from a global structure indexed by channelIndex
    // DAT_01223480 + 0x54 points to a table; +0x34 + channelIndex*4 is uint32
    int* globalBase = (int*)0x01223480;
    uint32_t* tablePtr = (uint32_t*)(*(int*)((char*)globalBase + 0x54) + 0x34);
    uint32_t headerHigh = tablePtr[channelIndex];

    *(uint64_t*)((char*)this + 0x4C) = ((uint64_t)headerHigh << 32) | headerLow;

    // Store dataSize at offset 0x15 (dword index) -> byte offset 0x54
    *(uint64_t*)((char*)this + 0x54) = (uint64_t)dataSize;

    // Zero at offset 0x17 -> byte offset 0x5C
    *(int*)((char*)this + 0x5C) = 0;
}