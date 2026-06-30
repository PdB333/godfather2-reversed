// FUNC_NAME: TNLConnection::processIncomingSequence
void __thiscall TNLConnection::processIncomingSequence(TNLConnection* this) {
    uint currentSequence = *(uint*)((char*)this + 0x68);
    uint expectedSequence = *(uint*)((char*)this + 0x58);
    uint windowSize = *(uint*)((char*)this + 0x6c);
    uint typeId = *(uint*)((char*)this + 0x40);
    void* callback = *(void**)((char*)this + 0x78);
    uint triggerCount = *(uint*)((char*)this + 0x64); // offset 100 = 0x64

    if (currentSequence < expectedSequence) {
        currentSequence++;
        *(uint*)((char*)this + 0x68) = currentSequence;

        // Check if we exceeded the receive window
        if (windowSize < currentSequence) {
            FUN_008c7890(*(undefined4*)((char*)this + 0x40), 1); // notify with type
        }

        // Invoke callback handler if set
        if (callback != 0) {
            FUN_006b4b50(); // likely callback call
        }

        // Prepare logging structure
        struct LogContext {
            char* format;   // pointer to format string
            int padding;    // likely unused
            int level;      // log level
            char pad;       // alignment
            // ...
        };
        LogContext logCtx;
        logCtx.format = &PTR_LAB_00d5dbb0; // global debug format string
        logCtx.level = DAT_0112a5a4;        // debug level constant
        logCtx.pad = 0;

        // Call logging function
        FUN_00408a00(&logCtx, 0); // log message

        // Specific type check for a known packet type (e.g., GHOST_PACKET)
        if (typeId == 0x637b907) {
            // Check if we reached the trigger count
            if (currentSequence == triggerCount) {
                FUN_00894c90(0x59e83a3b); // fire global event
            }
        }
    }
}