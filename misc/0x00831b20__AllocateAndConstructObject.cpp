// FUNC_NAME: AllocateAndConstructObject
typedef struct {
    unsigned int alignmentExp; // +0x00 exponent for 2^alignment
    unsigned int flags;        // +0x04 allocation flags (e.g., pool ID)
    unsigned int debugTag;     // +0x08 debug label or 0
} AllocInfo;

// Allocate memory and construct an object of size 0xD0 (208 bytes)
// Uses a singleton allocator obtained via FUN_009c8f80 (likely IMemoryManager*)
unsigned int AllocateAndConstructObject(void) {
    // Get the global allocator (e.g., EARS::Memory::Allocator*)
    unsigned int* vtablePtr = (unsigned int*)FUN_009c8f80();
    
    AllocInfo allocInfo;
    allocInfo.alignmentExp = 2;   // 4-byte alignment
    allocInfo.flags = 0x10;       // e.g., kAllocFlagNoWrap
    allocInfo.debugTag = 0;       // no debug name

    // Call virtual function at vtable index 0 (allocate memory)
    // Signature: void* (__thiscall*)(void* this, unsigned int size, AllocInfo* info)
    typedef void* (__thiscall* AllocFunc)(void*, unsigned int, AllocInfo*);
    AllocFunc allocFunc = (AllocFunc) * (void**)*vtablePtr;
    void* mem = allocFunc(vtablePtr, 0xD0, &allocInfo);

    if (mem) {
        // Construct the object (FUN_0082cda0 likely a constructor returning pointer)
        unsigned int result = FUN_0082cda0();
        return result;
    }
    return 0;
}