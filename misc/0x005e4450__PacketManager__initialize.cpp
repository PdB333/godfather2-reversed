// FUNC_NAME: PacketManager::initialize
// Address: 0x005e4450
// Role: Initializes packet slot table and buffer pool for network packet management.
// Called from FUN_005e33e0 (likely PacketManager constructor or init).

#include <cstring> // for memset

// Constants derived from the decompiled code
const uint32_t kSlotCount = 512;          // 0x200
const uint32_t kSlotStride = 12;          // 0xC
const uint32_t kBufferSize = 0xE800;      // 59392 bytes
const uint32_t kBlockCount = 64;          // 0xE800 / 0x3A0
const uint32_t kBlockSize = 0x3A0;        // 928 bytes per block
const uint32_t kDefaultValue = DAT_00e2b1a4; // Placeholder for the constant value

// Structure for a single slot in the handle table (at this+0x24)
struct SlotEntry {
    uint32_t index;   // +0x00
    uint8_t  pad[8];  // +0x04 to +0x0B (total 12 bytes)
};

// Structure for a single buffer block (allocated buffer)
struct BufferBlock {
    uint32_t field0;  // +0x54
    uint32_t field1;  // +0xC8
    uint32_t field2;  // +0x13C
    uint32_t field3;  // +0x1B0
    uint32_t field4;  // +0x224
    uint32_t field5;  // +0x298
    uint32_t field6;  // +0x30C
    uint32_t field7;  // +0x380
    // Remaining bytes (0x3A0 - 0x384 = 0x1C) are unused/padding
};

// Forward declaration of the allocator interface (vtable-based)
struct IAllocator {
    virtual void* allocate(uint32_t size, void* alignmentInfo) = 0; // vtable[0]
    virtual void  init() = 0;                                        // vtable[8]
};

// The PacketManager class (inferred from offsets)
class PacketManager {
public:
    // Member offsets (relative to this)
    // +0x10: uint8_t slotTable[0x6000]  (contains SlotEntry array at +0x24)
    // +0x6010: IAllocator* allocator
    // +0x603C: BufferBlock* bufferPool

    int __fastcall initialize(IAllocator* allocator);
};

int __fastcall PacketManager::initialize(IAllocator* allocator) {
    if (allocator == nullptr) {
        return 0;
    }

    // Store the allocator pointer
    this->allocator = allocator; // +0x6010

    // Call the allocator's init method (vtable offset 8)
    allocator->init();

    // Zero out the slot table (0x6000 bytes starting at +0x10)
    memset(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + 0x10), 0, 0x6000);

    // Initialize the slot entry array at +0x24
    // Each entry is 12 bytes, first field is the index (0..511)
    uint32_t* slotPtr = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x24);
    for (uint32_t i = 0; i < kSlotCount; ++i) {
        *slotPtr = i;
        slotPtr += kSlotStride / sizeof(uint32_t); // advance 12 bytes (3 uint32s)
    }

    // Allocate the buffer pool (size 0xE800) via the allocator's allocate method
    // The third parameter (stack struct) is likely alignment info; we pass a dummy
    uint32_t alignmentInfo[3] = {0, 0, 0};
    void* buffer = allocator->allocate(kBufferSize, alignmentInfo);
    this->bufferPool = static_cast<BufferBlock*>(buffer); // +0x603C

    if (buffer == nullptr) {
        return 0;
    }

    // Zero out the entire buffer
    memset(buffer, 0, kBufferSize);

    // Initialize each block's 8 fields to the default value
    BufferBlock* block = this->bufferPool;
    for (uint32_t i = 0; i < kBlockCount; ++i) {
        block->field0 = kDefaultValue;
        block->field1 = kDefaultValue;
        block->field2 = kDefaultValue;
        block->field3 = kDefaultValue;
        block->field4 = kDefaultValue;
        block->field5 = kDefaultValue;
        block->field6 = kDefaultValue;
        block->field7 = kDefaultValue;
        // Advance to next block (size 0x3A0)
        block = reinterpret_cast<BufferBlock*>(reinterpret_cast<uintptr_t>(block) + kBlockSize);
    }

    return 1;
}