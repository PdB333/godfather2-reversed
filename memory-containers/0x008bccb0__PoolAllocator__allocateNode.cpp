// FUNC_NAME: PoolAllocator::allocateNode
int __fastcall PoolAllocator::allocateNode(int* this)
{
    // this[0] = pointer to pool buffer (base)
    // this[1] = current number of allocated nodes (count)
    // this[2] = capacity (max nodes before resize)
    int capacity = this[2];
    if (this[1] == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Reallocate pool to new capacity (each node 0x2c bytes)
        FUN_008bc950(newCapacity);
    }

    // Pointer to the next free slot (at index this[1])
    uint8_t* node = (uint8_t*)(this[1] * 0x2c + this[0]);
    if (node != nullptr) {
        // Debug fill pattern for memory tracking
        *(uint32_t*)(node + 0x18) = 0xbadbadba;     // +0x18
        *(uint32_t*)(node + 0x1c) = 0xbeefbeef;     // +0x1c
        *(uint32_t*)(node + 0x20) = 0xeac15a55;     // +0x20
        *(uint32_t*)(node + 0x24) = 0x91100911;     // +0x24
        *(uint8_t*)(node + 0x28) = 1;               // +0x28
        *(uint8_t*)(node + 0x29) = 0;               // +0x29
        // Clear first 24 bytes (three quadwords)
        *(uint64_t*)(node) = 0;
        *(uint64_t*)(node + 8) = 0;
        *(uint64_t*)(node + 0x10) = 0;
    }

    int index = this[1];
    this[1] = index + 1;
    return this[0] + index * 0x2c;   // return address of allocated node
}