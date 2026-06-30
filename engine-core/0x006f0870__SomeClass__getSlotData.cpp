// FUNC_NAME: SomeClass::getSlotData
void __thiscall SomeClass::getSlotData(int *outSlot, uint slotIndex) {
    // Check if the slots array (at +0x64) is valid and index is within bounds
    if ((m_slotsArray != NULL) && (outSlot != NULL) && (slotIndex < 5)) {
        // Each slot is 0x2c bytes; calculate pointer to the slot
        *outSlot = (int)((byte*)m_slotsArray + slotIndex * 0x2c);
    }
}