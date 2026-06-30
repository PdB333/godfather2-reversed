// FUNC_NAME: PoolObject::~PoolObject

// Likely destructor for an object managed by a global pool at DAT_01206880.
// The vtable pointer is set to &PTR_FUN_00e37110.
// If this->unusedNext (offset 0x10) is non-null, the node is returned to the free list.
// param_2: bit0 indicates whether to free the memory via operator delete (FUN_009c8eb0).

class PoolObject {
public:
    void* vtable;           // +0x00
    char pad_04[0x0C];      // +0x04
    int* unusedNext;        // +0x10 (offset 0x10 = param_1[4])
    int* unusedPrev;        // +0x14 (offset 0x14 = param_1[5])

    // Destructor
    void __thiscall ~PoolObject(byte freeMemoryFlag) {
        // Set vtable to base class vtable
        this->vtable = &PTR_FUN_00e37110;

        int* node = this->unusedNext;  // offset 0x10
        if (node != nullptr) {
            // Access global pool manager: DAT_01206880 + 0x14
            int** poolFreeList = reinterpret_cast<int**>(DAT_01206880 + 0x14);
            // Advance free list pointer (maybe a pool slot pointer)
            *poolFreeList = reinterpret_cast<int*>(&PTR_LAB_01123be8);
            *poolFreeList = *poolFreeList + 4; // increment by 4 bytes
            // Store the node address into the free list slot
            **poolFreeList = reinterpret_cast<int>(node);
            *poolFreeList = *poolFreeList + 4; // increment again

            // Clear the node references
            this->unusedNext = nullptr;
            this->unusedPrev = nullptr;
        }

        // If freeMemoryFlag has bit0 set, call operator delete on this object
        if ((freeMemoryFlag & 1) != 0) {
            FUN_009c8eb0(this);
        }
    }
};