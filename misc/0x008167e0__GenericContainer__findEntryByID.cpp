// FUNC_NAME: GenericContainer::findEntryByID
// Address: 0x008167e0
// This function searches a container's entry list for an entry matching a given ID.
// Returns 1 if found, 0 if not found. On success, writes the entry pointer to param_3.

// Container layout:
// +0x0C: int* pFirstEntry      // pointer to first entry in the array
// +0x10: uint  entryCount      // number of entries in the array
// +0x14: ? (not used here)

// Entry layout (each entry is 0x10 bytes):
// +0x00: ? (unknown)
// +0x04: int* pEntryData        // pointer to actual entry data
// +0x08: ? (unknown)
// +0x0C: int  entryID           // the ID to match against param_2

int __thiscall GenericContainer::findEntryByID(int thisPtr, int searchID, int* outEntry)
{
    int currentEntry;
    uint index;
    
    // Initialize return value and index
    int result = 0;
    index = 0;
    
    // Only search if there are entries
    if (*(uint*)(thisPtr + 0x10) != 0)
    {
        currentEntry = *(int*)(thisPtr + 0x0C);
        
        // Linear search through the entry array (each entry is 0x10 bytes)
        while (*(int*)(*(int*)(currentEntry + 4) + 0x0C) != searchID)
        {
            index++;
            currentEntry += 0x10; // advance to next entry
            
            // Exit if we've checked all entries
            if (*(uint*)(thisPtr + 0x10) <= index)
            {
                return result;
            }
        }
        
        // Found matching entry - write pointer to output
        *outEntry = currentEntry;
        result = 1;
    }
    
    return result;
}