// FUNC_NAME: Graphics::initializeDisplaySettings
void __cdecl initializeDisplaySettings(void)
{
    int iVar1;
    float fVar2;
    uint uVar3;
    uint uVar4;
    uint uVar7;
    float aspectRatioScale[7]; // Actually only used up to index 3

    // Global min/max clamping for some rendering parameters
    // DAT_012058d0 and DAT_00f15988 seem to be min/max clamping values (e.g., for resolution)
    if (DAT_012058d0 < 22) {
        DAT_012058d0 = 22;
    }
    if (22 < DAT_00f15988) {
        DAT_00f15988 = 22;
    }

    _DAT_011f3a30 = 1; // Some flag

    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }

    _DAT_011f39f4 = 0;

    if (DAT_012058d0 < 14) {
        DAT_012058d0 = 14;
    }
    if (14 < DAT_00f15988) {
        DAT_00f15988 = 14;
    }

    _DAT_011f3a10 = 0;

    if (DAT_012058d0 < 25) {
        DAT_012058d0 = 25;
    }
    if (25 < DAT_00f15988) {
        DAT_00f15988 = 25;
    }

    _DAT_011f3a3c = 5;

    if (DAT_012058d0 < 24) {
        DAT_012058d0 = 24;
    }
    if (24 < DAT_00f15988) {
        DAT_00f15988 = 24;
    }

    _DAT_011f3a38 = 0;

    if (DAT_012058d0 < 15) {
        DAT_012058d0 = 15;
    }
    if (15 < DAT_00f15988) {
        DAT_00f15988 = 15;
    }

    _DAT_011f3a14 = 0;

    if (DAT_012058d0 < 27) {
        DAT_012058d0 = 27;
    }
    if (26 < DAT_00f15988) {
        DAT_00f15988 = 27;
    }

    _DAT_011f3a44 = 1;

    // Calls to set some rendering state
    FUN_00417cf0(1, 2, 1); // Unknown render function
    FUN_00609890(1);       // Possibly set flag

    iVar1 = DAT_01218ee0;  // Current display mode index?
    uVar4 = DAT_011f38f0;  // Old display mode index?
    uVar7 = 0;

    // Search for matching display mode in a table of 20 entries
    do {
        if ((&DAT_01218e50)[uVar7 * 2] == DAT_01218ee0) {
            // Clear low 2 bits of some flag in matched entry
            if (uVar7 < 20) {
                (&DAT_01218e54)[uVar7 * 2] = (&DAT_01218e54)[uVar7 * 2] & 0xfffffffc;
            }
            break;
        }
        uVar7 = uVar7 + 1;
    } while (uVar7 < 20);

    // Store new display mode index and clear some state
    uVar3 = DAT_011f38f4;
    DAT_011f38f0 = iVar1;
    DAT_011f38f4 = 0;

    // Change render target/resolution
    FUN_00609340(0, uVar4, uVar3);       // swap/resize render targets?
    FUN_0060db60(0, 0, 0, 1.0f, 1.0f); // set viewport to full screen

    FUN_0053c6f0(); // Unknown
    FUN_0053c670(); // Unknown

    // If old mode invalid, skip
    if (uVar4 != 0xffffffff) {
        // If old mode within range, reset some state
        if (uVar4 < 0x1000) {
            int offset = uVar4 * 0x38; // 56 bytes per entry
            // Check if entry exists and status < 4
            if ((&DAT_011a0f28)[offset] != 0) {
                // Not null: check mode status
                if ((byte)(&DAT_011a0f28)[offset] < 4) {
                    // If there is an associated buffer, free it with a flag
                    if (*(int *)(&DAT_011a0f44 + offset) != 0) {
                        FUN_00606e60(*(int *)(&DAT_011a0f44 + offset), 0x200000); // deallocate with flags
                    }
                    // Clear some bits and set a flag for allocation
                    *(uint *)(&DAT_011a0f34 + offset) =
                        *(uint *)(&DAT_011a0f34 + offset) & 0xfcac8fff | 0x200000;
                    FUN_006189c0(); // Update some internal state
                }
            }
        }
        // If mode < 0x1000 (valid), fall through to compute aspect ratio
        // else skip to label with puVar5 = 0
        if (uVar4 < 0x1000) {
            goto LAB_0053254f; // This goto actually falls through below
        }
    }

    // Compute aspect ratio scale factors for current mode
    if (uVar4 < 0x1000) {
        puVar5 = &DAT_011a0f28 + uVar4 * 0x38;
    } else {
        puVar5 = nullptr;
    }

LAB_0053256b:
    // Compute horizontal aspect ratio from width/height
    aspectRatioScale[0] = DAT_00e2b1a4 / (float)*(ushort *)(puVar5 + 2); // width / height?
    aspectRatioScale[1] = 0.0f;
    aspectRatioScale[2] = 0.0f;

    if (uVar4 < 0x1000) {
        puVar5 = &DAT_011a0f28 + uVar4 * 0x38;
    } else {
        puVar5 = nullptr;
    }

    aspectRatioScale[3] = DAT_00e2b1a4 / (float)*(ushort *)(puVar5 + 4); // width / something?

    // If there's an active render target, set projection matrix
    if (DAT_0121be7c[7] != 0) {
        FUN_0060add0(DAT_0121bc24, DAT_0121be7c[7], aspectRatioScale);
    }

    // If first render target active, do something
    if (*DAT_0121be7c != 0) {
        FUN_006063b0();
    }

    // Allocate memory for some configuration block (type 0xd)
    uint* pConfig = (uint*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    uVar3 = DAT_00e2eff4;  // Some global value (maybe screen height?)
    fVar2 = DAT_00e2b1a4;  // Screen width

    if (pConfig != nullptr) {
        pConfig[0]  = uVar3;
        pConfig[1]  = (uint)fVar2;
        pConfig[2]  = 0;
        pConfig[3]  = 0;
        pConfig[4]  = (uint)fVar2;
        pConfig[5]  = (uint)fVar2;
        pConfig[6]  = (uint)fVar2;
        pConfig[7]  = 0;
        pConfig[8]  = (uint)fVar2;
        pConfig[9]  = uVar3;
        pConfig[10] = (uint)fVar2;
        pConfig[11] = (uint)fVar2;
        pConfig[12] = uVar3;
        pConfig[13] = uVar3;
        pConfig[14] = 0;
        pConfig[15] = (uint)fVar2;
        FUN_0060cde0(); // Possibly register/release allocator lock
    }

    FUN_00612e00(); // Another rendering setup function

    // Clear global pointers
    DAT_0121bc20 = 0;
    DAT_0121bc24 = 0;

    FUN_00609890(1); // Set some flag again
    FUN_004e3a70();  // Maybe finalize initialization

    // Local label (actually used with goto)
    // LAB_0053254f: simply falls through to compute aspect ratio (handled above)
}