// FUNC_NAME: allocateAndConstructObject
// Function at 0x00830910: Allocates memory via custom allocator and constructs an object.
// The allocator is obtained from a global singleton (FUN_009c8f80) which returns a pointer to an allocator object.
// The allocator's vtable's first function (Allocate) is called with size 0x100 and an allocation descriptor containing:
//   memoryClass = 2 (likely heap/pool class)
//   alignment = 0x10
//   flags = 0
// If allocation succeeds, the constructor at 0x008307f0 is called on the allocated memory, and the constructed object's pointer is returned.
// On failure, returns 0.

// Undefined types for forward declarations
typedef int (__thiscall *AllocatorAllocateFunc)(void* allocator, uint size, void* descriptor);
typedef void* (__thiscall *ObjectConstructorFunc)(void* memory);

// Global allocator singleton
void* GetAllocator(void); // 0x009c8f80

// Constructor for the target object (size 0x100)
void* ConstructObject(void* memory); // 0x008307f0

// Allocation descriptor layout (size, alignment, flags)
struct AllocDescriptor {
    int memoryClass;   // +0x00
    int alignment;     // +0x04
    int flags;         // +0x08
};

void* allocateAndConstructObject(void)
{
    void* allocator = GetAllocator();               // Get the allocator singleton
    AllocDescriptor desc;
    desc.memoryClass = 2;                           // e.g., heap class 2
    desc.alignment = 0x10;                          // 16-byte alignment
    desc.flags = 0;                                 // no special flags

    // Call allocator's vtable function at offset 0 (Allocate)
    AllocatorAllocateFunc allocFunc = *(AllocatorAllocateFunc*)allocator;
    int allocResult = allocFunc(allocator, 0x100, &desc); // Returns non-zero on success

    if (allocResult != 0) {
        // Allocation succeeded: construct object in the allocated memory
        void* obj = ConstructObject((void*)allocResult); // 0x008307f0
        return obj;
    }

    return 0; // Allocation failed
}