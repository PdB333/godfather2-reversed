// FUNC_NAME: SortedUIntSet::insertUnique
uint* SortedUIntSet::insertUnique(uint* valuePtr) {
    // Offset 0x00: this->data (uint*)
    // Offset 0x04: this->count (int)
    int i = 0;
    if (this->count > 0) {
        uint* current = this->data;
        do {
            if (*valuePtr == *current) {
                return nullptr; // duplicate value, insertion rejected
            }
            if (*valuePtr < *current) {
                break; // insertion point found before current
            }
            i++;
            current++;
        } while (i < this->count);
    }
    // Allocate a new slot in the sorted array (FUN_004837e0 handles resizing)
    uint* newSlot = reinterpret_cast<uint*>(FUN_004837e0());
    *newSlot = *valuePtr;   // store the value
    return newSlot + 1;     // return pointer following the inserted value (internal iterator convention)
}