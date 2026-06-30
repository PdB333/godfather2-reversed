// FUNC_NAME: InputDeviceManager::findActiveDevice
// Address: 0x007057c0
// Role: Iterates through a static array of device slot indices and returns a pointer to the first active device that is not in a disabled state.
// The device base is obtained by subtracting 0x48 from the pointer stored in the device info array at this+0x18.
int __thiscall InputDeviceManager::findActiveDevice(void* this) {
    int iVar2;  // Pointer to device info entry
    int iVar1;  // Pointer to base device object
    uint uVar4; // Loop index into g_deviceIndexMap

    uVar4 = 0;
    do {
        // Read index from static map at g_deviceIndexMap[uVar4] (each entry is 4 bytes)
        int index = *(int*)((int)&g_deviceIndexMap + uVar4);
        // Offset into device info array (each element is 0x14 bytes)
        iVar2 = *(int*)((int)this + 0x18 + index * 0x14);

        if (iVar2 != 0) {
            iVar1 = iVar2 - 0x48; // Get base device object from info pointer
            if (iVar1 != 0) {
                // Check if device is marked as enabled (byte at +0x160)
                if (*(char*)(iVar2 + 0x160) != '\x01') {
                    return iVar1;
                }
                // If enabled, perform additional validation
                char cVar3 = FUN_00701ed0(); // Possibly check device state
                if (cVar3 != '\0') {
                    return iVar1;
                }
            }
        }
        uVar4 += 4;
        if (0x27 < uVar4) {
            return 0;
        }
    } while (true);
}