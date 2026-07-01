// FUNC_NAME: UIntKeyValueMap::insertKeyOrReturnValueSlot
/**
* Function: UIntKeyValueMap::insertKeyOrReturnValueSlot
* Address: 0x0094ab00
* Role: Inserts a uint key into a sorted array of key-value pairs (key/value each 4 bytes).
*       Performs linear scan to find insertion point; no duplicates allowed.
*       Returns pointer to the value slot after insertion, or nullptr if key already exists.
*       The map structure:
*       +0x00: uint* array pointer (size = capacity * 2 * 4)
*       +0x04: int32 count (number of pairs currently stored)
*/
uint* __thiscall UIntKeyValueMap::insertKeyOrReturnValueSlot(void* thisPtr, uint* keyPtr)
{
    int32 count = *(int32*)((char*)thisPtr + 4);
    uint* array = *(uint**)thisPtr;
    int32 i = 0;

    if (count > 0)
    {
        uint* current = array;
        do
        {
            if (*keyPtr == *current)
            {
                // Duplicate key; no insertion.
                return (uint*)0;
            }
            if (*keyPtr < *current)
            {
                // Found insertion point.
                break;
            }
            i = i + 1;
            current = current + 2; // Skip key and value (8 bytes)
        } while (i < count);
    }

    // Insert at position i, shift elements and possibly grow the array.
    uint* insertedSlot = (uint*)FUN_00949b10(i);
    *insertedSlot = *keyPtr; // Store the key
    return insertedSlot + 1; // Return pointer to the value slot
}