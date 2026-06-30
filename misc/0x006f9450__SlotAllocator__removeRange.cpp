// FUNC_NAME: SlotAllocator::removeRange
void __thiscall SlotAllocator::removeRange(int startIndex, unsigned int count) {
    int* slotBase = *(int**)this;          // +0x00: base pointer to an array of 8-byte entries
    int slotCount = *(int*)(this + 4);     // +0x04: number of allocated entries

    // Process entries from startIndex up to slotCount-2
    if (startIndex < slotCount - 1) {
        do {
            uint offset = startIndex * 8;   // each entry is 8 bytes
            int* entry = (int*)((char*)slotBase + offset);

            // entry[0] = prev, entry[1] = ???, entry[2] used as next pointer (beyond 8-byte boundary – likely a linked list trick)
            int* nextEntry = (int*)entry[2];

            // Unlink this entry if it is not already self‑linked
            if (entry[0] != (int)nextEntry) {
                if (entry[0] != 0) {
                    removeNode(entry);   // FUN_004daf90 – unlinks the entry from its list
                }
                // Relink: set prev to next
                entry[0] = (int)nextEntry;
                if (nextEntry != 0) {
                    entry[1] = *(int*)((char*)nextEntry + 4);   // copy next entry’s second field
                    *(int**)((char*)nextEntry + 4) = entry;     // make next entry point back to this
                }
            }
            startIndex++;
        } while (startIndex < slotCount - 1);
    }

    // Decrease the count
    slotCount--;
    *(int*)(this + 4) = slotCount;

    // If the entry now at the end is not null, clean it up
    int* lastEntry = (int*)((char*)slotBase + slotCount * 8);
    if (lastEntry[0] != 0) {
        removeNode(lastEntry);   // FUN_004daf90
    }
}