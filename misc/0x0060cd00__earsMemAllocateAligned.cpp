// FUNC_NAME: earsMemAllocateAligned
// Function at 0x0060cd00: Custom aligned memory allocator with header tracking.
// Uses a global heap manager (with vtable at 0x2c for allocate, 0x30 for release)
// and a global allocation header pool (DAT_0120584c).
// Input: size (param_3), alignment offset (param_2), and flags via registers.
// Returns aligned pointer or 0 on failure.

struct AllocHeader {
    uint32_t flag;          // +0x00
    uint32_t kind;          // +0x04
    uint32_t ebp;           // +0x08
    int32_t edi;            // +0x0C
    size_t size;            // +0x10
    uint32_t alignPad;      // +0x14
    int32_t param3;         // +0x18
    uint32_t ebx;           // +0x1C
    uint32_t retAddr;       // +0x20
};

extern AllocHeader* gAllocHeaderPtr;   // DAT_0120584c
extern uint32_t gWatermark;            // DAT_01205844
extern void* gHeapManager;             // DAT_01205840

uint32_t earsMemAllocateAligned(int32_t param1, int32_t param2, int32_t param3, int32_t param4)
{
    int32_t size = param3;
    int32_t align = param4;

    // If param3 is not INT_MIN, use param2 as size (?!)
    if (param3 != -0x80000000) {
        align = param2;
    }

    // Calculate aligned block size: ((align * edi + 0xF) >> 4) + 1) * 0x10
    // edi is stored in the caller's register (used as alignment factor?)
    uint32_t blockSize = (((align * gSavedEdi + 0xF) >> 4) + 1) * 0x10;

    uint32_t allocFlags = 0x1000;
    if (gWatermark < blockSize) {
        // If block is larger than remaining watermark, reset and use larger flags
        allocFlags = 0x2000;
        gWatermark = 0;
    }

    param3 = 0;
    // Call virtual allocate on heap manager (vtable+0x2c)
    int32_t result = (*(int32_t (**)(int32_t, uint32_t, uint32_t, int32_t*))
                     (*(int32_t*)gHeapManager + 0x2c))
                    ((int32_t*)gHeapManager, gWatermark, blockSize, &param3);

    if (result < 0) {
        return 0;
    }

    if (!IsBadWritePtr(gSavedEsi, blockSize)) {
        gAllocHeaderPtr->kind = allocFlags;
        gAllocHeaderPtr->ebp = gSavedEbp;
        uint32_t alignedAddr = ((uint32_t)gSavedEsi + 0xF) & ~0xF;
        gAllocHeaderPtr->size = blockSize;
        gAllocHeaderPtr->edi = gSavedEdi;
        gAllocHeaderPtr->alignPad = alignedAddr - (uint32_t)gSavedEsi;
        gAllocHeaderPtr->ebx = gSavedEbx;
        gAllocHeaderPtr->param3 = size;
        gAllocHeaderPtr->retAddr = gSavedRetAddr;
        gAllocHeaderPtr->flag = 1;
        return alignedAddr;
    }

    // If write fails, call virtual release (vtable+0x30)
    (*(void (**)(int32_t*))(*(int32_t*)gHeapManager + 0x30))((int32_t*)gHeapManager);
    return 0;
}