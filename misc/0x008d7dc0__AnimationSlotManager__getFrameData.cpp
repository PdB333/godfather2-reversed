// FUNC_NAME: AnimationSlotManager::getFrameData
// 0x008d7dc0: Returns a pointer to frame data for a given animation slot and frame index.
// Uses a two-level lookup: first finds a slot (44-byte entries) by ID, then offsets into a frame array (20-byte entries).

int __thiscall AnimationSlotManager::getFrameData(int slotId, int frameIndex)
{
    int slotIndex;
    int* slotBase;

    // Try to get the slot index from the slot ID (fast path)
    slotIndex = this->findSlotById(&slotId);
    if ((slotIndex < 0) ||
        (slotBase = (int*)(slotIndex * 44 + 4 + *(int*)(this + 0x2c)), slotBase == (int*)0))
    {
        // Slot not found or invalid; allocate a new slot and perform a short wait
        slotIndex = this->createSlot(&slotId);
        int retries = 2;
        do {
            this->yieldSpin();
            retries--;
        } while (retries != 0);
        slotBase = (int*)(slotIndex * 44 + 4 + *(int*)(this + 0x2c));
    }
    // Return pointer to the frame data within the slot
    return (int)(slotBase + frameIndex * 20);
}

// Static helper functions (declared within the class but not shown in the decompiled code)
// int AnimationSlotManager::findSlotById(int* slotId);    // 0x008d7190
// int AnimationSlotManager::createSlot(int* slotId);      // 0x008d7d20
// void AnimationSlotManager::yieldSpin();                  // 0x008d5df0