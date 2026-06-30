// FUNC_NAME: ResourceTable::fixup
// Function address: 0x004cfe00
// This function appears to fix up relative pointers in a resource table and build an index
// from a compact format. It processes a table of 0x100 pointers (offsets relative to this + iVar1)
// and then iterates over a secondary table of 0x18-byte entries to link them into a lookup structure.

// The class layout (offsets from this):
// +0x00: some base pointer (param1)
// +0x04: (unused or part of vtable)
// +0x08: ...
// +0x0C: (in_EAX[3]) offset to secondary table
// +0x10: (in_EAX[4]) base adjustment value (iVar1)
// +0x44..+0x43C: table of 256 pointers (in_EAX[0x11] to [0x111])
// +0x440: (in_EAX[0x110]) ...
// +0x444: (in_EAX[0x111]) param2 stored here
// +0x448: (in_EAX[0x112]) short count, if 0, clears pointer at +0x450
// +0x44C: (in_EAX[0x113]) offset for pointer at +0x450
// +0x450: (in_EAX[0x114]) pointer that gets computed from offset above

class ResourceTable {
public:
    // Secondary entry structure (size 0x18 = 24 bytes)
    struct Entry {
        byte idSmall;     // offset +0x00, used as index into pointer array (multiplied by 4)
        byte idLarge;     // offset +0x01, used as index into the pointer array (byte)
        byte padding[22]; // rest of entry (unknown)
    };

    // Fields
    void* basePtr;                   // +0x00 (param1)
    // ... (unknown fields at +0x04..+0x0B)
    int secondaryTableOffset;        // +0x0C (in_EAX[3]) offset from this to start of secondary entries
    int baseAdjust;                  // +0x10 (in_EAX[4]) base value added to pointers in fixup
    void* pointers[256];             // +0x44 (in_EAX[0x11]) array of pointer slots (0x100 entries)
    // +0x444: (in_EAX[0x111]) stored param2?
    // +0x448: short secondaryEntryCount (in_EAX[0x112])
    // +0x44C: int pointerOffset (in_EAX[0x113])
    // +0x450: void* computedPtr (in_EAX[0x114])

    short secondaryEntryCount;       // +0x448 (short at offset 0x112*4 = 0x448? Wait, in_EAX is int*, so index 0x112 -> offset 0x448)
    int pointerOffset;               // +0x44C (in_EAX[0x113])
    void* computedPtr;               // +0x450 (in_EAX[0x114])

    // Note: The offsets above are derived from in_EAX being int* (4-byte aligned). 
    // But the decompiled code uses *(short*)(this+10) - that's offset 0x0A (not int-aligned). 
    // This indicates the class has a mix of types. Let's correct.

    // Better: Use byte offsets. in_EAX is used as int*, but actual fields may be char/short.
    // For clarity, we keep the structure as per the decompiled access patterns.
};

void __thiscall ResourceTable::fixup(int param1, int param2) {
    // Get base adjustment from offset +0x10 (in_EAX[4])
    int adj = this->baseAdjust; // in_EAX[0x10]
    
    // Pointer to secondary entry block: this + secondaryTableOffset (in_EAX[3])
    byte* entryPtr = (byte*)(this->secondaryTableOffset + (int)this);
    // in decompiled: pbVar2 = (byte *)(in_EAX[3] + (int)in_EAX);
    
    // Handle pointer at +0x450
    if (*(short*)((int)this + 0x448) == 0) { // check short at offset 0x448 (index 0x112)
        this->computedPtr = 0; // in_EAX[0x114] = 0
    } else {
        // computedPtr = this + pointerOffset (offset +0x44C, index 0x113)
        this->computedPtr = (void*)(this->pointerOffset + (int)this);
    }
    
    // Fixup 256 pointers in the array starting at +0x44
    int* pSlot = (int*)&this->pointers[0]; // in_EAX + 0x11
    int count = 0x100; // 256
    do {
        if (*pSlot != 0) {
            // Convert from relative offset to absolute pointer: this + offset + adj
            *pSlot = (int)this + *pSlot + adj;
        }
        pSlot++;
        count--;
    } while (count != 0);
    
    // Build index for secondary entries
    unsigned int entryIdx = 0;
    short numEntries = *(short*)((int)this + 10); // short at offset 10 (in_EAX[2.5])
    if (numEntries != 0) {
        do {
            // Get small ID (byte 0) and large ID (byte 1) from current entry
            byte smallId = entryPtr[0];
            byte largeId = entryPtr[1];
            
            // Get pointer at slot index = largeId (array index from 0..255)
            int* slotPtr = (int*)(this->pointers[largeId]); // in_EAX[largeId + 0x11]
            if (slotPtr != 0) {
                // Set pointer at offset smallId*4 within that slot's pointed memory to point to this entry
                *(byte**)((int)slotPtr + smallId * 4) = entryPtr;
            }
            
            entryIdx++;
            entryPtr += 0x18; // size of each entry
        } while (entryIdx < (uint)numEntries);
    }
    
    // Store parameters
    this->pointers[0x100]? // Actually in_EAX[0x111] = param2; that is after the array?
    // The array is 256 entries, so index 0x111 (273) goes beyond. But decompiled says in_EAX[0x111].
    // This must be another field at offset 0x444. We'll treat it as field at offset 0x444.
    *(int*)((int)this + 0x444) = param2; // in_EAX[0x111]
    *(int*)this = param1; // *in_EAX = param1
}
```