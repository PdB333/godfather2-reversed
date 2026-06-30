// FUNC_NAME: InputManager::initializeControllerSlots
void InputManager::initializeControllerSlots(void)
{
    // in_EAX points to the InputManager instance (this)
    InputManager* thisPtr = (InputManager*)in_EAX;
    int* pSlotIndex;
    int slotCount;
    int i;
    
    // Store global pointer to this InputManager instance
    // +0x0: vtable pointer (PTR_FUN_00e3edcc)
    gInputManager = thisPtr;
    thisPtr->vtable = &PTR_FUN_00e3edcc;
    
    // Initialize 0xBF (191) controller slots? Actually 0xC0 (192) slots
    // Each slot is 0x35 * 4 = 0xD4 bytes (212 bytes)
    // Starting from offset +0x18 (6 dwords from start)
    slotCount = 0xbf;
    uint* pSlot = (uint*)(thisPtr + 6);  // +0x18 offset
    
    i = 0;
    do {
        // Clear slot data structure (0x35 dwords = 0xD4 bytes)
        pSlot[-4] = 0;   // +0x08
        pSlot[1] = 0;    // +0x1C
        pSlot[-1] = 0;   // +0x14
        *pSlot = 0;      // +0x18
        pSlot[4] = 0;    // +0x28
        pSlot[2] = 0;    // +0x20
        pSlot[3] = 0;    // +0x24
        pSlot[5] = 0xffffffff;  // +0x2C, set to -1 (unused)
        *(byte*)(pSlot + 6) = 0;  // +0x30
        pSlot[7] = 0;    // +0x34
        pSlot[0x28] = 0; // +0xA0
        pSlot[0x29] = 0; // +0xA4
        pSlot[0x2a] = 0; // +0xA8
        pSlot[0x2d] = 0; // +0xB4
        pSlot[0x2b] = 0; // +0xAC
        pSlot[0x2c] = 0; // +0xB0
        pSlot[0x2e] = 0; // +0xB8
        pSlot[0x2f] = 0; // +0xBC
        *(byte*)(pSlot + 0x18) = 0; // +0x60
        *(byte*)(pSlot + 8) = 0;     // +0x38
        pSlot += 0x35;  // Move to next slot (0x35 dwords = 0xD4 bytes)
        slotCount--;
    } while (slotCount >= 0);
    
    // Initialize slot indices (0 to 0xBF)
    pSlotIndex = (int*)(thisPtr + 1);  // +0x04
    i = 0;
    do {
        *pSlotIndex = i;
        i++;
        pSlotIndex += 0x35;  // Each slot is 0x35 dwords apart
    } while (i < 0xc0);  // 192 slots total
    
    // Set up function pointers for controller management
    // These are likely callbacks for different controller operations
    gControllerFunc1 = &LAB_005d15b0;  // Some initialization function
    gControllerFunc2 = &LAB_005d1570;  // Update function
    gControllerFunc3 = &DAT_005d15a0;  // Data pointer
    gControllerFunc4 = &LAB_005d1630;  // Shutdown function
    
    return;
}