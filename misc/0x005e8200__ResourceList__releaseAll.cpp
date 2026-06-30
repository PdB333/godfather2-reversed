// FUNC_NAME: ResourceList::releaseAll
// Reconstructed cleanup function iterating over 5 entries (each 16 bytes) with object pointer at +0x00 and destructor function pointer at +0x0C.
// Used to release allocated resources.
struct ResourceEntry {
    void* objectPtr;  // +0x00
    // +0x04 unknown, possibly padding
    // +0x08 unknown
    void (*destructor)(void*); // +0x0C
};

class ResourceList {
public:
    ResourceEntry entries[5]; // total 80 bytes (0x50)
    
    __thiscall void releaseAll() {
        // Entry at offset 0x40 (entries[4])
        if (entries[4].objectPtr != nullptr) {
            entries[4].destructor(entries[4].objectPtr);
        }
        // Entry at offset 0x30 (entries[3])
        if (entries[3].objectPtr != nullptr) {
            entries[3].destructor(entries[3].objectPtr);
        }
        // Entry at offset 0x20 (entries[2])
        if (entries[2].objectPtr != nullptr) {
            entries[2].destructor(entries[2].objectPtr);
        }
        // Entry at offset 0x10 (entries[1])
        if (entries[1].objectPtr != nullptr) {
            entries[1].destructor(entries[1].objectPtr);
        }
        // Entry at offset 0x00 (entries[0])
        if (entries[0].objectPtr != nullptr) {
            entries[0].destructor(entries[0].objectPtr);
        }
    }
};