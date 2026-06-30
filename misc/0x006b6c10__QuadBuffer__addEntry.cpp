// FUNC_NAME: QuadBuffer::addEntry
void __thiscall QuadBuffer::addEntry(const uint* src) {
    // +0x00: count (uint, max 4)
    // +0x04: entries[0] (20 bytes = 5 uint per entry)
    //   each entry: data[5] but only first 4 used here
    if (this->count < 4) {
        uint* dest = reinterpret_cast<uint*>(reinterpret_cast<uintptr_t>(this) + sizeof(uint)) + this->count * 5;
        dest[0] = src[0];
        dest[1] = src[1];
        dest[2] = src[2];
        dest[3] = src[3];
        this->count++;
    }
}