// FUNC_NAME: SomeManager::SomeManager (constructor)
// Address: 0x00727e10
// This appears to be a singleton manager constructor that initializes a large data structure.
// It sets up a vtable, initializes some fields, and optionally loads default data from a static buffer.
// The loop of 4 iterations of FUN_00727cc0(0x40) suggests creating 4 sub-instances or pools of size 0x40.

class SomeManager
{
public:
    // +0x00: vtable pointer
    void **vtable;
    // +0x04: flag: set to 1 (maybe initialized or active)
    int flag1;
    // +0x08: counter or some int (set to 0)
    int counter;
    // +0x0C: pointer to a global table (initially &PTR_LAB_00d62444, then changed to &PTR_LAB_00d62448)
    void *globalTablePtr;
    // +0x10 to +0x3C: zeroed out area (likely other member variables)
    char reserved[0x30]; // from offset 0x10 to 0x3F (0x10 + 0x30 = 0x40)
    // Note: total size at least 0x40 bytes

    // Global singleton pointer (stored in DAT_01129964)
    static SomeManager *s_instance;

    // Constructor
    SomeManager();
};

SomeManager *SomeManager::s_instance = nullptr;

__thiscall SomeManager* SomeManager::SomeManager()
{
    // Set flag to 1 (active?)
    this->flag1 = 1;
    // Initialize counter to 0
    this->counter = 0;
    // Initially point to one global label
    this->globalTablePtr = &PTR_LAB_00d62444;
    // Store this instance in global singleton
    s_instance = this;
    // Set vtable pointer (class-specific vtable)
    this->vtable = &PTR_FUN_00d6244c;
    // Reassign globalTablePtr to another global label
    this->globalTablePtr = &PTR_LAB_00d62448;
    // Zero out reserved memory from offset 0x10 to 0x3C
    this->reserved[0] = 0; // equivalent to loop setting param_1[4] through param_1[0xf] to 0
    // (In practice, the decompiler shows sequential assignments)
    // Copy data from static buffer if available
    if (DAT_012069c4 != 0) {
        // FUN_00408900 likely copies 0x8000 bytes from DAT_012069c4 into this object
        // Note: This may overwrite beyond the declared size; perhaps 'this' is part of a larger allocation
        copyFromBuffer(this, &DAT_012069c4, 0x8000); // memcpy-like
    }
    // Create 4 sub-instances of size 0x40 (each via FUN_00727cc0)
    int count = 4;
    do {
        // FUN_00727cc0 appears to allocate/initialize a sub-object of size 0x40
        initSubObject(0x40);
        count--;
    } while (count != 0);
    return this;
}