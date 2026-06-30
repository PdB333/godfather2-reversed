// FUNC_NAME: setInputState
// Function: 0x0042b480
// Role: Sets a 16-bit input state value for a given slot index and logs the event to a replay buffer if not in playback mode.
void setInputState(int slot, short value)
{
    // Get thread-local input context pointer (FS:[0x2c] -> TLS, then deref for base)
    int* pTlsBase = *(int**)(*(int**)(__readfsdword(0x2c)) + 0x2c);
    // Base pointer for input state array (offset +0x0c)
    int* pInputStateBase = *(int**)pTlsBase; // actually **(int**)(unaff_FS_OFFSET + 0x2c)

    // Get a flag/mode from offset 0x34 of the same base
    int replayMode = *(int*)(pInputStateBase + 0x34 / 4); // offset 0x34
    // Write the 16-bit value into the array at offset 0x0c, indexed by slot
    *(short*)((char*)pInputStateBase + 0x0c + slot * 2) = value;

    // If not in replay mode (replayMode != 1), log the event to the replay buffer
    if (replayMode != 1) {
        // Global replay buffer pointer at DAT_01206880
        // Buffer structure: at +0x14 is a pointer to a growing allocation
        uint** ppBufPtr = (uint**)(DAT_01206880 + 0x14);
        // Write a vtable pointer (PTR_LAB_0110b810) into the current allocation
        **(uint**)(*ppBufPtr) = (uint)&PTR_LAB_0110b810;
        *ppBufPtr = (uint*)((uint)*ppBufPtr + 4); // advance by 4 bytes
        // Align to next 4-byte boundary
        *ppBufPtr = (uint*)((uint)*ppBufPtr & 0xfffffffc);
        // Store slot (param_1) and value (param_2) as a compact event
        **(int**)(*ppBufPtr) = slot; // store slot
        *ppBufPtr = (uint*)((uint)*ppBufPtr + 4);
        // Store 16-bit value, then advance with alignment to 4
        *(short*)(*ppBufPtr) = value;
        *ppBufPtr = (uint*)(((uint)*ppBufPtr + 5) & 0xfffffffc);
    }
    return;
}