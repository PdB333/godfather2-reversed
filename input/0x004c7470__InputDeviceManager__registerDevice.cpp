// FUNC_NAME: InputDeviceManager::registerDevice
// Function address: 0x004c7470
// Registers a device object into a global device table.
// param_1 (ECX): pointer to device object (this)
// in_EAX (EDX): device index/ID
void __fastcall InputDeviceManager::registerDevice(void* deviceObject, int deviceIndex)
{
    // Clear global flag
    gDeviceRegistered = 0;

    // Device info structure passed to virtual function
    struct DeviceInfo {
        int type;       // +0x00
        int someField;  // +0x04
        int another;    // +0x08
    } info = {2, 0x10, 0};

    // Store current device object and index globally
    gCurrentDeviceObject = deviceObject;
    gCurrentDeviceIndex = deviceIndex;

    // Call virtual function (likely allocate/init) with (deviceIndex*8, &info)
    gDeviceHandle = (*(int (__thiscall**)(void*, int, DeviceInfo*))(*((int*)deviceObject) + 0))(deviceObject, deviceIndex * 8, &info);

    // Search for an empty slot in the global device table (12-byte entries)
    int slotIndex = 0;
    char* entryPtr = (char*)gDeviceTable;
    while (entryPtr < (char*)gDeviceTable + MAX_DEVICE_SLOTS * 12)
    {
        if (*entryPtr == '\0') // Empty slot found
        {
            // Fill slot with device constants
            *(int*)(gDeviceTableField4 + slotIndex * 12) = DEVICE_CONSTANT_1; // 0x00e446dc
            *(int*)(gDeviceTableField8 + slotIndex * 12) = DEVICE_CONSTANT_2; // 0x00e2b1a4
            *(char*)(gDeviceTable + slotIndex * 12) = 1; // Mark as used
            gDeviceSlotIndex = slotIndex;
            return;
        }
        entryPtr += 12;
        slotIndex++;
    }

    // No empty slot found
    gDeviceSlotIndex = -1;
}