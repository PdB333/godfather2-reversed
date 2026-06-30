// FUNC_NAME: Container::getEntry
// Address: 0x004bb610
// Role: Accessor - returns pointer to an element in an array allocated at offset 0x1c, each element size 0x10

int Container::getEntry(int index) {
    // *(this + 0x1c) is the base pointer to an array of elements
    // Each element is 0x10 bytes, so element address = base + index * 0x10
    return *(int *)(this + 0x1c) + index * 0x10;
}