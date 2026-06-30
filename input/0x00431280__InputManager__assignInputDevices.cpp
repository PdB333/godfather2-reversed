// FUNC_NAME: InputManager::assignInputDevices
void assignInputDevices(int* outDevice1, int* outDevice2, int* outDevice3)
{
    // Start of array of slot structures (size 0x210 bytes each)
    char* slotFlags = &DAT_01163841;
    // Pointer to list of device object pointers (starting at 0x30 offset from global base)
    int* devicePtrList = (int*)(DAT_012233b0 + 0x30);

    // Loop over exactly 3 slots (from 0x1163841 to 0x1163e71 = 0x630 = 3 * 0x210)
    for (int slot = 0; slot < 3; slot++)
    {
        int currentDevice = *devicePtrList;
        if (currentDevice != 0)
        {
            // Check device type at offset +0x20 (1 = gamepad/controller?)
            if (*(int*)(currentDevice + 0x20) == 1)
            {
                // slotFlags[0] indicates if this slot is already taken
                if (*slotFlags == '\0')
                {
                    *outDevice1 = currentDevice;
                }
                else
                {
                    *outDevice2 = currentDevice;
                }
            }
            else
            {
                // For non-controller devices (e.g., keyboard)
                // Get base pointer from thread-local storage (FS:[0x2c])
                int tlsBase = *(int*)(__readfsdword(0x2c));
                int globalPtr = *(int*)(tlsBase + 8); // +8 offset to global singleton

                int deviceSubType = *(int*)(currentDevice + 0x18); // +0x18 subtype identifier
                // Pointer to a 16-byte metadata block (e.g., input mapping)
                unsigned int* metaData = (unsigned int*)(globalPtr + 0x30 + deviceSubType);
                // Copy 16 bytes of metadata into local struct
                struct {
                    unsigned int data[4];
                } localMeta;
                localMeta.data[0] = metaData[0];
                localMeta.data[1] = metaData[1];
                localMeta.data[2] = metaData[2];
                localMeta.data[3] = metaData[3]; // Actually only first 3 copied? The decompiled shows 3 assignments, then another at +0x70 separately.
                // Actually uStack_14 = *(undefined4 *)(iVar2 + iVar3 + 0x70); That's a separate read, not part of the first 16 bytes.

                *outDevice3 = currentDevice;
                unsigned int extraFlag = *(unsigned int*)(globalPtr + deviceSubType + 0x70); // +0x70 extra flag

                // Call a function that checks the metadata (returns 2 if special condition)
                int result = FUN_004bdae0(&localMeta);
                if (result == 2)
                {
                    *outDevice3 = 0; // Clear assignment
                }
            }
        }
        // Advance to next slot: slotFlags increments by 0x210, devicePtrList by 1 (int pointer)
        slotFlags += 0x210;
        devicePtrList++;
    }
}