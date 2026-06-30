// FUNC_NAME: InputDeviceManager::handleDeviceMessage
void __thiscall InputDeviceManager::handleDeviceMessage(void* thisPtr, int* msg)
{
    // msg points to a message type identifier (e.g., device connect/disconnect)
    if (*msg == g_msgDeviceDisconnect) { // DAT_012067dc
        // Call base class vtable method at offset 0x248 (via adjusted this)
        // Base subobject at thisPtr - 0x3c
        (**(code **)(*(int *)((char*)thisPtr - 0x3c) + 0x248))();
    }

    // Process the message further (likely base class method)
    FUN_00542aa0(msg);

    if (*msg == g_msgDeviceConnect) { // DAT_0120e93c
        if (*(int*)((char*)thisPtr + 0x444) != 0) {
            // Process 4 slots at offset 0x900, each 0x30 bytes (48 bytes)
            for (int i = 0; i < 4; i++) {
                int* slotData = (int*)((char*)thisPtr + 0x900 + i * 0x30);
                if (*(int*)((char*)thisPtr + 0x1dc) != 0) {
                    FUN_00572c50(slotData);
                }
            }
        }

        uint defaultState = DAT_00e2b1a4; // Some global default state pointer or value
        uint zero = 0;
        *(int*)((char*)thisPtr + 0x444) = 0;

        // Pointer to array of 4 flags (each 4 bytes) at offset 0x368
        int* flags = (int*)((char*)thisPtr + 0x368);
        // Pointer to array of 4 controller slots (each 48 bytes) at offset 0x388
        // This pointer points to the second int (offset +4) of each slot
        int* slotPtr = (int*)((char*)thisPtr + 0x388);

        for (int i = 0; i < 4; i++) {
            if ((*flags & 2) == 0) { // Check bit 1 (uninitialized? )
                // Zero out the entire 48-byte slot structure
                slotPtr[-1] = 0; // field0 (offset -4)
                slotPtr[0]  = 0; // field1 (offset  0)
                slotPtr[1]  = 0; // field2 (offset  4)
                slotPtr[2]  = defaultState; // field3 (offset  8)
                slotPtr[3]  = 0;
                slotPtr[4]  = 0;
                slotPtr[5]  = 0;
                slotPtr[6]  = 0;
                slotPtr[7]  = 0;
                slotPtr[8]  = 0;
                slotPtr[9]  = 0;
                slotPtr[10] = 0;

                bool bResetRequired = (*(int*)((char*)thisPtr + 0x1dc) != 0);
                if (bResetRequired) {
                    FUN_00572ac0(); // Reset associated hardware?
                }
                *(uint*)((char*)thisPtr + 0x444) = (uint)bResetRequired;
            }
            flags++;
            slotPtr += 12; // Move to next slot (12 ints = 48 bytes)
        }
    }
}