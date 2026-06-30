// FUNC_NAME: sortedArrayInsertKeyReturnValue
// Function address: 0x00617440
// Role: Insert a key into a sorted array of uint pairs (key, value) if not already present.
//       Returns pointer to the value slot of the existing or newly inserted entry.
//       Returns null (0) if the key already exists (duplicate detection).
// Struct layout: param_1 points to a container with:
//   +0x00: pointer to an array of uint pairs (key at even index, value at odd index)
//   +0x04: count of pairs (int)
// Called from 0x00616800.

uint* sortedArrayInsertKeyReturnValue(void* container, uint* keyPtr)
{
    int i = 0;
    int count = *(int*)((char*)container + 4); // +0x04
    if (0 < count)
    {
        uint* current = *(uint**)container; // +0x00
        do
        {
            if (*keyPtr == *current)
            {
                return (uint*)0x0; // key already exists
            }
            if (*keyPtr < *current) break; // insertion point found
            i++;
            current += 2; // advance to next pair
        } while (i < count);
    }
    // Insert at position i (shifted by FUN_006177c0)
    uint* insertionPoint = FUN_006177c0(container, i);
    *insertionPoint = *keyPtr;
    return insertionPoint + 1; // pointer to the value slot
}