// FUNC_NAME: KeyedArray::removeByKey
// Address: 0x0082b140
// Removes an object from the internal array by matching a 4-int key stored at offsets +0x1c, +0x20, +0x24, +0x28.
// Returns a pointer to the removed object, or nullptr if not found.
// The array is stored at +0x08 (pointer to array of pointers) and count at +0x0c.

void* __thiscall KeyedArray::removeByKey(const int* key) {
    uint count = *(uint*)(this + 0x0c);          // number of elements
    if (count != 0) {
        void** entries = *(void***)(this + 0x08); // array of pointers to objects
        for (uint i = 0; i < count; i++) {
            void* entry = entries[i];
            // Compare the 4-int key stored in the object
            if (*(int*)((char*)entry + 0x1c) == key[0] &&
                *(int*)((char*)entry + 0x20) == key[1] &&
                *(int*)((char*)entry + 0x24) == key[2] &&
                *(int*)((char*)entry + 0x28) == key[3]) {
                // Shift remaining elements to fill the gap
                if (i < count - 1) {
                    for (uint j = i; j < count - 1; j++) {
                        entries[j] = entries[j + 1];
                    }
                }
                // Decrement count
                *(int*)(this + 0x0c) = count - 1;
                return entry;
            }
        }
    }
    return nullptr;
}