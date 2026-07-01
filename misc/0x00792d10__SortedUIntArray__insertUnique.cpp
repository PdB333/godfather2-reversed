// FUNC_NAME: SortedUIntArray::insertUnique
uint* __thiscall SortedUIntArray::insertUnique(uint* thisPtr, uint* newKey)
{
    // thisPtr layout:
    // +0x00: uint* data (array of sorted uints)
    // +0x04: int size (current number of elements)
    uint* data = (uint*)thisPtr[0];
    int size = (int)thisPtr[1];
    int insertIndex = 0;

    // Linear search for insertion point or duplicate
    if (size > 0) {
        uint* current = data;
        do {
            if (*newKey == *current) {
                // Duplicate found – return null
                return (uint*)0x0;
            }
            if (*newKey < *current) {
                // Found insertion point (sorted order)
                break;
            }
            insertIndex++;
            current++;
        } while (insertIndex < size);
    }

    // Insert new element at insertIndex (shift elements right, reallocate if needed)
    uint* insertionPoint = (uint*)FUN_00792ac0(insertIndex);
    *insertionPoint = *newKey;
    return insertionPoint + 1; // Return pointer to next slot (may be used for additional data)
}