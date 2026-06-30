// FUNC_NAME: ObjectContainer::findFirstActive
// Function at 0x00416ce0: Iterates over an array of elements (each 0x58 bytes) and returns
// a combined value: low byte = 1 if found, 0 if not found; high 24 bits = index (if found) or count (if not found).
// Offsets: +0x34 = uint count of elements; +0x50 = pointer to array of Element (+0x2c = short isActive flag)
uint __fastcall ObjectContainer::findFirstActive() {
    uint index = 0;
    // +0x34: count of elements in the array
    if (this->count != 0) {
        // +0x50: pointer to the first element, then +0x2c to reach the "isActive" short
        short* currentActive = &(this->elements[0].isActive);
        do {
            if (*currentActive != 0) {
                // Found: encode index in upper 24 bits, set low byte to 1
                return (index << 8) | 1;
            }
            index++;
            // Advance to the next element's isActive field: each element is 0x58 bytes
            currentActive = (short*)((char*)currentActive + 0x58);
        } while (index < this->count);
    }
    // Not found: return index (which equals count) shifted left 8, low byte zero
    return index << 8;
}