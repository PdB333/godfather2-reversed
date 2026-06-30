// FUNC_NAME: PacketPool::allocatePacket

#include <stdint.h>

struct Packet {
    // offsets from base (4-byte aligned)
    uint32_t unknown[7];   // +0x00 to +0x1b
    uint8_t  channel;      // +0x1c
    uint8_t  slot;         // +0x1d
    uint8_t  flags;        // +0x1e
    uint8_t  padding;      // +0x1f
    void*    buffer;       // +0x20 - pointer to data buffer
    uint32_t bufferSize;   // +0x24
    uint32_t field28;      // +0x28
    uint32_t field2C;      // +0x2c
};

struct PoolManager {
    // +0x00: unknown
    // +0x04: unknown
    void*    freeListHead; // +0x08
    int32_t  createParam1; // +0x0c
    int32_t  createParam2; // +0x10
    int32_t  freeCount;    // +0x14
    int32_t  lowWatermark; // +0x18
    void*    allocator;    // +0x1c - points to an object with a vtable
};

// Global base address for the packet pool structure
// The structure contains:
//   +0x00: 8 channel bitmap entries, each 2 uint32 (8 bytes)
//   +0x40: ... (other data)
//   +0x90: PoolManager* manager
//   +0x94: uint32* bufferTable[8][64] - array of pointers to fixed-size buffers
#define G_PACKET_POOL_BASE (*(uint8_t**)0x0120550c)

// Helper: find first zero bit in a 64-bit value, returns index (0-63)
int32_t findFirstZeroBit(uint32_t low, uint32_t high); // FUN_00505ce0

Packet* PacketPool::allocatePacket() {
    uint8_t* poolBase = G_PACKET_POOL_BASE;
    PoolManager* manager = *(PoolManager**)(poolBase + 0x90);
    Packet* packet;

    // Try to reuse a packet from the free list
    packet = (Packet*)manager->freeListHead;
    if (packet != nullptr) {
        manager->freeListHead = *(void**)packet; // first word is next pointer
        manager->freeCount--;
        if ((uint32_t)manager->freeCount < (uint32_t)manager->lowWatermark) {
            manager->lowWatermark = manager->freeCount;
        }
    } else {
        // No free packets, need to create a new one
        if (manager->allocator == nullptr) {
            return nullptr;
        }
        // Call allocator method at vtable offset 4
        // Parameters: manager->createParam1, manager->createParam2
        void* allocatorObj = manager->allocator;
        void* (__thiscall *createFunc)(void*, int32_t, int32_t) =
            *(void* (__thiscall**)(void*, int32_t, int32_t))allocatorObj;
        packet = (Packet*)createFunc(allocatorObj, manager->createParam1, manager->createParam2);
    }

    if (packet != nullptr) {
        // Find a free channel/slot from the 8-channel bitmap
        int32_t channelIndex;
        for (channelIndex = 0; channelIndex < 8; channelIndex++) {
            uint32_t* bitmapEntry = (uint32_t*)(poolBase + channelIndex * 8);
            uint32_t low = bitmapEntry[0];
            uint32_t high = bitmapEntry[1];
            if ((low & high) != 0xFFFFFFFF) {
                // At least one zero bit => free slot exists
                int32_t bitIndex = findFirstZeroBit(low, high);

                // Clear the bit (mark slot as allocated)
                uint64_t mask = (uint64_t)1 << bitIndex;
                bitmapEntry[1] = (uint32_t)(mask >> 32) | high;
                bitmapEntry[0] = (uint32_t)mask | low;

                // Store channel and slot info into the packet header
                packet->channel = (uint8_t)channelIndex;
                packet->slot   = (uint8_t)bitIndex;
                packet->flags  = 0;

                // Set buffer pointer from the pre-allocated buffer table
                // Table: poolBase + 0x94, indexed by (channelIndex * 64 + bitIndex)
                packet->buffer = *(void**)(poolBase + 0x94 + (channelIndex * 0x40 + bitIndex) * 4);
                packet->bufferSize = 0;
                packet->field28 = 0;
                packet->field2C = 0;

                break;
            }
        }
    }

    return packet;
}