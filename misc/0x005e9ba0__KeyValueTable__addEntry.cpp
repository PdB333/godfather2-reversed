// FUNC_NAME: KeyValueTable::addEntry
// 0x005e9ba0
// Adds a key (12-byte struct) and a value (4-byte) to the table, with key initially zero and value computed from an input handle.
void KeyValueTable::addEntry(int inputHandle)
{
    // Grow large struct array if needed (each element = 12 bytes)
    // Offset: +0x1c = large capacity, +0x18 = large count
    // Offset: +0x14 = pointer to large data
    if (this->largeCount == this->largeCapacity) {
        int newCapacity = (this->largeCount == 0) ? 1 : (this->largeCount * 2);
        // FUN_005f0040 reallocates large array
        growLargeArray(newCapacity);
    }

    // Add a zeroed 12-byte entry to large array
    LargeEntry* pEntry = (LargeEntry*)(this->largeArray + this->largeCount * 12);
    this->largeCount++;
    if (pEntry != nullptr) {
        pEntry->key64 = 0;   // first 8 bytes
        pEntry->key32 = 0;   // next 4 bytes
    }

    // Grow small int array if needed (4-byte elements)
    // Offset: +0x10 = small capacity, +0x0c = small count
    // Offset: +0x08 = pointer to small data
    if (this->smallCount == this->smallCapacity) {
        int newCapacity = (this->smallCount == 0) ? 1 : (this->smallCount * 2);
        growSmallArray(newCapacity);
    }

    // Add a zeroed int entry to small array
    int* pValue = this->smallArray + this->smallCount;
    this->smallCount++;
    if (pValue != nullptr) {
        *pValue = 0;
    }

    // Now overwrite the last small entry (the one just added) with a computed value
    int* lastValue = this->smallArray + this->smallCount - 1;
    if (inputHandle != 0) {
        *lastValue = mapInputToInternalId(inputHandle);  // FUN_004dafd0
    } else {
        *lastValue = 0;
    }
}