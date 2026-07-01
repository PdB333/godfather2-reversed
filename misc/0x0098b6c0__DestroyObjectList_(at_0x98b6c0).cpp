// FUNC_NAME: DestroyObjectList (at 0x98b6c0)
// This function iterates over an array of 16-byte entries, each containing an object pointer and a destructor function pointer.
// It calls the destructor on non-null objects.
struct ObjectEntry {
    void* object;              // +0x00: pointer to the managed object
    int unused_04;             // +0x04: unknown/padding
    int unused_08;             // +0x08: unknown/padding
    void (*destroyFunc)(void*); // +0x0C: function to destroy/release the object
};

void DestroyObjectList(ObjectEntry* entriesStart, ObjectEntry* entriesEnd) {
    // Iterate through the range of entries
    for (ObjectEntry* entry = entriesStart; entry < entriesEnd; ++entry) {
        if (entry->object != nullptr) {
            // Call the object's destructor
            entry->destroyFunc(entry->object);
        }
    }
}