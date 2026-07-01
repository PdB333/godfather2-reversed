// FUNC_NAME: PoolAllocator::PoolAllocator
// Address: 0x008f72d0
// Role: Constructor for a fixed-size block memory pool allocator (EA EARS engine).
// Initializes allocator with 26 internal slabs (0x100-byte blocks) and additional
// external pools for large allocations (0x8000 bytes). The loop creates fixed-size
// pools for most size classes except for indices 15, 20, 21, 24 (mask 0x1300800).
// Final calls create pools for 0x40, 0x600, 0x50, and 0x80 byte blocks.

struct PoolAllocator;

// Externally-defined per-instance pools (externally allocated memory blocks)
extern void* bigPool1;   // DAT_012069f4
extern void* bigPool2;   // DAT_012069c4
extern void* bigPool3;   // DAT_012069d4

void setNumPools(int count);               // FUN_008f7260
void registerExternalPool(PoolAllocator* allocator, void** poolPtr, uint size); // FUN_00408900
void createFixedSizePool(uint blockSize);  // FUN_008f6480

class PoolAllocator {
public:
    void** vtable;          // +0x00
    uint field_4;           // +0x04 (initialized to 1)
    uint field_8;           // +0x08 (initialized to 0)
    // ... remaining fields
};

PoolAllocator* __fastcall PoolAllocator::PoolAllocator(PoolAllocator* this) {
    byte index = 0;
    uint offset = 0;

    this->vtable = &PoolAllocator_vtable;   // PTR_FUN_00d8121c
    this->field_4 = 1;
    this->field_8 = 0;

    setNumPools(0x1a);                     // 26 pool sizes

    // Attach any externally pre-allocated large pools
    if (bigPool1 != 0) {
        registerExternalPool(this, &bigPool1, 0x8000);
    }
    if (bigPool2 != 0) {
        registerExternalPool(this, &bigPool2, 0x8000);
    }
    if (bigPool3 != 0) {
        registerExternalPool(this, &bigPool3, 0x8000);
    }

    // Initialize 26 fixed-size pools for 0x100-byte blocks,
    // skipping those where the bitmask has a 1 (indices 15,20,21,24)
    offset = 0;
    do {
        if ((1 << (index & 0x1f) & 0x1300800U) == 0) {
            createFixedSizePool(0x100);
        }
        offset += 0x10;
        index++;
    } while (offset < 0x1a0);

    // Additional pools for different block sizes
    createFixedSizePool(0x40);   // 64 bytes
    createFixedSizePool(0x600);  // 1536 bytes
    createFixedSizePool(0x50);   // 80 bytes
    createFixedSizePool(0x80);   // 128 bytes

    return this;
}