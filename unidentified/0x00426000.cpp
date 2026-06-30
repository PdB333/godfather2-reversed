// FUNC_ADDR: 0x00426000 - Releases all object pointers in the internal array and sets them to null
// Class: PointerArray (likely container for dynamic array of object pointers)
// Offsets: +0x14 = start of pointer array, +0x150 = count (uint32)
void PointerArray::releaseAll() {
    uint32 count = *(uint32*)((uint8_t*)this + 0x150);
    if (count != 0) {
        void** array = (void**)((uint8_t*)this + 0x14);
        for (uint32 i = 0; i < count; i++) {
            if (array[i] != nullptr) {
                // Call separate release function on the object (FUN_004226c0)
                releaseObject(array[i]);
                array[i] = nullptr;
            }
        }
    }
}

// External release function (address 0x004226c0) - frees or deinitializes an object
extern void releaseObject(void* obj);