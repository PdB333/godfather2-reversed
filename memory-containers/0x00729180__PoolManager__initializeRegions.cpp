// FUNC_NAME: PoolManager::initializeRegions
void __fastcall PoolManager::initializeRegions(int thisObj) {
    int* piVar1;
    int iVar2;
    int iterCount;

    // Global constants from static data
    int g_someGlobalA = DAT_01205228;  // Possibly a static pool or null handle
    int g_someGlobalB = DAT_00d5ccf8;  // Another global constant

    // Pointer to the currently initialized region data (starts at this+0x18)
    int* regionData = (int*)(thisObj + 0x18);

    // Initialize 8 regions, each 0x140 bytes (80 ints)
    iterCount = 8;
    do {
        // Region header (first 6 ints)
        regionData[-6] = (int)&PTR_FUN_00d5dbbc;  // vtable ptr
        regionData[-5] = -1;                       // sentinel
        regionData[-4] = 0;
        regionData[-3] = 0;

        // First two data fields of the region (after header)
        *(unsigned char*)(regionData + 1) = 0;  // byte at offset 4 from start of data area
        *regionData = 0;
        regionData[-1] = 0;
        regionData[-2] = 0;

        // Slot 0 (starts at regionData[2], 10 ints)
        regionData[2] = g_someGlobalA;
        regionData[3] = g_someGlobalB;
        regionData[4] = (int)&PTR_FUN_00d5dbbc;
        regionData[5] = -1;
        regionData[6] = 0;  // linked list head
        regionData[7] = 0;  // linked list tail (if node present)
        // If linked list head was non-null, would set it up, but it's zero.
        *(unsigned char*)(regionData + 0xb) = 0;  // byte field
        regionData[10] = 0;
        regionData[9] = 0;
        regionData[8] = 0;

        // Slot 1
        regionData[0xc] = g_someGlobalA;
        regionData[0xd] = g_someGlobalB;
        regionData[0xe] = (int)&PTR_FUN_00d5dbbc;
        regionData[0xf] = -1;
        regionData[0x10] = 0;
        regionData[0x11] = 0;
        *(unsigned char*)(regionData + 0x15) = 0;
        regionData[0x14] = 0;
        regionData[0x13] = 0;
        regionData[0x12] = 0;

        // Slot 2
        regionData[0x16] = g_someGlobalA;
        regionData[0x17] = g_someGlobalB;
        regionData[0x18] = (int)&PTR_FUN_00d5dbbc;
        regionData[0x19] = -1;
        regionData[0x1a] = 0;
        regionData[0x1b] = 0;
        *(unsigned char*)(regionData + 0x1f) = 0;
        regionData[0x1e] = 0;
        regionData[0x1d] = 0;
        regionData[0x1c] = 0;

        // Slot 3
        regionData[0x20] = g_someGlobalA;
        regionData[0x21] = g_someGlobalB;
        regionData[0x22] = (int)&PTR_FUN_00d5dbbc;
        regionData[0x23] = -1;
        regionData[0x24] = 0;
        regionData[0x25] = 0;
        *(unsigned char*)(regionData + 0x29) = 0;
        regionData[0x28] = 0;
        regionData[0x27] = 0;
        regionData[0x26] = 0;

        // Slot 4
        regionData[0x2a] = g_someGlobalA;
        regionData[0x2b] = g_someGlobalB;
        regionData[0x2c] = (int)&PTR_FUN_00d5dbbc;
        regionData[0x2d] = -1;
        regionData[0x2e] = 0;
        regionData[0x2f] = 0;
        *(unsigned char*)(regionData + 0x33) = 0;
        regionData[0x32] = 0;
        regionData[0x31] = 0;
        regionData[0x30] = 0;

        // Slot 5
        regionData[0x34] = g_someGlobalA;
        regionData[0x35] = g_someGlobalB;
        regionData[0x36] = (int)&PTR_FUN_00d5dbbc;
        regionData[0x37] = -1;
        regionData[0x38] = 0;
        regionData[0x39] = 0;
        *(unsigned char*)(regionData + 0x3d) = 0;
        regionData[0x3c] = 0;
        regionData[0x3b] = 0;
        regionData[0x3a] = 0;

        // Slot 6
        regionData[0x3e] = g_someGlobalA;
        regionData[0x3f] = g_someGlobalB;
        regionData[0x40] = (int)&PTR_FUN_00d5dbbc;
        regionData[0x41] = -1;
        regionData[0x42] = 0;
        regionData[0x43] = 0;
        *(unsigned char*)(regionData + 0x47) = 0;
        regionData[0x46] = 0;
        regionData[0x45] = 0;
        regionData[0x44] = 0;

        // Slot 7 (incomplete – only 2 ints written)
        regionData[0x48] = g_someGlobalA;
        regionData[0x49] = g_someGlobalB;

        // Advance to next region (each region is 0x140 bytes = 80 ints)
        regionData += 0x50;  // pointer arithmetic: adds 0x50*4 = 0x140 bytes

        iterCount--;
    } while (iterCount != 0);

    // Final marker at end of all regions
    *(int*)(thisObj + 0xa00) = 0;
}