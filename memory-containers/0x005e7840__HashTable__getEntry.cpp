// FUNC_NAME: HashTable::getEntry
bool __thiscall HashTable::getEntry(uint id, uint32 outData[4]) {
    byte count = *(byte *)(this + 0x1c);               // +0x1c: number of slots
    byte idx = (byte)id;                               // low byte as index
    uint hashed = id ^ 0xad103100;                     // simple hash verification

    if (hashed < (uint)count && count != 0 && idx < count) {
        int *entry = *(int **)(this + 4 + idx * 4);    // +4: array of entry pointers
        if (entry != 0) {
            // Copy 16 bytes from entry+0x40 (e.g., a Vector4 or RGBA color)
            outData[0] = *(uint32 *)(entry + 0x40);
            outData[1] = *(uint32 *)(entry + 0x44);
            outData[2] = *(uint32 *)(entry + 0x48);
            outData[3] = *(uint32 *)(entry + 0x4c);
            return true;
        }
    }
    return false;
}