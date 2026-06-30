// FUNC_NAME: Container::removeToCount
void __thiscall Container::removeToCount(int targetCount) {
    // This object has an internal data pointer at +0x1c
    int* internal = *(int**)(this + 0x1c);             // +0x1c: pointer to internal structure
    // internal fields:
    // [0x00]: pointer to another structure (used for array base)
    // [0x06]: value to write during removal (at +0x18)
    // [0x0d]: count of elements (at +0x34)
    // [0xae]: start of an array of indices (at +0x2b8) – each index is into a 12-byte record

    while (targetCount < internal[0xd]) {
        internal[0xd]--;                                // decrement count (removing from end)
        // Get the index stored at the newly removed position (which is now the last valid entry)
        int recordIndex = internal[internal[0xd] + 0xae]; // read index from internal->m_indices[newCount]
        // Destination: base from (*internal + 0x18) + 8 + recordIndex * sizeof(record) // each record is 12 bytes
        int* destArray = *(int**)(*internal + 0x18);    // +0x18 on pointed structure: pointer to array of records
        *(int*)(destArray + 8 + recordIndex * 0xc) = internal[6]; // write internal->m_value into record field at offset 8
    }
}