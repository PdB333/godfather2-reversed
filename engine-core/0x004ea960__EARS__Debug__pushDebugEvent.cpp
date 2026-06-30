// FUNC_NAME: EARS::Debug::pushDebugEvent
void EARS::Debug::pushDebugEvent(void* thisPtr)
{
    // Get thread-local data pointer from FS segment (TEB + 0x2c)
    int* threadLocalData = *(int**)(*(int**)__readfsdword(0x2c) + 0x34);
    int isMultiplayer = (threadLocalData != 0) ? 1 : 0;

    // Compute offset into this object: +4 for single player, +0x9c for multiplayer
    int* eventData = (int*)((uint)isMultiplayer * 0x98 + 4 + (int)thisPtr);

    // Copy event data: eventData[0] = eventData[1]
    *eventData = eventData[1];
    if (eventData[1] > 0) {
        // Copy two 8-byte values from offset 0x88 and 0x90 to offset 8 and 16
        *(long long*)(eventData + 2) = *(long long*)(eventData + 0x22);
        *(long long*)(eventData + 4) = *(long long*)(eventData + 0x24);
    }
    eventData[1] = -1; // Mark as processed

    // Select global debug log buffer based on mode
    int* logBuffer = (isMultiplayer != 0) ? g_debugLogBuffer2 : g_debugLogBuffer1;

    // Push event marker and flag onto log stack (stack pointer at logBuffer+0x14)
    int** stackPtr = (int**)(logBuffer + 0x14);
    int* currentTop = *stackPtr;
    *currentTop = (int)&DEBUG_EVENT_MARKER; // Write marker address
    currentTop++;
    *stackPtr = currentTop;
    *currentTop = isMultiplayer; // Write flag
    currentTop++;
    *stackPtr = currentTop;
}