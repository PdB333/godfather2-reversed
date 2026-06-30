// FUNC_NAME: NetSession::update
// Reconstructed C++ for function at 0x006f2890 (NetSession::update)
// Handles session update logic, including packet processing and GUID-based routing.

class NetSession {
public:
    // Offsets in heap object:
    // +0x00: vtable
    // +0x50: flags (uint32) - bit7 = pending? bit0 = something
    // +0x54: sequenceCounter (uint32)
    // +0x90: pPacketBuffer (void*)
    // +0xCC: pAdditionalData (void*) - for non-null GUID
    // +0xDC: guid[4] (uint32[4]) - 128-bit identifier
    // +0xF1: byte - flag to skip processing

    void __thiscall update() {
        uint32 flags = *(uint32*)((int)this + 0x50);
        char skipByte = *(char*)((int)this + 0xF1);

        // Early exit if processing is already flagged and not skipping
        if (((flags & 0x80) != 0) && (skipByte != 0)) {
            return;
        }

        // Lock mutex (global or per-object? using static data at LAB_006f19d0)
        lockMutex(&g_sessionMutex, this);

        uint32 someParam = 0;
        uint32 seq = *(uint32*)((int)this + 0x54);
        if (seq > 6) {
            someParam = 4;
        }

        // Check if we can process more (resource check)
        if (isProcessingAvailable(someParam) == false) {
            // Fall through
        } else {
            uint32* guid = (uint32*)((int)this + 0xDC);
            // GUID is 128 bits stored as four uint32
            // Check for null or specific magic GUID
            if ((guid[0] == 0xBBDBBBBA && guid[1] == 0xBEEFBEEF && guid[2] == 0xEAC15A55 && guid[3] == 0x91100911) ||
                (guid[0] == 0 && guid[1] == 0 && guid[2] == 0 && guid[3] == 0)) {
                // Null or magic GUID -> use simple key
                uint64 key = make64bitKey(seq, flags);
                uint32 keyHigh = (uint32)(key >> 32);
                uint32 keyLow = (uint32)(key);
                char tempGuid[16]; // not used in this path? Or filled by function
                bool result = processPacketWithoutGuid((void*)((int)this + 0x90), tempGuid, keyHigh, keyLow);
                if (result) {
                    *(char*)((int)this + 0xF1) = 1;
                    unlockMutex(&g_sessionMutex);
                    return;
                }
            } else {
                // Non-null GUID -> use additional data
                if (isConnectionValid() != false) {
                    uint64 key = make64bitKey(seq, flags);
                    uint32 keyHigh = (uint32)(key >> 32);
                    uint32 keyLow = (uint32)(key);
                    void* pAdditional = (void*)((int)this + 0xCC);
                    char tempGuid[16];
                    bool result = processPacketWithGuid((void*)((int)this + 0x90), tempGuid, keyHigh, pAdditional, keyLow);
                    if (result) {
                        *(char*)((int)this + 0xF1) = 1;
                        unlockMutex(&g_sessionMutex);
                        return;
                    }
                }
            }
        }

        // Fallback processing
        if ((*(uint8*)((int)this + 0x50) & 1) != 0) {
            handleFlagEvent();
        }

        // Call virtual method at vtable offset 0x2c (onFrameUpdate)
        (this->*vtable_onFrameUpdate)();

        unlockMutex(&g_sessionMutex);
    }

private:
    // Forward declarations of called functions (inlined for clarity)
    void lockMutex(void* mutex, NetSession* session);
    void unlockMutex(void* mutex);
    bool isProcessingAvailable(uint32 param);
    bool isConnectionValid();
    uint64 make64bitKey(uint32 low, uint32 high);
    bool processPacketWithoutGuid(void* buffer, char* tempGuid, uint32 keyHigh, uint32 keyLow);
    bool processPacketWithGuid(void* buffer, char* tempGuid, uint32 keyHigh, void* additionalData, uint32 keyLow);
    void handleFlagEvent();
    typedef void (__thiscall *VFunc)(void);
    static constexpr int VTBL_OFFSET_ONFRAME = 0x2c;
    VFunc vtable_onFrameUpdate; // Actually obtained from vtable, but kept as concept

    // Static global mutex data (reference to LAB_006f19d0)
    static void* g_sessionMutex;
};

// Static member definition
void* NetSession::g_sessionMutex = (void*)0x006f19d0; // Placeholder