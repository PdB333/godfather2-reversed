// FUNC_NAME: DeviceManager::readSlot
uint DeviceManager::readSlot(int deviceIndex, uint inputFlags) {
    // Index into global device table (0x011eb8f4), each entry 0x10 bytes
    DeviceEntry* entry = &gDeviceTable[deviceIndex * 0x10]; // Actually param_1 * 0x10 added to base
    // But the decompiled code does: &DAT_011eb8f4 + param_1 * 0x10, so entry = base + deviceIndex * 0x10
    // First dword at entry is a pointer to a device object with vtable
    void* deviceObj = *(void**)entry;

    // Virtual call at vtable+0x24: getNumSlots() or getSlotCount()
    uint slotCount = (*(uint(__thiscall**)(void*, int))(*(uint*)deviceObj + 0x24))(deviceObj, 0);
    if (slotCount == 0) {
        return 0;
    }

    // Variables to receive slot data (stack locals &0xffffffbc and &0xffffffb8)
    uint slotData1, slotData2;
    // Virtual call at vtable+0x18: getSlotData(slotIndex, &slotData1, &slotData2)
    int result = (*(int(__thiscall**)(void*, uint, uint*, uint*))(*(uint*)deviceObj + 0x18))(deviceObj, slotCount, &slotData1, &slotData2);
    if (result != 0) {
        return 0;
    }

    // unaff_EBX likely contains a mode/type from calling context (maybe a global state or register param)
    // If mode is not 1 (left? ) and not 2 (right? ), return a packed result
    if (gDeviceMode != 1 && gDeviceMode != 2) {
        // Build result: high bit from gDeviceFlags[deviceIndex] ? 0x80000000 : 0, then OR with (1 << 8) from some SI register (unaff_SI) and low byte from inputFlags
        // unaff_SI is another register variable (maybe byte from calling context)
        uint lowPart = ((uint)gInputMode << 8) | 1; // unaff_SI << 8 | 1
        uint highPart = (gDeviceFlags[deviceIndex] != 0) ? 0x80000000 : 0;
        return (lowPart << 8) | highPart | inputFlags;
    }

    // For mode 1 or 2, return slot count
    return slotCount;
}