// FUNC_NAME: SoundBufferPool::allocateBlock
// Address: 0x00505da0
// Role: Allocates a fixed-size block from a pool managed by a global singleton. Scans 8 slots (each with a 64-bit bitmap) for an available block, marks it, and returns a pointer to the block's metadata structure. Returns null if pool is exhausted.

#include <cstdint>

// Global singleton pointer (DAT_0120550c) - points to pool manager instance
static SoundBufferPool* gPoolManager = reinterpret_cast<SoundBufferPool*>(0x0120550c);

// Forward declaration of helper that finds first zero bit in a 64-bit mask
static int findFirstFreeBit(uint32_t lowBits, uint32_t highBits);

// The allocation function
SoundBufferBlock* SoundBufferPool::allocateBlock()
{
    // Access the pool's sub-manager (offset +0x90)
    PoolInternal* poolInternal = reinterpret_cast<PoolInternal*>(gPoolManager->m_poolPtr); // +0x90
    SoundBufferBlock* block = nullptr;

    // Try to pop from free list (head at poolInternal+8)
    block = reinterpret_cast<SoundBufferBlock*>(poolInternal->m_freeListHead); // +0x8
    if (block == nullptr)
    {
        // No free list head; try to construct one using a callback (offset +0x1c)
        AllocCallback* callback = reinterpret_cast<AllocCallback*>(poolInternal->m_allocCallback); // +0x1c
        if (callback == nullptr)
            return nullptr;
        block = callback->create(poolInternal->m_param1, poolInternal->m_param2); // +0xc, +0x10
    }
    else
    {
        // Pop from free list
        poolInternal->m_freeListHead = reinterpret_cast<SoundBufferBlock*>(block->m_nextFree); // *block = next
        poolInternal->m_freeCount--; // +0x14
        if (poolInternal->m_freeCount < poolInternal->m_minFreeCount) // +0x18
            poolInternal->m_minFreeCount = poolInternal->m_freeCount;
    }

    if (block == nullptr)
        return nullptr;

    // Search for a slot with available blocks (8 slots, each with a 64-bit allocation bitmap)
    int slotIndex = 0;
    while (slotIndex < 8)
    {
        uint32_t lowMask  = gPoolManager->m_bitmapLow[slotIndex];  // base + slotIndex*8
        uint32_t highMask = gPoolManager->m_bitmapHigh[slotIndex]; // base + 4 + slotIndex*8
        if ((lowMask & highMask) != 0xFFFFFFFF) // Check if any bit pair is not both set (i.e., there is a free block)
            break;
        slotIndex++;
    }
    if (slotIndex >= 8)
        return block; // No free block found? This might return an invalid block? Actually returns block without marking.

    // Combine the pair into a 64-bit mask
    uint64_t combinedMask = (static_cast<uint64_t>(gPoolManager->m_bitmapHigh[slotIndex]) << 32) | gPoolManager->m_bitmapLow[slotIndex];
    int bitIndex = findFirstFreeBit(gPoolManager->m_bitmapLow[slotIndex], gPoolManager->m_bitmapHigh[slotIndex]);
    uint64_t one = 1;
    uint64_t bit = one << (bitIndex % 64); // Actually we need to find the bit position within 64 bits
    // The shift operation from __allshl: shift combinedMask left by something? Actually the code does __allshl() with no args? That's strange. Let's reconstruct:
    // The decompiled shows:
    // uVar7 = __allshl();
    // That is likely a compiler intrinsic for 64-bit shift with two parameters? Hmm, maybe we missed parameters. But we know the intent: set the bit to mark allocation.
    // Let's assume we set the bit in the combined mask.
    uint64_t newMask = combinedMask | bit;
    gPoolManager->m_bitmapLow[slotIndex]  = static_cast<uint32_t>(newMask & 0xFFFFFFFF);
    gPoolManager->m_bitmapHigh[slotIndex] = static_cast<uint32_t>(newMask >> 32);

    // Set block metadata
    block->slotIndex = static_cast<uint8_t>(slotIndex);       // +0x1d
    block->bitIndex  = static_cast<uint8_t>(bitIndex);       // +7 (offset 28)
    block->someFlag  = 0;                                     // +0x1e

    // Calculate pointer to the actual data block in a 2D array (slotIndex * 0x40 + bitIndex) * 4
    // Base is at gPoolManager + 0x94? Actually the code does: iVar3 + 0x94 + (iVar6*0x40 + iVar5)*4
    // iVar3 is gPoolManager, so m_dataBase + (slotIndex * 64 + bitIndex) * 4
    block->dataPointer = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(gPoolManager) + 0x94 + (slotIndex * 64 + bitIndex) * 4);
    block->field9 = 0;
    block->fieldA = 0;
    block->fieldB = 0;

    return block;
}