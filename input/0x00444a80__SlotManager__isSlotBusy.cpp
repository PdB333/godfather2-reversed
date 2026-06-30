// FUNC_NAME: SlotManager::isSlotBusy
bool __thiscall SlotManager::isSlotBusy(unsigned int slotIndex) const {
    // +0x14: array of 16 elements, each 0x18 bytes (SlotElement)
    // +8 within element: flags byte, bit 2 (0x4) indicates occupied/active
    if (slotIndex >= 0x10)
        return true; // out of range → treat as busy

    // Compute pointer to the slot element
    SlotElement* elem = reinterpret_cast<SlotElement*>(this + 0x14 + slotIndex * 0x18);
    if (elem == nullptr)
        return true; // null pointer → busy

    // Check if the slot is actually in use (bit 2 set)
    if ((*(unsigned char*)(elem + 8) & 4) != 0)
        return true; // flag set → occupied

    return false; // slot is free
}