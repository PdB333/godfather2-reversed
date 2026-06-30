// FUNC_NAME: EARS::SlotManager::removeSlot
// Address: 0x00704260 (thunk at 0x00704380)
// Removes the slot at a given index from a doubly linked list stored in a compact array.
// Each slot is 8 bytes: +0: m_pData (pointer to an object), +4: m_pPrev (pointer back to the node from the object).
// The object itself has a back-pointer at offset +0x04 to the slot node.
// The array is stored as: this[0] = pointer to node array, this[4] = number of active slots.
// After removal, all slots after the index are shifted left by overwriting data pointers,
// and the linked list pointers are updated accordingly.

void __thiscall EARS::SlotManager::removeSlot(int* pThis, unsigned int index)
{
    int* nodeArray = (int*)pThis[0];   // base pointer to slot array (each slot 8 bytes)
    unsigned int count = pThis[1];     // number of active slots
    
    // Process slots from index to count-2 (the last slot is handled separately)
    if (index < count - 1U)
    {
        do
        {
            int* currentSlot = nodeArray + index * 2;  // each slot is 2 ints (8 bytes)
            int* nextSlot = currentSlot + 2;           // next slot's first int (at +8 bytes)
            
            // If the slot object itself does not point to the next slot (meaning the data pointer is not self-referencing or invalid)
            if (currentSlot != nextSlot)
            {
                int nextData = nextSlot[0];  // data pointer of the next slot
                
                // Only perform relinking if the current data pointer differs
                if (currentSlot[0] != nextData)
                {
                    if (currentSlot[0] != 0)
                    {
                        // Clean up the current slot's object reference
                        // FUN_004daf90 likely destroys or releases the object
                        // We'll call it with the current slot pointer
                        // Not defined, assume it's a method of the class
                        // For now, we leave as external call
                        // replace with actual cleanup function name if known
                        EARS::SlotManager::cleanupSlot(currentSlot);
                    }
                    
                    // Update current slot's data pointer to the next slot's data
                    currentSlot[0] = nextData;
                    
                    if (nextData != 0)
                    {
                        // The object at nextData has a back-pointer at +0x04 pointing to its slot.
                        // We need to make that back-pointer point to the current slot instead of the next slot.
                        // currentSlot[1] becomes the previous back-pointer of the next object.
                        currentSlot[1] = *(int*)(nextData + 4);
                        // Update the object's back-pointer to now point to the current slot
                        *(int**)(nextData + 4) = currentSlot;
                    }
                }
            }
            
            index++;
        } while (index < count - 1U);
    }
    
    // Decrement the active slot count
    pThis[1] = count - 1;
    
    // Check the last slot (now at the end of the array after decrement)
    int* lastSlot = nodeArray + (count - 1) * 2;  // note: after decrement, count-1 is the new last index? 
    // Actually after decrement, the last slot index is count-2 (since count decreased).
    // But the code uses: *(int *)(*param_1 + param_1[1] * 8) where param_1[1] is the new count.
    // That's: nodeArray[newCount * 2] (first int of slot at newCount)
    // So it examines the slot at index = newCount, which is one past the new last slot.
    // That slot might be unused; if its data pointer is non-zero, it needs cleanup.
    if (*(int*)((int)nodeArray + pThis[1] * 8) != 0)
    {
        // Call cleanup on that slot (with no arguments? but signature requires a pointer)
        // Possibly it's an error; we assume cleanupSlot with the slot pointer.
        EARS::SlotManager::cleanupSlot(nodeArray + pThis[1] * 2);
    }
}

// Note: The original code's cleanup function (FUN_004daf90) is called in two places.
// Its signature is likely: void __thiscall EARS::SlotManager::cleanupSlot(int* slot)
// We'll define it as a stub here for completeness.
// Since it's not provided, we leave the call as a placeholder.