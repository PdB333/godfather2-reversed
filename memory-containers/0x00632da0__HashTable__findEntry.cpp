// FUNC_NAME: HashTable::findEntry
int HashTable::findEntry(float *key) {
    // this in EAX (or ECX? Probably __thiscall with this in ECX, but decompiled shows in_EAX)
    // Hash table is at this+0x44
    HashTable *ht = *(HashTable**)((char*)this + 0x44);

    // Get size power-of-two from byte at ht+7
    int size = 1 << (ht->shift & 0x1f);  // shift is at ht+7

    if (size == 0) {
        return 0;
    }

    // Array of entries at ht+0x10, each entry size 0x14 (20 bytes)
    Entry *entryArray = ht->entries;          // ht+0x10
    Entry *entry = &entryArray[size - 1];     // start from last entry

    do {
        // Entry layout (each 20 bytes):
        // +0x00: int reserved
        // +0x04: int typeOrFlags
        // +0x08: float keyX
        // +0x0C: float keyY
        // +0x10: int data

        float *entryKeyX = &entry->keyX;      // same as (float*)(entry + 3) but careful
        float *entryKeyY = &entry->keyY;

        // Compare first key component
        if (key[0] == entry->keyX) {
            // Switch on first key component (reinterpreted as int for sentinel values)
            switch (*(int*)&key[0]) {
            case 0x00000000: // 0.0f
                break; // always accept if first key matches
            default:
            case 0x00000001: // 4.2039e-45f (denormalized sentinel)
                if (key[1] != entry->keyY) {
                    goto nextEntry;
                }
                break;
            }

            // Additional condition: entry[-1] (previous entry) type must be 4
            if ((entry - 1)->typeOrFlags == 4) {
                return (entry - 1)->data + 0x10;
            }
        }

nextEntry:
        entry--;        // move to previous entry
    } while (entry >= entryArray); // loop while entry index >= 0

    return 0;
}