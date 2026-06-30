// FUNC_NAME: ObjectPool::initialize (address 0x005e4450)
// Role: Initializes an object pool with a free-list index array and a large buffer of 64 slots.
// The pool uses an external allocator interface (vtable-based) to allocate its buffer.
// Offsets: this+0x10 main data (0x6000 bytes), this+0x24 free-list array (512 x 12 bytes),
//          this+0x6010 allocator pointer, this+0x603c pool buffer pointer.
// Buffer: 64 rows of 0x3a0 bytes each, each row has 8 fields initialized to a constant.

int __thiscall ObjectPool::initialize(int* allocatorInterface)
{
    if (allocatorInterface == nullptr) {
        return 0;
    }

    // Store allocator interface pointer
    this->m_allocator = allocatorInterface; // +0x6010

    // Call virtual function at vtable offset 8 (third entry, likely reset/prepare)
    ((void (*)(void))(*allocatorInterface)[2])();

    // Clear the main data area (size 0x6000)
    memset(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + 0x10), 0, 0x6000);

    // Initialize free-list index array at offset 0x24
    // 512 entries, each 12 bytes (stored as uint32 at entry start, rest padding)
    uint32_t* freeList = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x24);
    for (uint32_t i = 0; i < 0x200; i++) {
        *freeList = i;
        freeList += 3; // Advance 12 bytes (3 * sizeof(uint32))
    }

    // Stack variable for allocation alignment hint (unused in this context)
    uint32_t alignmentHint[3] = {0, 0, 0};

    // Allocate the pool buffer via allocator's first virtual function (vtable[0])
    void* poolBuffer = reinterpret_cast<void* (*)(uint32_t, void*)>(
        reinterpret_cast<void**>(*allocatorInterface)[0])(
            0xe800, &alignmentHint);

    if (poolBuffer == nullptr) {
        return 0;
    }

    // Store pool buffer pointer
    this->m_poolBuffer = poolBuffer; // +0x603c

    // Zero the entire pool buffer
    memset(poolBuffer, 0, 0xe800);

    // Initialize 64 rows of 0x3a0 bytes each with constant value
    uint32_t constantValue = DAT_00e2b1a4; // Replace with actual constant
    for (uint32_t row = 0; row < 0xe800; row += 0x3a0) {
        uint8_t* base = reinterpret_cast<uint8_t*>(poolBuffer) + row;
        *reinterpret_cast<uint32_t*>(base + 0x54)  = constantValue;
        *reinterpret_cast<uint32_t*>(base + 0xC8)  = constantValue; // offset 200 decimal
        *reinterpret_cast<uint32_t*>(base + 0x13C) = constantValue;
        *reinterpret_cast<uint32_t*>(base + 0x1B0) = constantValue;
        *reinterpret_cast<uint32_t*>(base + 0x224) = constantValue;
        *reinterpret_cast<uint32_t*>(base + 0x298) = constantValue;
        *reinterpret_cast<uint32_t*>(base + 0x30C) = constantValue;
        *reinterpret_cast<uint32_t*>(base + 0x380) = constantValue;
    }

    return 1;
}