// FUNC_NAME: GameManager::lockedExecute
void __thiscall GameManager::lockedExecute(int thisPtr, undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5)
{
    // Check if the initialization flag at offset 0x249c bit 5 (0x20) is not set
    if ((*(uint *)(thisPtr + 0x249c) >> 5 & 1) == 0) {
        // If not initialized, call global initialization routine (likely critical section or manager init)
        FUN_0093c210();
    }
    // Set the bit to mark as initialized / locked
    *(uint *)(thisPtr + 0x249c) = *(uint *)(thisPtr + 0x249c) | 0x20;
    // Debug/logging call (0 might indicate a specific debug channel)
    FUN_00849d50(0);
    // Primary execution function with forwarded parameters
    FUN_007dc1a0(thisPtr, param2, param3, param4, param5);
    // Post-execution cleanup or finalization
    FUN_0079e330();
    return;
}