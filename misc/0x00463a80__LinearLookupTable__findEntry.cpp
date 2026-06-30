// FUNC_NAME: LinearLookupTable::findEntry
void __thiscall LinearLookupTable::findEntry(int key, int *outValue)
{
    // +0x0c: this->entriesArray (pointer to array of 12-byte entries)
    // +0x10: this->entryCount (uint32)
    // Each entry: 12 bytes = { int key; int flag; int value; }

    int currentIndex = 0;
    uint byteOffset = 0;
    int foundFlag = 0;

    do {
        if (this->entryCount <= currentIndex) {
            return; // No match found (or exhausted)
        }

        Entry *entry = (Entry *)(this->entriesArray + byteOffset);
        if (entry->key == key) {
            foundFlag = entry->flag;  // Used to exit loop only if non-zero
            *outValue = entry->value; // Return the value via output parameter
        }

        currentIndex++;
        byteOffset += 0xc; // Advance to next entry (12 bytes)
    } while (foundFlag == 0);

    // When foundFlag is non-zero, loop ends; function returns with outValue set
}