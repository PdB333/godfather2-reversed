// FUNC_NAME: ObjectManager::allocateObjectArray
void ObjectManager::allocateObjectArray()
{
    // Calculate total size: (byte at this+0x1c + 12) * 20
    int objectCount = *(byte *)(this + 0x1c); // +0x1c: number of objects to allocate
    int totalSize = (objectCount + 0xc) * 0x14; // each object is 20 bytes, plus 12 extra? Or index offset?

    // Allocation parameters: (alignment=2, size=0x10, flags=0)
    struct AllocParams {
        int alignment; // 2
        int size;      // 0x10 (16)
        int flags;     // 0
    } params = {2, 0x10, 0};

    // Call global memory allocator function pointer
    int (__cdecl *allocFunc)(int size, AllocParams *params) = (int (__cdecl *)(int, AllocParams*))DAT_01194538;
    int allocatedPtr = allocFunc(totalSize, &params);

    if (allocatedPtr == 0) {
        return; // allocation failed
    }

    // Initialize the allocated objects (or this object's internal data)
    FUN_0051a360(this);
}