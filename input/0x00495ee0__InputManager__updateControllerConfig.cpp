// FUNC_NAME: InputManager::updateControllerConfig
void __thiscall InputManager::updateControllerConfig(int thisPtr, int *newConfigObject)
{
    int *oldConfigObject = *(int **)(thisPtr + 4);  // +0x04: current configuration object pointer
    int slotIndex = 0;
    
    if (oldConfigObject == NULL)
    {
        *(int **)(thisPtr + 4) = newConfigObject;
        return;
    }
    
    byte currentSlotByte = *(byte *)(DAT_012233b4 + 0x564);  // gInputState +0x564: current controller slot index
    int controllerStructPtr = 0;
    
    if (currentSlotByte == 0x11)  // Special value: use slot 0 (first structure in array)
    {
        controllerStructPtr = DAT_012233b4 + 0x2c;  // gInputState +0x2c: base of controller slot structures (each 0x44 bytes)
    }
    else
    {
        if (currentSlotByte > 0xf)
        {
            *(int **)(thisPtr + 4) = newConfigObject;  // Invalid slot, just assign and return
            return;
        }
        controllerStructPtr = DAT_012233b4 + 0x2c + (uint)currentSlotByte * 0x44;
    }
    
    if (controllerStructPtr == 0)
    {
        *(int **)(thisPtr + 4) = newConfigObject;
        return;
    }
    
    // Initialize controller slot structure fields (likely analog stick/trigger values)
    *(short *)(controllerStructPtr + 0x10) = 0;  // +0x10: left thumb X
    *(short *)(controllerStructPtr + 0x12) = 0;  // +0x12: left thumb Y
    *(short *)(controllerStructPtr + 0x14) = 0;  // +0x14: right thumb X (or triggers)
    
    // Iterate over all 16 controller slots
    do {
        // Call old config object's per-slot update for slot 'slotIndex'
        (**(code **)(*oldConfigObject + 0xc))(slotIndex);  // virtual method at vtable+0x0C
        int subIndex = 0;
        // Iterate over 30 sub-components (e.g., buttons+dpad+analog)
        do {
            // Call new config object's per-component update for sub-index
            (**(code **)(*newConfigObject + 0xc))(subIndex);
            subIndex++;
        } while (subIndex < 0x1e);
        slotIndex++;
    } while (slotIndex < 0x10);
    
    *(int **)(thisPtr + 4) = newConfigObject;
    return;
}