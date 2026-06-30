// FUNC_NAME: lookupByKey
// Function at 0x006833d0 - linear search in an inline key-value array
// Structure: this+0x8: array of (int key, undefined4 value) pairs, each 8 bytes
//            this+0x88: count of valid entries (uint)
// Returns the value associated with aKey, or 0 if not found.
undefined4 __thiscall lookupByKey(int thisPtr, int aKey)
{
    uint index;
    int *pairPtr;

    // Default return value: 0 (null/not found)
    undefined4 result = 0;
    index = 0;

    // Only search if there are entries
    if (*(uint *)(thisPtr + 0x88) != 0) {
        // Start at the beginning of the key-value array
        pairPtr = (int *)(thisPtr + 8);
        
        // Linear scan: compare each key with aKey
        while (*pairPtr != aKey) {
            index = index + 1;
            pairPtr = pairPtr + 2;  // advance to next pair (8 bytes)
            
            if (*(uint *)(thisPtr + 0x88) <= index) {
                // Reached end without finding match
                return result;  // 0
            }
        }
        
        // Found matching key: return the corresponding value (at offset+0xC + index*8)
        result = *(undefined4 *)(thisPtr + 0xC + index * 8);
    }
    
    return result;
}