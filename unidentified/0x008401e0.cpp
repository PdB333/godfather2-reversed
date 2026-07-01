// FUN_008401e0: allocateObjectWithVtable
// This function allocates memory for an object, initializes its vtable pointer,
// calls a constructor, and returns a pointer to the object data (offset +4).
// Used by many constructors in the EA EARS engine for custom memory management.
// param_1: additional size offset (base allocation size is 0x10)
// param_2: pointer to class metadata structure (contains allocator and constructor pointers)
undefined4* allocateObjectWithVtable(int param_1, int* param_2)
{
    // Allocation request descriptor used by the engine's memory manager
    int allocType = 2;   // +0x00: allocation type (e.g., object pool)
    int baseSize  = 0x10; // +0x04: base allocation size
    int allocFlags = 0;   // +0x08: flags (alignment, etc.)

    // Fetch the allocator function from the metadata.
    // The metadata structure is accessed through param_2:
    //   *param_2 = pointer to an array of function pointers (vtable-like)
    //   [0] = allocator function, [2] = constructor function (offset 8)
    void* (*allocFunc)(int, int*) = (void* (*)(int, int*))(*param_2);

    // Allocate memory with size = param_1 + 0x10 (base + extra)
    undefined4* mem = (undefined4*)allocFunc(param_1 + 0x10, &allocType);

    // Store the class metadata pointer at the start of allocated memory
    *mem = param_2;

    // Retrieve and call the constructor function from metadata[2]
    void (*ctorFunc)() = *(void (**)())(*param_2 + 8);
    ctorFunc();

    // Return pointer to the object's base (after the stored metadata pointer)
    return mem + 4;
}