// FUNC_NAME: DataTable::findEntryById
char * __thiscall DataTable::findEntryById(int thisPtr, int id, uint *outMaxPriority)
{
    uint priority;
    char *entryPtr;
    uint currentIndex;
    int keyOffset;
    int valueOffset;
    
    *outMaxPriority = 0;
    currentIndex = 0;
    
    if (*(int *)(thisPtr + 0xc) == 0) {
        return (char *)0x0;
    }
    
    keyOffset = 0;
    valueOffset = 0;
    
    do {
        // Compare the key at current position (key array element size = 0x10)
        if (*(int *)(*(int *)(thisPtr + 4) + keyOffset) == id) {
            // Match found: get pointer to value entry (value array element size = 0x2c)
            entryPtr = (char *)(*(int *)(thisPtr + 8) + valueOffset);
            
            // Update maximum priority (at offset +0x28 within value entry)
            priority = *(uint *)(entryPtr + 0x28);
            if (*outMaxPriority < priority) {
                *outMaxPriority = priority;
            }
            
            // If first byte (valid flag?) is non-zero, return pointer to entry
            if (*entryPtr != '\0') {
                return entryPtr;
            }
        }
        
        currentIndex++;
        keyOffset += 0x10;   // advance to next key slot
        valueOffset += 0x2c; // advance to next value slot
        
        // Check if all entries have been processed
        if (*(uint *)(thisPtr + 0xc) <= currentIndex) {
            return (char *)0x0;
        }
    } while (true);
}