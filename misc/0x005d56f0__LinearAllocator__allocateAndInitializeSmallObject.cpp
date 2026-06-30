// FUNC_NAME: LinearAllocator::allocateAndInitializeSmallObject
// Address: 0x005d56f0
// This function allocates a small object from a linear bump allocator, initializes its vtable, and stores three fields.
// The allocator is a global structure (likely singleton) at DAT_01206880.
// +0x14 is the current allocation pointer (bump pointer).

// Global allocator pointer
extern uint8_t* gLinearAllocatorBase; // DAT_01206880, points to a struct with bump pointer at +0x14

// Vtable for the small object being allocated
extern void* gSmallObjectVtable; // PTR_LAB_01126c30

// The function takes a value to store as the first field after vtable (possibly size/ID)
void __fastcall allocAndInitSmallObject(uint initValue) {
    uint8_t* allocator = gLinearAllocatorBase;
    uint8_t* bumpPtr = *(uint8_t**)(allocator + 0x14); // current bump pointer
    
    // Set vtable at object start
    *(void**)bumpPtr = gSmallObjectVtable;
    bumpPtr += 4;
    *(uint8_t**)(allocator + 0x14) = bumpPtr;
    
    // Align bump pointer to next 4-byte boundary
    uint8_t* aligned1 = (uint8_t*)(((uint32_t)bumpPtr + 3) & ~3);
    *(uint8_t**)(allocator + 0x14) = aligned1;
    *(uint32_t*)aligned1 = initValue;
    
    // Align again and store value 1
    uint8_t* aligned2 = (uint8_t*)(((uint32_t)aligned1 + 7) & ~3);
    *(uint8_t**)(allocator + 0x14) = aligned2;
    *(uint32_t*)aligned2 = 1;
    
    // Align again and store value 1
    uint8_t* aligned3 = (uint8_t*)(((uint32_t)aligned2 + 7) & ~3);
    *(uint8_t**)(allocator + 0x14) = aligned3;
    *(uint32_t*)aligned3 = 1;
    
    // Advance bump pointer by 4 for next allocation
    *(uint8_t**)(allocator + 0x14) = aligned3 + 4;
}