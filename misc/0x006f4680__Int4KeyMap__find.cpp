// FUNC_NAME: Int4KeyMap::find
int __thiscall Int4KeyMap::find(int this, int* key) {
    // +0x0c: pointer to a dynamic array container (Int4KeyMapEntry)
    int* container = *(int**)(this + 0x0c);
    if (container == nullptr) {
        return 0;
    }

    int count = container[1]; // +0x04: number of entries
    if (count == 0) {
        return 0;
    }

    // container[0] is a pointer to an array of entry pointers
    int** entries = (int**)container[0];
    for (uint i = 0; i < (uint)count; i++) {
        int* entry = entries[i]; // each entry is a pointer to a struct
        // Compare four ints at offsets 0x0c, 0x10, 0x14, 0x18 against the key array
        if (entry[0x0c / 4] == key[0] &&   // key1
            entry[0x10 / 4] == key[1] &&   // key2
            entry[0x14 / 4] == key[2] &&   // key3
            entry[0x18 / 4] == key[3]) {   // key4
            // Return the entry pointer (same as entries[i])
            return (int)entries[i];
        }
    }
    return 0;
}