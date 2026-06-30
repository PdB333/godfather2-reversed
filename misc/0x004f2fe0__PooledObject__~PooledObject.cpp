// FUNC_NAME: PooledObject::~PooledObject
// Address: 0x004f2fe0
// Role: Destructor that returns the object to a pool and optionally frees memory.
// The pool is a simple stack-based allocator where each slot is 8 bytes.
// The global pool head pointer is at DAT_01206880 + 0x14.
// The object's link field at offset 0x10 is saved to the pool, then cleared.

void __thiscall PooledObject::~PooledObject(byte freeMemory) {
    // Update vtable to a custom one (likely for use-after-free detection)
    this->vtable = &PTR_FUN_00e37110; // +0x00

    int* poolNode = this->link; // +0x10, pointer to a pool node (handle)
    if (poolNode != 0) {
        // Get the pool head pointer (points to next free slot)
        int* poolHead = (int*)(DAT_01206880 + 0x14); // global pool head

        // Push the node onto the pool:
        // Each slot: first 4 bytes = sentinel (vtable), next 4 bytes = data (node pointer)
        *(undefined***)*poolHead = &PTR_LAB_01123be8; // sentinel
        *poolHead = *poolHead + 4;                     // advance to data part
        *(int*)*poolHead = poolNode;                   // store the node pointer
        *poolHead = *poolHead + 4;                     // advance to next slot

        // Clear the object's link fields
        this->link = 0;   // +0x10
        this->link2 = 0;  // +0x14
    }

    // If bit 0 is set, free the memory
    if ((freeMemory & 1) != 0) {
        FUN_009c8eb0(this); // likely operator delete
    }

    return this;
}