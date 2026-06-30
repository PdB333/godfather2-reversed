// FUNC_NAME: MemoryAllocator::allocateAlignedMemory

// Function address: 0x0060cd00
// Role: Custom aligned memory allocation wrapper around a virtual allocator (vtable at 0x01205840).
// Tracks allocation metadata in a global header structure at 0x0120584c.
// Handles alignment to 16 bytes, overflow recovery, and debug validation.

struct AllocationHeader {
    uint32_t flags;           // +0x00: 1 = allocated
    uint32_t allocFlags;      // +0x04: page allocation flags (0x1000 or 0x2000)
    uint32_t ebp;             // +0x08: caller's EBP (stack frame)
    uint32_t sizeMultiplier;  // +0x0C: raw multiplier factor (from EDI)
    uint32_t size;            // +0x10: aligned request size
    uint32_t alignmentOffset; // +0x14: difference between unaligned and aligned address
    uint32_t originalParam3;  // +0x18: original third parameter (or INT_MIN)
    uint32_t ebx;             // +0x1C: caller's EBX
    uint32_t returnAddr;      // +0x20: caller return address (for leak tracking)
};

// Global allocator object pointer (vtable-based)
extern void* g_allocator;          // DAT_01205840
// Global counter of allocated bytes (used for overflow detection)
extern uint32_t g_allocatedBytes;  // DAT_01205844
// Global pointer to the current allocation header (used for tracking)
extern AllocationHeader* g_currentHeader; // DAT_0120584c

uint32_t MemoryAllocator::allocateAlignedMemory(
    uint32_t param1,      // unknown context (could be thread ID or flags)
    int32_t param2,       // base size factor
    int32_t param3,       // optional multiplier (or INT_MIN)
    int32_t param4        // secondary size factor
)
{
    int32_t sizeFactor;
    int32_t secondFactor;
    uint32_t alignedSize;
    uint32_t pageAllocFlags = 0x1000; // MEM_COMMIT (Windows)
    int32_t allocationResult; // result from virtual allocator
    BOOL writeableCheck;

    // Determine which parameter is the "size" depending on param3 == INT_MIN
    if (param3 == INT_MIN) {
        // param3 is special marker: use param4 as second factor, param2 as first
        sizeFactor = param2;
        secondFactor = param4;
    } else {
        // param3 is not marker: use param3 as sizeFactor, param2 as multiplier? Actually param_2 is used as secondFactor?
        // From decompile: iVar3 = param_4; iVar2 = param_3; if param_3 != -0x80000000 then iVar3 = param_2
        // This seems swapped? Let's follow decompile precisely.
        sizeFactor = param3;
        secondFactor = param2; // because param_2 becomes iVar3 when param_3 != INT_MIN
    }
    // unaff_EDI is a register passed from caller, acts as a multiplier
    // Typically will be something like sizeof(thing) or alignment constant.
    // Let's call it baseMultiplier.
    uint32_t baseMultiplier = /* value from EDI */;
    // Compute aligned request size: ((sizeFactor * baseMultiplier + 0xF) >> 4 + 1) << 4
    alignedSize = ((sizeFactor * baseMultiplier + 0xF) >> 4) + 1;
    alignedSize <<= 4; // align to 16 bytes

    // Check for overflow: if requested bytes > remaining capacity (1MB - g_allocatedBytes)
    if (alignedSize > 0x100000 - g_allocatedBytes) {
        // Overflow: increase allocation flag to 0x2000 (MEM_RESERVE?) and reset counter
        pageAllocFlags = 0x2000;
        g_allocatedBytes = 0;
    }

    // Call the virtual allocator's function at vtable offset 0x2c (likely VirtualAlloc or similar)
    // The allocator object is at *g_allocator (deref for vtable pointer)
    // We pass g_allocatedBytes as the base address hint, alignedSize, and a pointer to store result.
    int32_t temp = 0; // param_3 in original, used as out param for success?
    allocationResult = (*(int32_t (__stdcall**)(void*, uint32_t, uint32_t, int32_t*))
        (*(int**)*g_allocator + 0x2c))(g_allocator, g_allocatedBytes, alignedSize, &temp);

    if (allocationResult < 0) {
        // Allocation failed
        return 0;
    }

    // Debug check: verify the returned address is writable
    // unaff_ESI holds a base pointer (possibly the returned allocation address before alignment)
    LPVOID rawAddress = /* value from ESI */;
    writeableCheck = IsBadWritePtr(rawAddress, alignedSize);
    if (writeableCheck != 0) {
        // Address is bad; free it via vtable offset 0x30
        (*(void (__stdcall**)(void*))(*(int**)*g_allocator + 0x30))(g_allocator);
        return 0;
    }

    // Fill allocation header at g_currentHeader
    AllocationHeader* header = g_currentHeader;
    header->flags = 1;                     // allocated
    header->allocFlags = pageAllocFlags;   // MEM flags
    header->ebp = /* unaff_EBP */;        // caller's EBP
    header->sizeMultiplier = baseMultiplier;
    header->size = alignedSize;
    // Alignment offset: how much was added to align to 16 bytes
    header->alignmentOffset = ((uint32_t)rawAddress + 0xF) & 0xFFFFFFF0) - (uint32_t)rawAddress;
    header->originalParam3 = param3;
    header->ebx = /* unaff_EBX */;        // caller's EBX
    header->returnAddr = /* unaff_retaddr */; // return address for tracking

    // Return the aligned address
    return ((uint32_t)rawAddress + 0xF) & 0xFFFFFFF0;
}