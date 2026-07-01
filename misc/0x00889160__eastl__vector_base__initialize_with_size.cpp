// FUNC_NAME: eastl::vector_base::initialize_with_size
// Address: 0x00889160
// Role: Initializes a vector-like container (3 pointers: begin, end, capacityEnd) by allocating memory for 'capacity' elements of 4 bytes each.
// Uses EASTL allocator with debug file/line info.

int* __thiscall eastl::vector_base::initialize_with_size(int* thisPtr, int capacity)
{
    if (capacity != 0) {
        // Allocate memory for capacity elements (each 4 bytes). The allocator is called with debug source file/line.
        int* allocBase = (int*)FUN_0068ab90(capacity * 4, "EASTL", 0, 0,
                                            "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);
        thisPtr[0] = (int)allocBase;          // +0x00: begin pointer
        thisPtr[1] = (int)allocBase;          // +0x04: end pointer (initially equals begin)
        thisPtr[2] = (int)(allocBase + capacity); // +0x08: capacity end pointer
        return thisPtr;
    }
    // Zero capacity: null out all pointers.
    thisPtr[0] = 0;
    thisPtr[1] = 0;
    thisPtr[2] = 0;
    return thisPtr;
}