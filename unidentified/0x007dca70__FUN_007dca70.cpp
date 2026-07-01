// FUNC_NAME: SomeClass::tryConsumeResource
bool __thiscall SomeClass::tryConsumeResource(int thisPtr, int resourceId)
{
    char cVar1;
    bool bResult;
    
    bResult = *(char *)(thisPtr + 0x152) == '\0';  // +0x152: resourceCount (or similar)
    if (!bResult) {
        if (*(char *)(thisPtr + 0x154) == '\0') {  // +0x154: isProcessing flag
            *(undefined1 *)(thisPtr + 0x154) = 1;  // Set processing flag
            cVar1 = FUN_007dc3b0(resourceId);       // Try to consume resource
            if (cVar1 == '\0') {                     // Failed to consume
                *(char *)(thisPtr + 0x152) = *(char *)(thisPtr + 0x152) + -1;  // Decrement resource count
                *(char *)(thisPtr + 0x150) = *(char *)(thisPtr + 0x150) + '\x01';  // +0x150: failCounter
                if (2 < *(byte *)(thisPtr + 0x150)) {  // Clamp failCounter to 0-2
                    *(undefined1 *)(thisPtr + 0x150) = 0;
                }
            }
            *(undefined1 *)(thisPtr + 0x154) = 0;  // Clear processing flag
        }
        bResult = *(char *)(thisPtr + 0x152) == '\0';  // Re-check resource count
    }
    return !bResult;  // Returns true if resources remain
}