// FUNC_NAME: NetSession::handleMessage

// Function address: 0x009084c0
// Role: Handles an incoming message buffer. Reads a 4-byte command ID from the buffer,
// stores it in the object's field at +0x88, and if the command ID is 1 and there is
// additional data, delegates processing to a global singleton's virtual method at vtable+0x3c.
// Returns 1 (success) unconditionally.

extern void* DAT_012234e0; // Global singleton (likely StreamManager or NetSession)

int __thiscall NetSession::handleMessage(
    void* thisPtr,
    uint32_t senderId,           // unused parameter
    const uint32_t* dataBuffer,  // buffer containing message data
    uint32_t dataSize            // size of the buffer in bytes
)
{
    int32_t commandId;

    // Default command ID: 2 (unknown/invalid)
    *(int32_t*)((uint8_t*)thisPtr + 0x88) = 2;  // +0x88: m_currentCommand

    if (dataSize > 3) {
        // First 4 bytes are the command ID
        commandId = *dataBuffer;
        *(int32_t*)((uint8_t*)thisPtr + 0x88) = commandId;

        // Command 1 indicates a special message that requires further processing
        if ((commandId == 1) && (dataSize > 4)) {
            // The global singleton (e.g., g_streamManager) handles the payload
            // The virtual function at vtable offset 0x3c (index 15) is called
            // with the remaining data after the command ID.
            void* globalObj = *(void**)DAT_012234e0; // dereference global pointer
            void (*handlerFunc)(void*, const void*, uint32_t) =
                *(void (__thiscall**)(void*, const void*, uint32_t))((uint32_t)globalObj + 0x3c);

            handlerFunc(globalObj, dataBuffer + 1, dataSize - 4);
        }
    }

    return 1; // Always success
}