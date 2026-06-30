// FUNC_NAME: ResolutionManager::updateScalingFromIndex
// Address: 0x004e21c0
// Role: Reads a resolution entry from a fixed table (0x38 byte struct) using an index stored at this+0x16c,
// then calculates scale factors by dividing a global base resolution (float) by the entry's width and height shorts.
// Stores results in global variables (likely for UI/scaling system).

struct ResolutionEntry {
    short unknown0;   // +0x00
    short width;     // +0x02
    short height;    // +0x04
    // ... rest of 0x38 bytes
};

void __fastcall ResolutionManager::updateScalingFromIndex(int thisPtr)
{
    // Table base: DAT_011a0f28 (array of ResolutionEntry[0x1000])
    // Index stored at thisPtr+0x16c
    unsigned int index = *(unsigned int*)(thisPtr + 0x16c);
    
    ResolutionEntry* entry = nullptr;
    if (index < 0x1000) {
        entry = (ResolutionEntry*)((char*)&DAT_011a0f28 + index * 0x38);
    }
    
    // Store width and height from the entry into global variables
    short width = 0;
    short height = 0;
    if (entry) {
        width = entry->width;
        height = entry->height;
    } else {
        // Could handle null case, but original code leaves them uninitialized
    }
    
    // Global output variables
    DAT_01218e40 = width;           // short, likely screen width
    DAT_01218e42 = height;          // short, likely screen height
    DAT_01218e44 = DAT_00e2b1a4 / (float)width;   // float scale X
    DAT_01218e48 = DAT_00e2b1a4 / (float)height;  // float scale Y
}