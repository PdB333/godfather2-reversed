// FUNC_NAME: handleDebugOverlayToggle
void handleDebugOverlayToggle(int param_1) // param_1: 0 = disable, nonzero = enable
{
    // Check if the debug overlay system has been initialized by examining a thread-local storage flag.
    // FS:0x2C points to the Thread Information Block (TIB), and offset +0x34 is typically a thread-specific flag.
    int* tibBase = *reinterpret_cast<int**>(__readfsdword(0x2C));
    int* initializationFlag = reinterpret_cast<int*>(*tibBase + 0x34);

    if (*initializationFlag == 0) {
        // System not yet initialized: create a callback entry.
        // DAT_01206880 is a global pointer; +0x14 points to a storage area for callback data.
        int** storagePtr = reinterpret_cast<int**>(DAT_01206880 + 0x14);
        // Store the vtable pointer for the callback handler.
        **storagePtr = reinterpret_cast<int>(&PTR_LAB_0110b860);
        // Advance the pointer by 4 bytes (size of one entry).
        *storagePtr = *storagePtr + 1;
        // Write the parameter as the callback data.
        **storagePtr = param_1;
        *storagePtr = *storagePtr + 1;
        return;
    }

    // System is initialized; toggle a flag in the player state structure.
    // DAT_012233a8 points to a global manager; +4 gives a base pointer.
    int* managerBase = *reinterpret_cast<int*>(DAT_012233a8 + 4);
    // Offset 0x3AF8 is a bitfield; bit 4 controls debug overlay visibility.
    uint* flagField = reinterpret_cast<uint*>(managerBase + 0x3AF8);
    if (param_1 != 0) {
        // Enable: set bit 4.
        *flagField |= 0x10;
    } else {
        // Disable: clear bit 4.
        *flagField &= ~0x10;
    }
}