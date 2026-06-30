// FUNC_NAME: EffectManager::updateSlot
void __thiscall EffectManager::updateSlot(int slotIndex)
{
    // Check for valid slot index and existence of active slots
    if (slotIndex < 0 || mActiveCount == 0)
        return;

    // Slot structure starts at this + slotIndex * 0x18
    Slot* slot = &mSlots[slotIndex];
    if (slot->field8 == 0)  // Slot not in use
        return;

    // Process secondary reference counter if timer expired
    if (mSecondaryCount != 0)
    {
        int secondaryIndex = mSlotInts[slotIndex];
        if (secondaryIndex >= 0 && mSlotFloats[slotIndex] <= 0.0f)
        {
            SecondaryPair* pair = &mSecondaryPairs[secondaryIndex];
            // Decrement reference count
            pair->second--;
            if (pair->second == 0)
            {
                // Clear the pair when count reaches zero
                pair->first = 0;
                pair->second = 0;
                mSecondaryCount--;
            }
        }
    }

    // If timer expired, deallocate the slot
    if (mSlotFloats[slotIndex] <= 0.0f)
    {
        mSlotFlags[slotIndex] = 0;          // Clear activation flag
        slot->field0 = 0;                   // Zero entire slot structure
        slot->field4 = 0;
        slot->field8 = 0;
        slot->fieldC = 0;
        slot->field10 = 0;
        slot->field14 = 0;
        mSlotInts[slotIndex] = -1;          // Reset index
        mActiveCount--;                     // Decrement active slot counter
    }
}