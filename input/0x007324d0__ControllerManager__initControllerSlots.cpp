// FUNC_NAME: ControllerManager::initControllerSlots
void __thiscall ControllerManager::initControllerSlots(int this)
{
    // Initialize 16 controller slots, each 12 bytes (three int32 fields)
    // Slot structure: [mId=0, mFlags=0, mDefaultValue=global]
    int defaultValue = DAT_00d5ccf8; // Global default value (likely 0 or -1)
    
    // Loop 16 times (iVar3 = 0xF downto 0)
    int slotIndex = 0xF;
    int* slotPtr = (int*)(this + 8); // Start at offset 8? Actually loop writes to offsets 0,4,8 then 12,16,20...
    do {
        slotPtr[-2] = 0; // offset 0 (or 12k)
        slotPtr[-1] = 0; // offset 4 (or 12k+4)
        *slotPtr = defaultValue; // offset 8 (or 12k+8)
        slotPtr += 3; // Advance 12 bytes
        slotIndex--;
    } while (slotIndex >= 0);
    
    // Set field at offset 0xC0 to 0 (likely a count or active mask)
    *(int*)(this + 0xC0) = 0;
}