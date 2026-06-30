// FUNC_NAME: PointerArray::remove
void __thiscall PointerArray::remove(int *thisPtr, int index)
{
    // thisPtr[0] = m_pData (array of 2-int slots)
    // thisPtr[1] = m_nCount (number of valid slots)
    int *dataArray = (int *)thisPtr[0];
    int count = thisPtr[1];
    int lastIndex = count - 1;

    if (index != lastIndex) {
        int *lastSlot = dataArray + lastIndex * 2; // each slot is 2 ints (8 bytes)
        int *removeSlot = dataArray + index * 2;

        if (removeSlot != lastSlot) {
            int lastObj = *lastSlot; // pointer to object at last slot
            if (*removeSlot != lastObj) {
                if (*removeSlot != 0) {
                    // Free the object that was at the removed slot
                    FUN_004daf90(removeSlot);
                }
                // Move the last slot's object pointer to the removed slot
                *removeSlot = lastObj;
                if (lastObj != 0) {
                    // Update linked list: the removed slot becomes successor of the last object
                    // The object at lastObj+4 is its "next" pointer
                    removeSlot[1] = *(int *)(lastObj + 4);
                    *(int **)(lastObj + 4) = removeSlot;
                }
            }
        }
    }

    // Decrement count (one element removed)
    thisPtr[1] = count - 1;

    // Check the slot that was formerly the last (now beyond the new count)
    int *oldLastSlot = dataArray + (count - 1) * 2; // after decrement, count-1 is new last index, so this is the old last slot
    // Actually the code checks slot at index `count` (since param_1[1] = count after decrement)
    // So we use dataArray + count * 2
    int *vacatedSlot = dataArray + thisPtr[1] * 2; // thisPtr[1] is new count, so index = new count
    if (*vacatedSlot != 0) {
        // Free the object that was at the vacated slot (if not null)
        FUN_004daf90(vacatedSlot);
    }
}