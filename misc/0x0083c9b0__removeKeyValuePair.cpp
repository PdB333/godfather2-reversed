// FUNC_NAME: removeKeyValuePair

// Reconstructed from 0x0083c9b0 - removes a key-value pair from an internal array
// The object has a dynamic length array of pairs starting at offset 0x100.
// Each pair is two ints: first is the key (used for matching), second is the value.
// Count of elements is at offset 0x128.
void __thiscall removeKeyValuePair(void *thisPtr, int targetKey)
{
    uint index = 0;
    // +0x128: count of pairs
    if (*(uint *)((char *)thisPtr + 0x128) != 0)
    {
        int *pairPtr = (int *)((char *)thisPtr + 0x100);
        // Search for the pair with the matching key
        while (*pairPtr != targetKey)
        {
            index++;
            pairPtr += 2; // move to next pair (2 ints)
            if (*(uint *)((char *)thisPtr + 0x128) <= index)
                return;
        }
        // Found at index 'index'
        if (index < *(uint *)((char *)thisPtr + 0x128))
        {
            // If not the last element, shift surviving pairs down
            if (index < *(uint *)((char *)thisPtr + 0x128) - 1)
            {
                // Start from the found location, overwrite with next pair
                // Compiler likely unrolled this into a memmove-like loop
                int *current = (int *)((char *)thisPtr + 0x100) + index * 2;
                do
                {
                    *current = current[2];
                    current[1] = current[3];
                    index++;
                    current += 2;
                } while (index < *(int *)((char *)thisPtr + 0x128) - 1U);
            }
            // Decrement count
            *(int *)((char *)thisPtr + 0x128) = *(int *)((char *)thisPtr + 0x128) - 1;
        }
    }
}