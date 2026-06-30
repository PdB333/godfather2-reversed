// FUNC_NAME: ArrayAllocator::construct
// Address: 0x0071a810
// This function initializes an array allocator object, allocates memory for an array of elements,
// and returns the initialized object.

// Field offsets of the class (assuming size 0x14):
// +0x00: arrayPtr (undefined4*) - pointer to the allocated array memory
// +0x04: flag (int) - set to 0 initially
// +0x08: elementCount (int) - number of elements
// +0x0C: allocHandle (undefined4*) - handle returned from inner allocator (FUN_004265d0)
// +0x10: allocator (int*) - pointer to the allocator object

// The allocator object has a vtable with at least two virtual methods:
// vtable+0x00: Alloc(size, context) -> allocate memory of given size
// vtable+0x08: PostConstruct() -> called after constructing the allocHandle

undefined4* __thiscall ArrayAllocator::construct(undefined4* this, int elementCount, int* allocator, undefined4 allocationTag)
{
    undefined4* allocHandle;
    undefined4* arrayPtr;
    undefined4* context;

    // Step 1: Initialize flags
    this[1] = 0;                  // +0x04: flag = 0
    this[2] = elementCount;       // +0x08: elementCount

    // Step 2: Create an allocator handle from the given allocator and tag
    allocHandle = FUN_004265d0(allocationTag, allocator);  // likely a factory/allocation context
    this[3] = allocHandle;        // +0x0C: store allocHandle

    this[4] = allocator;          // +0x10: store allocator pointer

    // Step 3: Call virtual method at offset 8 on the allocator (PostConstruct)
    (*(code**)(*(int*)allocator + 8))();

    // Step 4: Determine the context for the actual allocation
    context = allocHandle;
    if (context == (undefined4*)0x0) {
        context = &DAT_01218a14;  // fallback to a global default allocator
    }

    // Step 5: Allocate memory: elementCount * 12 bytes using the allocator's vtable[0]
    arrayPtr = (undefined4*)(*(code**)*(int*)allocator)(elementCount * 0xC, context);
    this[0] = arrayPtr;           // +0x00: store the allocated array pointer

    return this;
}