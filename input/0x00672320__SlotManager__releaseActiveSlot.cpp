// FUNC_NAME: SlotManager::releaseActiveSlot

void SlotManager::releaseActiveSlot(int* stopFlag) {
    // Check if there is an active slot index (not 0xFFFF)
    uint16_t activeIndex = *(uint16_t*)(this + 0x1e1c); // m_activeSlotIndex
    if (activeIndex == 0xffff) {
        return;
    }

    // Index is masked to 7 bits (max 128 slots)
    uint32_t slotIdx = activeIndex & 0x7f;
    
    // Read the count of sub-elements from the slot's short at offset 0x48 + idx*0x3c
    // This likely indicates how many times the inner cleanup loop runs
    int32_t loopCount = *(int16_t*)(this + 0x48 + slotIdx * 0x3c); // m_slotCountArray + slotIdx

    // Compute base of the slot's data block (stride 0x3c from start of this)
    int32_t slotDataBase = (int32_t)this + slotIdx * 0x3c; // m_slotDataArray[slotIdx]

    // Loop to process sub-elements (e.g., animations, tasks)
    for (int32_t i = loopCount; i > 0; i--) {
        FUN_00674eb0(); // likely a cleanup helper for sub-element
        if (*stopFlag == 0) {
            FUN_00675d20(); // additional cleanup if not stopped
        }
    }

    // Retrieve allocator manager at +0x1e38 (e.g., m_poolAllocator)
    int32_t allocator = *(int32_t*)(this + 0x1e38); // m_allocator

    // Free three pointers stored at offsets 0x4c, 0x50, 0x54 from the slot data base
    int32_t ptr1 = *(int32_t*)(slotDataBase + 0x4c);
    int32_t ptr2 = *(int32_t*)(slotDataBase + 0x4c); // Actually this is a copy; see below
    int32_t ptr3 = *(int32_t*)(slotDataBase + 0x50);
    
    // First pointer at offset 0x54
    if (ptr1 != 0) {
        // Clear the reference in the allocator's list (at offset +0xc of allocator)
        *(uint32_t*)(*(int32_t*)(allocator + 0xc) + *(int32_t*)(ptr1 - 8) * 4) = 0;
        // Decrement allocator count at allocator+4
        (*(int32_t*)(allocator + 4))--;
        // Deallocate the memory block (header at ptr1 - 0x10)
        (*DAT_01206694)(ptr1 - 0x10);
    }

    // Second pointer at offset 0x4c
    int32_t ptrSecond = *(int32_t*)(slotDataBase + 0x4c);
    if (ptrSecond != 0) {
        *(uint32_t*)(*(int32_t*)(allocator + 0xc) + *(int32_t*)(ptrSecond - 8) * 4) = 0;
        (*(int32_t*)(allocator + 4))--;
        (*DAT_01206694)(ptrSecond - 0x10);
    }

    // Third pointer at offset 0x50
    int32_t ptrThird = *(int32_t*)(slotDataBase + 0x50);
    if (ptrThird != 0) {
        *(uint32_t*)(*(int32_t*)(allocator + 0xc) + *(int32_t*)(ptrThird - 8) * 4) = 0;
        (*(int32_t*)(allocator + 4))--;
        (*DAT_01206694)(ptrThird - 0x10);
    }

    // Mark slot as inactive
    *(uint16_t*)(this + 0x1e1c) = 0xffff;
}