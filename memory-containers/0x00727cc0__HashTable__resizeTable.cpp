// FUNC_NAME: HashTable::resizeTable
void __thiscall HashTable::resizeTable(int *this, uint newCapacity)
{
    int *oldSlotAddr;
    int nodePtr;
    int *newSlotAddr;
    uint idx;
    int *newArray;

    // Only resize if current capacity is less than requested
    if ((uint)this[2] < newCapacity) {
        // Allocate new array of entries, each entry is 8 bytes (two ints)
        newArray = (int *)FUN_009c8e80(newCapacity * 8);
        if (*this != 0) {
            idx = 0;
            newSlotAddr = newArray;
            // Copy existing entries (count is this[1])
            if (this[1] != 0) {
                do {
                    // Pointer to old entry at this[0] + idx * 8
                    oldSlotAddr = (int *)(*this + idx * 8);
                    if (newSlotAddr != (int *)0x0) {
                        // Copy first int (node pointer) to new entry
                        nodePtr = *oldSlotAddr;
                        *newSlotAddr = nodePtr;
                        // Initialize new entry's second int to 0 (next pointer)
                        newSlotAddr[1] = 0;
                        if (nodePtr != 0) {
                            // If old node existed, copy its next pointer to new entry's second int
                            newSlotAddr[1] = *(int *)(nodePtr + 4);
                            // Then update old node's next to point to the new entry (relink)
                            *(int **)(nodePtr + 4) = newSlotAddr;
                        }
                    }
                    // Clean up old entry (likely unlink/free node)
                    if (*oldSlotAddr != 0) {
                        FUN_004daf90(oldSlotAddr);
                    }
                    idx++;
                    newSlotAddr += 2; // move to next new entry (2 ints)
                } while (idx < (uint)this[1]);
            }
            // Free old array
            FUN_009c8f10(*this);
        }
        // Update members
        *this = (int)newArray;
        this[2] = newCapacity;
    }
    return;
}