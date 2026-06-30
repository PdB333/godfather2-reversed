// FUN_004524b0: Manager::removeFirstItem
void __thiscall Manager::removeFirstItem(void)
{
    // +0x500 : number of active items
    int itemCount = *(int *)(this + 0x500);
    if (itemCount == 0) return;

    // Shift all elements left by one slot (each slot is 0x28 bytes, stored as 10 dwords)
    if (itemCount != 1)
    {
        // Data array starts at +0x34
        // Use raw pointer manipulation as in original: start at base, increment by 0x28 each iteration
        unsigned int i = 0;
        unsigned int* puVar4 = (unsigned int*)(this + 0x34); // pointer to current slot (first dword)
        do {
            // Copy 5 dwords from slot i+1 to slot i (offsets in bytes: -0x34, -0x30, -0x2C, -0x28, -0x24 from next slot's start?)
            // The original uses negative offsets relative to puVar4, so we replicate that:
            // *(byte*)(puVar4-13) = *(byte*)(puVar4-3);
            // *(dword*)(puVar4-12) = *(dword*)(puVar4-8);
            // ... etc.
            // For brevity and clarity, we can interpret as a block copy of 5 dwords from offset -0x34 to -0x24 of next slot.
            // The exact pattern: copy bytes from (puVar4+2) to (puVar4-0xd) etc. We'll use a memcpy-like approach:
            unsigned int* nextSlot = puVar4 + 10; // next slot (10 dwords = 40 bytes)
            // Overwrite the beginning of current slot with the beginning of next slot
            puVar4[0] = nextSlot[0];
            puVar4[1] = nextSlot[1];
            puVar4[2] = nextSlot[2];
            puVar4[3] = nextSlot[3];
            puVar4[4] = nextSlot[4];
            // Then call FUN_004d3e20 on puVar4+2 (offset +8 in current slot)
            // This likely performs additional cleanup for the slot after shifting
            FUN_004d3e20(puVar4 + 2);
            // Copy the next dword (offset +0x18 in next slot -> offset +0x0C in current slot)
            puVar4[5] = nextSlot[5];
            i++;
            puVar4 = nextSlot; // move to next slot
        } while (i < (unsigned int)(itemCount - 1));
    }

    // Decrement count
    *(int *)(this + 0x500) = itemCount - 1;
    int newCount = *(int *)(this + 0x500); // re-read (original reads from memory again)

    // +0x14 : array of object pointers (0x28 bytes per entry, aligned with data array)
    int* objArray = (int*)(this + 0x14);
    int objPtr = objArray[newCount]; // pointer to the object being removed
    if (objPtr != 0)
    {
        // +0x20 : function pointer stored alongside the array slot (not in the object)
        // The call is: (*(void (__thiscall **)(int))(this + newCount*0x28 + 0x20))(objPtr);
        void (__thiscall *dtor)(int) = *(void (__thiscall **)(int))(this + newCount * 0x28 + 0x20);
        dtor(objPtr);
    }

    // Clear the slot that was just removed (now at index newCount)
    char* slot = (char*)(this + newCount * 0x28);
    // The original checks slot != 0, which is always true here (unless overflow)
    if (slot != 0)
    {
        *slot = 1;               // mark slot as freed? (original sets first byte to 1)
        FUN_004d9500(0);         // unknown reset function
        *(int*)(slot + 0x14) = 0;
        *(int*)(slot + 0x18) = 0;
        *(int*)(slot + 0x1C) = 0;
        *(int*)(slot + 0x20) = 0;
        slot[0x24] = 0;
    }
    return;
}