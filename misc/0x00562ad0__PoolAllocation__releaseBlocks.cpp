// FUNC_NAME: PoolAllocation::releaseBlocks
// Function address: 0x00562ad0
// This function releases two pool-allocated blocks owned by a PoolAllocation object.
// Indices are signed: bit31 clear (>=0) indicates a valid allocation.
// First block (indexA) uses a 30-bit index with flags in bits30-31, block size = indexA * 12.
// Second block (indexB) uses a 31-bit index, block size = indexB * 16.
// The TLS value (likely for debug heap) is fetched but not used here; it may be consumed by poolFree.
// The debug fill marker 0x17 is passed to poolFree.

#include <windows.h> // For TlsGetValue

extern DWORD g_TlsIndex; // DAT_01139810

struct PoolAllocation {
    void* poolB;        // +0x00
    int   unused1;      // +0x04 (not used here)
    int   indexB;       // +0x08
    void* poolA;        // +0x0C
    int   unused2;      // +0x10 (not used here)
    uint  indexA;       // +0x14
};

// FUN_00aa26e0: poolFree(void* pool, uint size, int debugMarker)
void __fastcall poolFree(void* pool, uint size, int debugMarker);

void __fastcall FUN_00562ad0(PoolAllocation* this_)
{
    uint uIndexA = this_->indexA;
    if ((int)uIndexA >= 0) // Valid if bit31 == 0
    {
        TlsGetValue(g_TlsIndex); // Retrieve thread-local storage (heap context)
        uint realIndexA = uIndexA & 0x3fffffff;
        uint blockSizeA = realIndexA * 12;
        poolFree(this_->poolA, blockSizeA, 0x17);
    }

    int iIndexB = this_->indexB;
    if (iIndexB >= 0) // Valid if bit31 == 0
    {
        TlsGetValue(g_TlsIndex);
        uint blockSizeB = (uint)iIndexB << 4; // multiply by 16
        poolFree(this_->poolB, blockSizeB, 0x17);
    }

    return;
}