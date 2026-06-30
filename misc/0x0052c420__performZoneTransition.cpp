// FUNC_NAME: performZoneTransition

// Function address: 0x0052c420
// Role: Manages zone/area transitions with fog, depth texture, and effect blending.
// Parameters:
//   isInitialTransition - bool indicating if this is the initial setup,
//   zoneA - primary zone ID (or -1),
//   zoneB - secondary zone ID (or -1),
//   floatParamA, floatParamB - transition distances/timing (passed in XMM0 and XMM1).
// Global arrays (DAT_01218e50 etc.) hold zone state slots (0x14 entries, each 2*4 bytes).
// Global arrays (DAT_011a0f28 etc.) hold resource slots (0x38 bytes each, up to 0x1000).
// Constants DAT_00e2b04c and DAT_00e2d99c represent near/far fog boundaries.

void __thiscall performZoneTransition(char isInitialTransition, uint zoneA, uint zoneB)
{
    uint uVar1;
    bool bVar2;
    int iVar3;
    bool bVar4;
    undefined4 uVar5;
    int iVar6;
    uint uVar7;
    uint uVar8;
    float in_XMM0_Da;   // passed in XMM0
    float fVar9;
    float fVar10;
    float in_XMM1_Da;   // passed in XMM1
    undefined4 uVar11;
    float local_1c;
    uint local_10;

    // Resolve zoneB: if 0, use default from table based on isInitialTransition
    if (zoneB == 0) {
        // Index into table: offset = (-(isInitialTransition != 0) & 0xFFFFFFFD) * 2
        // If true: offset = 0xFFFFFFFD * 2 = 0x1FFFFFFFA (wraps) - likely a decompiler glitch.
        // Actual: uses an array of 2 entries for two states (indoor/outdoor?).
        // Simplified: zoneB = (isInitialTransition) ? outdoor_default_zone : indoor_default_zone.
        if (isInitialTransition) {
            zoneB = DAT_01218eb8[0xFFFFFFFD]; // placeholder: needs real offset
        } else {
            zoneB = DAT_01218eb8[0];          // placeholder: index 0
        }
    }

    // If the float in XMM0 equals a sentinel value (DAT_00e2eff4), override with XMM1
    if (in_XMM0_Da == DAT_00e2eff4) {
        in_XMM0_Da = in_XMM1_Da;
    }

    // Compute distances from thresholds
    local_1c = DAT_00e2d99c; // default near threshold
    if (isInitialTransition) {
        local_1c = DAT_00e2b04c; // outdoor threshold
    }
    local_1c = in_XMM1_Da - local_1c;

    fVar9 = DAT_00e2d99c;
    if (isInitialTransition) {
        fVar9 = DAT_00e2b04c;
    }
    fVar9 = in_XMM0_Da - fVar9;

    fVar10 = fVar9;
    if (fVar9 < local_1c) {
        fVar10 = local_1c; // take the maximum of the two distances
    }

    if (fVar10 <= 0.0f) {
        return; // no transition if distance is zero or negative
    }

    local_10 = zoneA;

    // Resolve primary zone index from table
    {
        uint offset = (isInitialTransition) ? 0xFFFFFFFB : 0; // similar pattern
        uVar1 = DAT_01218ea8[offset * 2]; // placeholder
    }

    iVar6 = (isInitialTransition ? 0xFFFFFFFD : 0) + 0xD; // index into some table
    uVar8 = DAT_01218e50[iVar6 * 2]; // secondary zone from table

    // Determine if both distances are positive and not equal
    if (((local_1c == fVar9) || (fVar9 <= 0.0f)) || (bVar4 = true, local_1c <= 0.0f)) {
        bVar4 = false;
    }
    bVar2 = (fVar9 < local_1c); // true if second distance is smaller

    // Conditional update of uVar8 based on threshold check
    if (DAT_00e2b04c <= (float)((uint)(fVar9 - local_1c) & DAT_00e44680)) {
        if (bVar4) {
            uVar8 = *(uint *)(&DAT_01218e78 + (isInitialTransition ? 0xFFFFFFFD : 0) * 8);
            if (bVar2) {
                local_1c = fVar9;
            }
            goto LAB_0052c531;
        }
    } else {
        bVar4 = false;
    }
    local_1c = 0.0f;

LAB_0052c531:
    // Release and mark resources for zoneA, uVar1, uVar8, zoneB
    // Each resource slot is 0x38 bytes, first byte must be < 4 (active?)
    // Set flag 0x100000 at offset 0x0C, release pointer at offset 0x1C
    if ((zoneA != 0xFFFFFFFF) && (zoneA < 0x1000)) {
        iVar3 = zoneA * 0x38;
        if ((&DAT_011a0f28 + iVar3 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar3] < 4)) {
            if (*(int *)(&DAT_011a0f44 + iVar3) != 0) {
                FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar3), 0x100000);
            }
            *(uint *)(&DAT_011a0f34 + iVar3) = *(uint *)(&DAT_011a0f34 + iVar3) & 0xFC9C8FFF | 0x100000;
            FUN_006189c0();
        }
    }
    // Repeat for uVar1, uVar8, zoneB (identical pattern)
    // ... (code omitted for brevity, same structure)
    if ((uVar1 != 0xFFFFFFFF) && (uVar1 < 0x1000)) {
        iVar3 = uVar1 * 0x38;
        if ((&DAT_011a0f28 + iVar3 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar3] < 4)) {
            if (*(int *)(&DAT_011a0f44 + iVar3) != 0) {
                FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar3), 0x100000);
            }
            *(uint *)(&DAT_011a0f34 + iVar3) = *(uint *)(&DAT_011a0f34 + iVar3) & 0xFC9C8FFF | 0x100000;
            FUN_006189c0();
        }
    }
    if ((uVar8 != 0xFFFFFFFF) && (uVar8 < 0x1000)) {
        iVar3 = uVar8 * 0x38;
        if ((&DAT_011a0f28 + iVar3 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar3] < 4)) {
            if (*(int *)(&DAT_011a0f44 + iVar3) != 0) {
                FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar3), 0x100000);
            }
            *(uint *)(&DAT_011a0f34 + iVar3) = *(uint *)(&DAT_011a0f34 + iVar3) & 0xFC9C8FFF | 0x100000;
            FUN_006189c0();
        }
    }
    if ((zoneB != 0xFFFFFFFF) && (zoneB < 0x1000)) {
        iVar3 = zoneB * 0x38;
        if ((&DAT_011a0f28 + iVar3 != (byte *)0x0) && ((byte)(&DAT_011a0f28)[iVar3] < 4)) {
            if (*(int *)(&DAT_011a0f44 + iVar3) != 0) {
                FUN_00606e60(*(int *)(&DAT_011a0f44 + iVar3), 0x100000);
            }
            *(uint *)(&DAT_011a0f34 + iVar3) = *(uint *)(&DAT_011a0f34 + iVar3) & 0xFC9C8FFF | 0x100000;
            FUN_006189c0();
        }
    }

    // Update global state
    FUN_0053d590();
    FUN_00417cf0(1, 2, 1); // maybe debug/log
    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }
    _DAT_011f3a44 = 0;

    // Search for uVar1 in zone table and mark as inactive (clear low 2 bits)
    uVar7 = 0;
    do {
        if (DAT_01218e50[uVar7 * 2] == uVar1) {
            if (uVar7 < 0x14) {
                DAT_01218e54[uVar7 * 2] = DAT_01218e54[uVar7 * 2] & 0xFFFFFFFC;
            }
            break;
        }
        uVar7 = uVar7 + 1;
    } while (uVar7 < 0x14);

    uVar5 = DAT_011f38f4;
    uVar11 = DAT_011f38f0;
    DAT_011f38f4 = 0;
    DAT_011f38f0 = uVar1;
    FUN_00609340(0, uVar11, uVar5); // set active zone?

    // Repeat for uVar8
    uVar7 = 0;
    do {
        if (DAT_01218e50[uVar7 * 2] == uVar8) {
            if (uVar7 < 0x14) {
                DAT_01218e54[uVar7 * 2] = DAT_01218e54[uVar7 * 2] & 0xFFFFFFFC;
            }
            break;
        }
        uVar7 = uVar7 + 1;
    } while (uVar7 < 0x14);

    uVar11 = DAT_011f38f4;
    uVar7 = DAT_011f38f0;
    DAT_011f38f4 = 0;
    DAT_011f38f0 = uVar8;
    FUN_00609340(0, uVar7, uVar11);

    // If bVar4 is true, perform a secondary transition (fade/pop)
    if (bVar4) {
        // Again mark uVar1 in zone table
        uVar8 = 0;
        do {
            if (DAT_01218e50[uVar8 * 2] == uVar1) {
                if (uVar8 < 0x14) {
                    DAT_01218e54[uVar8 * 2] = DAT_01218e54[uVar8 * 2] & 0xFFFFFFFC;
                }
                break;
            }
            uVar8 = uVar8 + 1;
        } while (uVar8 < 0x14);

        uVar11 = DAT_011f38f4;
        uVar8 = DAT_011f38f0;
        DAT_011f38f4 = 0;
        DAT_011f38f0 = uVar1;
        FUN_00609340(0, uVar8, uVar11);

        FUN_00609810(1); // begin batch update
        // Set up environment parameters for primary zone
        DAT_0121b750 = DAT_01219908;
        DAT_0121b874 = 0;
        DAT_0121b754 = DAT_0121bbac;
        if (((DAT_0121bbac == DAT_0121bbc0) || (DAT_0121bbac == DAT_0121bbc4)) ||
            (DAT_0121bbac == DAT_0121bbc8)) {
            // Look up shader parameters by name
            DAT_0121bb7c = FUN_0060a580(DAT_0121bbac, "fog_color");
            DAT_0121bb80 = FUN_0060a580(DAT_0121b754, "fog_params");
            DAT_0121bb84 = FUN_0060a580(DAT_0121b754, "depth_texture");
        }
        if (DAT_012058e8 == &DAT_0121b740) {
            FUN_0060a460(DAT_0121b754);
            FUN_0060a460(DAT_0121b750);
        }
        FUN_005388a0();
        FUN_0053a7f0(3 - (uint)bVar2);
        FUN_00528010();
        FUN_00539250();
        FUN_00609890(1); // end batch update

        fVar10 = fVar10 - DAT_00e2b04c;
        uVar8 = uVar1;
        local_10 = uVar1;
    }

    // Call the core transition helper
    FUN_0052c380(local_10, uVar8, fVar10 - local_1c, !bVar4);

    if (bVar4) {
        // Aftermath: update globals, set fog/effects for secondary zone
        if (DAT_012058d0 < 0x1b) {
            DAT_012058d0 = 0x1b;
        }
        if (0x1a < DAT_00f15988) {
            DAT_00f15988 = 0x1b;
        }
        _DAT_011f3a44 = 1;
        if (bVar2) {
            uVar11 = 3;
        } else {
            uVar11 = 1;
        }
        FUN_00417cf0(uVar11, 2, 2);
        DAT_0121b750 = DAT_01219908;
        DAT_0121b874 = 0;
        DAT_0121b754 = DAT_0121bba8; // different environment preset
        if (((DAT_0121bba8 == DAT_0121bbc0) || (DAT_0121bba8 == DAT_0121bbc4)) ||
            (DAT_0121bba8 == DAT_0121bbc8)) {
            DAT_0121bb7c = FUN_0060a580(DAT_0121bba8, "fog_color");
            DAT_0121bb80 = FUN_0060a580(DAT_0121b754, "fog_params");
            DAT_0121bb84 = FUN_0060a580(DAT_0121b754, "depth_texture");
        }
        if (DAT_012058e8 == &DAT_0121b740) {
            FUN_0060a460(DAT_0121b754);
            FUN_0060a460(DAT_0121b750);
        }
        FUN_005388a0();
        FUN_0053a7f0(bVar2);
        FUN_00528010();
        FUN_00539250();
        FUN_00417cf0(1, 2, 1);
        FUN_00609890(1);

        // Resolve new zone from table
        uVar1 = DAT_01218e50[iVar6 * 2];
        uVar7 = 0;
        do {
            if (DAT_01218e50[uVar7 * 2] == uVar1) {
                if (uVar7 < 0x14) {
                    DAT_01218e54[uVar7 * 2] = DAT_01218e54[uVar7 * 2] & 0xFFFFFFFC;
                }
                break;
            }
            uVar7 = uVar7 + 1;
        } while (uVar7 < 0x14);

        uVar11 = DAT_011f38f4;
        uVar7 = DAT_011f38f0;
        DAT_011f38f4 = 0;
        DAT_011f38f0 = uVar1;
        FUN_00609340(0, uVar7, uVar11);

        if (DAT_012058d0 < 0x1b) {
            DAT_012058d0 = 0x1b;
        }
        if (0x1a < DAT_00f15988) {
            DAT_00f15988 = 0x1b;
        }
        _DAT_011f3a44 = 0;

        // Final transition call
        FUN_0052c380(uVar8, uVar1, local_1c, 1);
    }

    // Final zone switch if current active zone differs from zoneB
    uVar1 = DAT_011f38f0;
    if (DAT_011f38f0 != zoneB) {
        uVar8 = 0;
        do {
            if (DAT_01218e50[uVar8 * 2] == zoneB) {
                if (uVar8 < 0x14) {
                    DAT_01218e54[uVar8 * 2] = DAT_01218e54[uVar8 * 2] & 0xFFFFFFFC;
                }
                break;
            }
            uVar8 = uVar8 + 1;
        } while (uVar8 < 0x14);

        uVar11 = DAT_011f38f4;
        DAT_011f38f0 = zoneB;
        DAT_011f38f4 = 0;
        FUN_00609340(0, uVar1, uVar11);

        FUN_00609810(1);
        DAT_01219954 = DAT_012198fc;
        DAT_01219950 = DAT_01219900;
        _DAT_01219a6c = 4;
        if (DAT_012058e8 == &DAT_01219940) {
            FUN_0060a460(DAT_012198fc);
            FUN_0060a460(DAT_01219950);
        }
        FUN_00530a60();
        FUN_00530df0();
        FUN_00528070();
        FUN_00612e00();
        DAT_01219950 = 0;
        DAT_01219954 = 0;
        _DAT_012199e4 = 0;
        _DAT_012199e8 = 0;
        FUN_00609890(1);
    }
    return;
}