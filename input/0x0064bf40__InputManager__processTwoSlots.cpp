// FUNC_NAME: InputManager::processTwoSlots
void InputManager::processTwoSlots(uint32_t slotIndex)
{
    // Next slot index (wraps around via byte cast)
    uint32_t nextSlotIndex = (uint32_t)(uint8_t)((int8_t)slotIndex + 1);

    // Apply operations to the next slot, then to the current slot
    setSlotActive(nextSlotIndex);   // Enable/initialize slot+1
    clearSlotActive(nextSlotIndex); // Disable/finalize slot+1
    setSlotActive(slotIndex);       // Enable/initialize current slot
    clearSlotActive(slotIndex);     // Disable/finalize current slot
}