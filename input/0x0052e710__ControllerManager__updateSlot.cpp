// FUNC_NAME: ControllerManager::updateSlot
void __fastcall ControllerManager::updateSlot(ControllerManager *this, uint slotIndex)
{
    // Check if slot index is within the 32-slot maximum
    if (slotIndex < 32) {
        // The device struct array is at base 0x01219390, each entry 0x18 bytes
        // Offsets: +0x4 = flags (uint), +0xC = device value (int)
        uint *deviceFlags = (uint *)((int)&deviceArray + slotIndex * 0x18 + 4);
        int *deviceValue = (int *)((int)&deviceArray + slotIndex * 0x18 + 0xC);
        
        // Check if the device has the connected/active flag (bit 24 = 0x1000000)
        if (*deviceFlags & 0x1000000) {
            // Mark slot as active and store the device's value
            activeSlotFlags[slotIndex] = 1;      // DAT_01219808
            activeSlotValues[slotIndex] = *deviceValue; // DAT_01219788
        } else {
            // Device not connected/active, clear slot
            activeSlotFlags[slotIndex] = 0;
            activeSlotValues[slotIndex] = 0;
        }
    }
    // Update internal state after slot changes
    update(); // FUN_0052e2e0
}