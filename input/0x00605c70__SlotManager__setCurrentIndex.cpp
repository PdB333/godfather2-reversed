// FUNC_NAME: SlotManager::setCurrentIndex
void SlotManager::setCurrentIndex(uint slotIndex, int enableBoundsCheck)
{
    uint adjustedIndex = slotIndex;

    // Only clamp if bounds checking is enabled and the flag at +0x0c is non-zero
    if ((enableBoundsCheck != 0) && (*(int *)(this + 0xc) != 0))
    {
        char validationResult = validateSlot(); // FUN_00605d60 – returns 0 if index should be adjusted
        if (validationResult == '\0')
        {
            clampSlotIndex(this, &slotIndex); // FUN_00605da0 – modifies slotIndex in place
            adjustedIndex = slotIndex;
        }
    }

    // If the (possibly adjusted) index is within capacity, advance the current pointer
    if (adjustedIndex < *(uint *)(this + 0x14)) // m_capacity
    {
        // Compute pointer to element (adjustedIndex + 1) with stride m_elementStride * 4 bytes
        *(uint *)(this + 0x1c) = // m_currentPointer
            *(int *)(this + 0x18) + // m_dataBase
            (adjustedIndex + 1) * *(int *)(this + 0x10) * 4; // m_elementStride
    }
}