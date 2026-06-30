// FUNC_NAME: GodfatherGameManager::initializeGameConstants

void GodfatherGameManager::initializeGameConstants(void)
{
    int iVar1;
    uint32_t* pTable;

    // Clamp global min/max values for something (likely reputation or respect)
    if (DAT_012058d0 < 0x16) {
        DAT_012058d0 = 0x16;
    }
    if (0x16 < DAT_00f15988) {
        DAT_00f15988 = 0x16;
    }
    _DAT_011f3a30 = 1; // +0x30? (global struct offset)

    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }
    _DAT_011f39f4 = 0; // +0x? (different global)

    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }
    _DAT_011f3a10 = 0; // +0x10

    if (DAT_012058d0 < 0x19) {
        DAT_012058d0 = 0x19;
    }
    if (0x19 < DAT_00f15988) {
        DAT_00f15988 = 0x19;
    }
    _DAT_011f3a3c = 5; // +0x3c

    if (DAT_012058d0 < 0x18) {
        DAT_012058d0 = 0x18;
    }
    if (0x18 < DAT_00f15988) {
        DAT_00f15988 = 0x18;
    }
    _DAT_011f3a38 = 0; // +0x38

    if (DAT_012058d0 < 0xf) {
        DAT_012058d0 = 0xf;
    }
    if (0xf < DAT_00f15988) {
        DAT_00f15988 = 0xf;
    }
    _DAT_011f3a14 = 0; // +0x14

    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }
    _DAT_011f3a44 = 0; // +0x44

    // Initialize some subsystem (maybe FamilyManager or CrimeManager)
    FUN_00417cf0(1, 2, 1);
    FUN_0053c6f0();
    FUN_0053c670();

    // Handle entity at global index DAT_01218ee0 (family index?)
    if ((DAT_01218ee0 != 0xffffffff) && (DAT_01218ee0 < 0x1000)) {
        iVar1 = DAT_01218ee0 * 0x38; // stride 0x38
        // gFamilyData is an array of 0x38-byte structures starting at 0x011a0f28
        byte* pFamily = (byte*)(&gFamilyDataBase) + iVar1;
        if ((pFamily != (byte*)0x0) && (pFamily[0] < 4)) { // first byte is state (0-3)
            // offset 0x1c? - pointer to some resource
            uint32_t* pResource = *(uint32_t**)(pFamily + 0x1c);
            if (pResource != 0) {
                FUN_00606e60(pResource, 0x200000); // deallocate resource with flag
            }
            // offset 0x0c? - flags field
            *(uint32_t*)(pFamily + 0x0c) = (*(uint32_t*)(pFamily + 0x0c) & 0xfcac8fff) | 0x200000;
            FUN_006189c0(); // update state/mark dirty?
        }
    }

    // Handle another entity index DAT_01218e58
    if ((DAT_01218e58 != 0xffffffff) && (DAT_01218e58 < 0x1000)) {
        iVar1 = DAT_01218e58 * 0x38;
        byte* pFamily = (byte*)(&gFamilyDataBase) + iVar1;
        if ((pFamily != (byte*)0x0) && (pFamily[0] < 4)) {
            uint32_t* pResource = *(uint32_t**)(pFamily + 0x1c);
            if (pResource != 0) {
                FUN_00606e60(pResource, 0x100000);
            }
            *(uint32_t*)(pFamily + 0x0c) = (*(uint32_t*)(pFamily + 0x0c) & 0xfc9c8fff) | 0x100000;
            FUN_006189c0();
        }
    }

    // Free some global pointers if allocated
    if (*DAT_0121be7c != 0) {
        FUN_006063b0(); // deallocate
    }
    if (DAT_0121be7c[2] != 0) {
        FUN_006063b0();
    }

    // Allocate a 16-element uint32 table (size 0x40 bytes?) and fill it with constants
    // heapAllocate(size, alignment?, ...)
    pTable = (uint32_t*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    if (pTable != (uint32_t*)0x0) {
        pTable[0] = DAT_00e2eff4;
        pTable[1] = DAT_00e2b1a4;
        pTable[2] = 0;
        pTable[3] = 0;
        pTable[4] = DAT_00e2b1a4;
        pTable[5] = DAT_00e2b1a4;
        pTable[6] = DAT_00e2b1a4;
        pTable[7] = 0;
        pTable[8] = DAT_00e2b1a4;
        pTable[9] = DAT_00e2eff4;
        pTable[10] = DAT_00e2b1a4;
        pTable[11] = DAT_00e2b1a4;
        pTable[12] = DAT_00e2eff4;
        pTable[13] = DAT_00e2eff4;
        pTable[14] = 0;
        pTable[15] = DAT_00e2b1a4;
        FUN_0060cde0(); // possibly commit the allocation or register it
    }

    FUN_00612e00(); // finalize initialization

    // Clear two event/flag indicators
    DAT_0121bc20 = 0;
    DAT_0121bc24 = 0;
}