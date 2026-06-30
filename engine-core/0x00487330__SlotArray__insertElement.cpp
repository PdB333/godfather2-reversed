// FUNC_NAME: SlotArray::insertElement
// Function at 0x487330: Insert an element into a fixed-size array of 4 slots (36 bytes each).
// The array occupies offsets 0x00-0x8F (4 * 0x24), with a count at offset 0x90.
// Returns 1 on success, 0 if the array is already full (count > 3).
// The source element is not destroyed; only two DWORDs from source+0x1C/source+0x20 are copied.
// Uses magic constant 0x2A7ED975 to check for a valid type in each slot's +0x04 field.
// Calls unknown cleanup functions before overwriting a slot.

int __thiscall SlotArray::insertElement(void* thisPtr, void* sourceElem, uint insertIndex)
{
    uint count = *(uint*)((uint)thisPtr + 0x90); // +0x90: number of stored elements

    if (count > 3) {
        return 0; // Array full (max 4 elements)
    }

    // Case 1: Appending at the end (insertIndex == count)
    if (insertIndex == count) {
        void* slot = (void*)((uint)thisPtr + insertIndex * 0x24); // target slot address
        if (slot != sourceElem) {
            // If the slot has allocated resources and is the wrong type, free them
            if ( (*(int*)((uint)slot + 0x18) != 0) && (*(int*)((uint)slot + 4) != 0x2A7ED975) ) {
                freeSlotResources(slot); // FUN_00407640 – likely destructor
            }
            clearSlot(slot); // FUN_00487200 – likely memset to zero
        }
        // Copy the last two DWORDs from source to slot
        *(int*)((uint)slot   + 0x1C) = *(int*)((uint)sourceElem + 0x1C);
        *(int*)((uint)slot   + 0x20) = *(int*)((uint)sourceElem + 0x20);
        *(uint*)((uint)thisPtr + 0x90) = count + 1; // increment count
        return 1;
    }
    // Case 2: Insert in the middle – shift elements to make room
    else {
        void* freeSlot = (void*)((uint)thisPtr + count * 0x24); // first empty slot (index == count)
        void* lastUsedSlot = (void*)((uint)freeSlot - 0x24);    // last occupied slot

        // Move the last element's data into the free slot (temporary shuffle)
        if (freeSlot != lastUsedSlot) {
            if ( (*(int*)((uint)freeSlot    + 0x18) != 0) &&
                 (*(int*)((uint)freeSlot    + 4   ) != 0x2A7ED975) ) {
                freeSlotResources(freeSlot);
            }
            clearSlot(freeSlot);
        }
        // Copy the last element's two fields into the free slot
        *(int*)((uint)freeSlot + 0x1C) = *(int*)((uint)lastUsedSlot + 0x1C);
        *(int*)((uint)freeSlot + 0x20) = *(int*)((uint)lastUsedSlot + 0x20);

        uint newCount = count - 1; // temporarily reduce count for the shift loop

        // Shift elements up by one from insertIndex to newCount-1
        if (insertIndex < newCount) {
            uint numShifts = newCount - insertIndex; // number of slots to move
            void* curSlot = (void*)((uint)thisPtr + (newCount - 1) * 0x24); // start from last used (now newCount-1)
            do {
                void* nextSlot = (void*)((uint)curSlot + 0x24); // slot after current
                if (curSlot != nextSlot) {
                    if ( (*(int*)((uint)nextSlot + 0x18) != 0) &&
                         (*(int*)((uint)nextSlot + 4   ) != 0x2A7ED975) ) {
                        freeSlotResources(nextSlot);
                    }
                    clearSlot(nextSlot);
                }
                // Copy current slot's data to the next slot
                *(int*)((uint)nextSlot + 0x1C) = *(int*)((uint)curSlot + 0x1C);
                *(int*)((uint)nextSlot + 0x20) = *(int*)((uint)curSlot + 0x20);
                curSlot = (void*)((uint)curSlot - 0x24); // move backwards
                numShifts--;
            } while (numShifts != 0);
        }

        // Now insert the new element at the original index
        *(uint*)((uint)thisPtr + 0x90) = *(uint*)((uint)thisPtr + 0x90) + 1; // restore count (stays <= 4)

        void* targetSlot = (void*)((uint)thisPtr + insertIndex * 0x24); // slot at insertIndex
        if (targetSlot != sourceElem) {
            if ( (*(int*)((uint)targetSlot + 0x18) != 0) &&
                 (*(int*)((uint)targetSlot + 4   ) != 0x2A7ED975) ) {
                freeSlotResources(targetSlot);
            }
            clearSlot(targetSlot);
        }
        *(int*)((uint)targetSlot + 0x1C) = *(int*)((uint)sourceElem + 0x1C);
        *(int*)((uint)targetSlot + 0x20) = *(int*)((uint)sourceElem + 0x20);
        return 1;
    }
}