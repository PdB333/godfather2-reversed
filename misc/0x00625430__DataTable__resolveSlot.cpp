// FUNC_NAME: DataTable::resolveSlot
int* DataTable::resolveSlot(int index) {
    int* result;
    if (index > -10000) {
        // Primary array (indices > -10000): base at this+0x08, each slot is 8 bytes
        return (int*)(*(int*)((char*)this + 8) + index * 8);
    }
    if (index == -10001) {
        // Special fixed offset at this+0x40
        return (int*)((char*)this + 0x40);
    }
    if (index == -10000) {
        // Secondary array (index -10000): base at this+0x10, offset +0x2c
        return (int*)(*(int*)((char*)this + 0x10) + 0x2c);
    }
    // Indices < -10001: tertiary array with header at *(this+0xc) - 4
    int headerPtr = *(int*)(*(int*)((char*)this + 0xc) - 4);
    int localIndex = -10001 - index;  // Compute index within this table
    if (localIndex <= *(unsigned char*)(headerPtr + 7)) {
        // Array starts at headerPtr + 8, each entry 8 bytes
        return (int*)(headerPtr + 8 + localIndex * 8);
    }
    return nullptr;
}