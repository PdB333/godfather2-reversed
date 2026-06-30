// FUNC_NAME: GlobalData::initialize
undefined4* GlobalData::initialize(void)
{
    // Constants for structure sizes
    const int slotCount = 32;                    // Number of slots (e.g., 32 packet window or controller slots)
    const int slotEntrySize = 0x18;              // Each slot entry: 6 dwords (24 bytes)
    undefined8* pEntry = (undefined8*)&g_globalData + 0x8; // Start at offset 8 (first 8 bytes cleared separately?)

    // First loop: zero-initialize 32 slots of 24 bytes each (total 0x300 bytes)
    // Each iteration clears: offsets -8, -4, 0, 4, 8, 12 from the current pointer,
    // effectively zeroing the 24-byte block starting at offset 0.
    int loopCount = slotCount - 1; // 31
    undefined8* p = pEntry;
    do {
        *(undefined4*)(p - 1) = 0;    // offset -8 (relative to pEntry)
        *(undefined4*)((int)p - 4) = 0; // offset -4
        *(undefined4*)p = 0;           // offset 0
        *(undefined4*)((int)p + 4) = 0; // offset 4
        *(undefined4*)(p + 1) = 0;     // offset 8
        *(undefined4*)((int)p + 0xc) = 0; // offset 12
        p = p + 3; // move to next 24-byte block (3 * 8 bytes)
        loopCount--;
    } while (loopCount >= 0);

    // Second loop: set 32 uint at offset 0x300 to 0xFFFFFFFF (likely used as bitmask or invalid flags)
    uint* pFlags = (uint*)(&g_globalData + 0x300);
    uint offset = 0x300;
    do {
        *pFlags = 0xFFFFFFFF;
        pFlags++;
        offset += 4;
    } while (offset < 0x380); // 32 iterations (128 bytes)

    // Initialize separate fields at offset 0x4A0-0x4B8 (12 dwords set to 0)
    // These are likely part of the structure but outside the main slot arrays
    *(int*)(&g_globalData + 0x4A0) = 0;
    *(int*)(&g_globalData + 0x4A8) = 0;
    *(int*)(&g_globalData + 0x4B0) = 0;
    *(int*)(&g_globalData + 0x4B8) = 0;
    *(int*)(&g_globalData + 0x4C0) = 0;
    *(int*)(&g_globalData + 0x4C8) = 0;
    // ... similarly for the other 6 fields (based on the decompiled DAT_0121982c etc.)
    // Assuming they are contiguous, we'll just zero a range for clarity:
    for (int i = 0; i < 12; i++) {
        *(int*)((int)(&g_globalData + 0x4A0) + i * 4) = 0;
    }

    // Third loop: copy 32 dwords from a source (stride 24 bytes) to contiguous offset 0x400,
    // and zero 32 dwords at offset 0x480
    int* pSrc = (int*)(&g_globalData + 0x14); // start at offset 0x14 (part of first slot? probably predefined data)
    int* pDst = (int*)(&g_globalData + 0x400);
    int* pZeroArray = (int*)(&g_globalData + 0x480); // array of 32 ints to zero
    int idx = 0;
    uint uVar3 = 0x400;
    do {
        // Zero a separate global array (DAT_01219308+uVar3) - this might be another structure
        *(int*)((int)&g_otherGlobal + uVar3) = 0;
        // Copy from source to destination in main structure
        *pDst = *pSrc;
        // Zero the corresponding entry in the auxiliary array
        pZeroArray[idx] = 0;
        uVar3 += 4;
        idx++;
        pDst++;
        pSrc += 6; // stride 24 bytes (6 ints)
    } while (uVar3 < 0x480); // 32 iterations

    return &g_globalData;
}