// FUNC_NAME: ObjectAllocator::allocateObject
// Function address: 0x006293c0
// Role: Allocate or assign an object; if input is 0, create new from internal pool; else reuse.
int __thiscall ObjectAllocator::allocateObject(int objectOrSize)
{
    int allocBlock[3]; // stack buffer for allocation info
    if (objectOrSize == 0)
    {
        // Compute pointer to allocation block from internal offset
        // Offset +0x08 points to some linked list or pool head minus 8 bytes header?
        allocBlock[0] = *(int *)(this + 8) - 8; // adjust for header
        allocBlock[1] = 0xFFFFFFFF; // maybe a sentinel or unused
        // Calculate size needed from offset +0x1c (maybe total block size or remaining)
        int blockSize = allocBlock[0] - *(int *)(this + 0x1c);
        // Call into low-level allocation with vtable pointer LAB_006261e0, the block, and size
        objectOrSize = FUN_00636570(&LAB_006261e0, allocBlock, blockSize);
        if (objectOrSize == 0)
            return 0; // allocation failed
    }
    // Perform initialization after allocation
    FUN_006292e0();
    return objectOrSize;
}