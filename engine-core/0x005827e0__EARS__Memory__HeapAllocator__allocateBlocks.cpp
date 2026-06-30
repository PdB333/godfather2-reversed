// FUNC_NAME: EARS::Memory::HeapAllocator::allocateBlocks
// Function address: 0x005827e0
// Allocates two memory regions: a block of count*4 bytes and a 16-byte header,
// then combines them via FUN_00582620.

typedef void* (__thiscall *AllocFunc)(void* self, int size, void* hint);

void* __thiscall HeapAllocator::allocateBlocks(int count) {
    // First allocation hint: 4-byte zero struct
    struct FirstHint { int zero; };
    FirstHint firstHint;
    firstHint.zero = 0;

    // Second allocation hint: 16-byte zero struct
    struct SecondHint { int a; int b; int c; int d; };
    SecondHint secondHint;
    secondHint.a = 0; secondHint.b = 0; secondHint.c = 0; secondHint.d = 0;

    // Get vtable
    void** vtable = *(void***)this;
    AllocFunc allocFunc1 = (AllocFunc)vtable[0]; // e.g., allocateRaw
    AllocFunc allocFunc2 = (AllocFunc)vtable[1]; // e.g., allocateHeader

    // Allocate the main block
    void* mainBlock = allocFunc1(this, count * 4, &firstHint);

    // Allocate header (16 bytes)
    int success = (int)allocFunc2(this, 0x10, &secondHint);

    if (success != 0) {
        // Combine mainBlock and header (or this) into final pointer
        return FUN_00582620(mainBlock, this);
    }
    return 0;
}