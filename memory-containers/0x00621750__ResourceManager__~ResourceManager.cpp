// FUNC_NAME: ResourceManager::~ResourceManager
// Function at 0x00621750: Destructor for a manager class containing two sub-objects (pools/allocators) and two allocated pointers.
// Offsets:
//  this+0x04: pointer to first sub-object (PoolA) with vtable (has virtual function at offset 4 for deallocation, offset 12 for finalize)
//  this+0x14: pointer to second sub-object (PoolB) with vtable (similar virtual functions)
//  this+0x18: pointer to allocated block 1 (freed via PoolB)
//  this+0x1c: pointer to allocated block 2 (freed via PoolA, size 0x28)
//  this+0x20: another pointer (set to 0)

void __thiscall ResourceManager::~ResourceManager()
{
    // Stack buffer for temporary guard or lock (12 bytes)
    struct ScopedGuard { /* ... */ } guardBuffer;

    // Call initialization/cleanup function with guard buffer and "this"
    // First two args: guardBuffer, this; then dereferences from this+0x1c (twice)
    // Possibly initializes a scope guard for the cleanup operation
    FUN_00622b80(&guardBuffer, this, **(void***)(this + 0x1c), this, *(void**)(this + 0x1c));

    // Free allocated block 2 (at offset 0x1c) using PoolA's deallocation virtual function (vtable entry at offset 4, size 0x28)
    {
        // vtable for PoolA is stored at this+0x04
        void** poolAVtable = *(void***)(this + 0x04);
        // Virtual function at offset 4 (second entry) takes pointer to block and size
        void* block2 = *(void**)(this + 0x1c);
        reinterpret_cast<void(__thiscall*)(void*, int)>(poolAVtable[1])(block2, 0x28);
    }

    // Clear pointers at offsets 0x1c and 0x20
    *(void**)(this + 0x1c) = 0;
    *(void**)(this + 0x20) = 0;

    // If allocated block 1 exists, free it using PoolB's deallocation virtual function
    if (*(void**)(this + 0x18) != 0) {
        void** poolBVtable = *(void***)(this + 0x14);
        void* block1 = *(void**)(this + 0x18);
        reinterpret_cast<void(__thiscall*)(void*, int)>(poolBVtable[1])(block1, 0);
        *(void**)(this + 0x18) = 0;
    }

    // Finalize PoolB by calling virtual function at offset 12 (fourth entry)
    {
        void** poolBVtable = *(void***)(this + 0x14);
        reinterpret_cast<void(__thiscall*)(void*)>(poolBVtable[3])();
    }

    // Global cleanup function
    FUN_00621f30();

    return;
}