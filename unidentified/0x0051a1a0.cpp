// FUN_0051a1a0: HeapAllocator::allocate
// Address: 0x0051a1a0
// Function: Attempts to allocate a block from a heap pool using a global function table.
//          On success, calls further initialization on the object (FUN_0051a360).
//          Uses a byte field at +0x1c to compute an allocation index/size.

struct AllocParams {
    int type;       // 0x00: e.g., 2 = persistent heap?
    int alignment;  // 0x04: e.g., 0x10 = 16-byte alignment
    int flags;      // 0x08: e.g., 0 = none
};

// Global pointer to a function table (likely a vtable or allocator dispatch table)
extern void* g_pAllocVtable; // DAT_01194538

// Internal init function called after successful allocation (address 0x0051a360)
extern void heapAllocInit(HeapAllocator* thisObj);

// __thiscall: 'this' passed in ECX, but decompiler shows in_EAX (register confusion)
// We assume the object pointer is the first (implicit) parameter.
void __thiscall HeapAllocator::allocate(HeapAllocator* thisObj)
{
    int allocResult;
    AllocParams params;
    
    params.type = 2;          // allocation type (e.g., heap slot index)
    params.alignment = 0x10;  // requested alignment
    params.flags = 0;         // no special flags

    // Compute allocation key from object's byte field at +0x1c:
    // (field_1C + 12) * 20 — likely an index into a free list or a block size.
    int allocIndex = (*(unsigned char*)((char*)thisObj + 0x1c) + 0xC) * 0x14;

    // Call through global function pointer table: first entry?
    allocResult = ((int (*)(int, AllocParams*))(*g_pAllocVtable))(allocIndex, &params);
    
    if (allocResult == 0) {
        return;  // allocation failed
    }

    // Allocation succeeded – perform further initialization
    heapAllocInit(thisObj);
}