// FUNC_NAME: EffectManager::releaseExpiredSlot

void __fastcall EffectManager::releaseExpiredSlot(EffectManager* this, int slotIndex)
{
    int subSlotIndex;
    int* refCounter;

    // Check if slot index is valid and the manager has active effects
    if (slotIndex >= 0 && this->activeEffectCount != 0)
    {
        // Get pointer to the slot structure (24 bytes each)
        EffectSlot* slot = (EffectSlot*)((uintptr_t)this + slotIndex * 0x18);

        // Check if the slot has an effect assigned (offset +8 non-zero)
        if (slot->effectTypeId != 0)
        {
            // Handle sub-effect reference counting (if active)
            if (this->subEffectActive &&
                (subSlotIndex = this->subEffectSlotIndices[slotIndex]) >= 0 &&
                this->subEffectTimers[slotIndex] <= 0.0f)
            {
                // Decrement reference count for the sub-effect
                refCounter = &this->subEffectRefCounts[subSlotIndex];
                (*refCounter)--;
                if (*refCounter == 0)
                {
                    // Clear sub-effect when count reaches zero
                    this->subEffectData[subSlotIndex] = 0;
                    this->subEffectRefCounts[subSlotIndex] = 0;
                    this->subEffectActive--;
                }
            }

            // If the slot's timer has expired, fully clear the slot
            if (this->slotTimers[slotIndex] <= 0.0f)
            {
                // Mark slot as inactive
                this->slotActiveFlags[slotIndex] = 0;
                // Clear the 24-byte slot structure
                slot->data1 = 0;
                slot->data2 = 0;
                slot->data3 = 0;
                slot->data4 = 0;
                slot->data5 = 0;
                slot->data6 = 0;
                // Reset sub-effect index and decrement active count
                this->subEffectSlotIndices[slotIndex] = -1;
                this->activeEffectCount--;
            }
        }
    }
}