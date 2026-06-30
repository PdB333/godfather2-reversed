// FUNC_NAME: GameSettingsManager::applySettingsFlags (0x0052f250)
// Function: Applies various game settings based on a bitmask flags parameter.
// Accesses global settings variables and clamps values to valid ranges.
void __thiscall GameSettingsManager::applySettingsFlags(uint flags, int param3)
{
    bool bHasBothParams;
    int iVar2;
    int iVar3;
    uint uVar4;
    undefined1 *puVar5;
    undefined4 uVar6;
    undefined4 extraout_ECX;
    float local_30;
    float local_2c;
    undefined4 local_28;
    undefined4 local_24;
    undefined1 local_20 [28];

    iVar3 = DAT_01205540;
    if (flags != DAT_01205538) {
        iVar3 = FUN_0053dff0(); // Check if settings are dirty
    }
    iVar2 = DAT_01218e58;
    if (iVar3 != 0) {
        // Determine if both parameters are non-zero
        bHasBothParams = (param3 != 0) && (flags != 0);

        // If pointer match condition, set some flag
        if ((DAT_011f38f0 == DAT_01218e58) && (DAT_011f38f4 == 0)) {
            FUN_00609890(1);
        }
        else {
            FUN_0060df60(DAT_011f38f0, DAT_01218e58);
        }

        // Set global state and clamp values for quality/settings
        DAT_0120551e = 1;
        if (DAT_012058d0 < 0x16) {
            DAT_012058d0 = 0x16;
        }
        if (0x16 < DAT_00f15988) {
            DAT_00f15988 = 0x16;
        }
        _DAT_011f3a30 = 1;
        if (DAT_012058d0 < 7) {
            DAT_012058d0 = 7;
        }
        if (7 < DAT_00f15988) {
            DAT_00f15988 = 7;
        }
        _DAT_011f39f4 = 0;
        if (DAT_012058d0 < 0xe) {
            DAT_012058d0 = 0xe;
        }
        if (0xe < DAT_00f15988) {
            DAT_00f15988 = 0xe;
        }
        _DAT_011f3a10 = 0;
        if (DAT_012058d0 < 0x19) {
            DAT_012058d0 = 0x19;
        }
        if (0x19 < DAT_00f15988) {
            DAT_00f15988 = 0x19;
        }
        _DAT_011f3a3c = 5;
        if (DAT_012058d0 < 0x18) {
            DAT_012058d0 = 0x18;
        }
        if (0x18 < DAT_00f15988) {
            DAT_00f15988 = 0x18;
        }
        _DAT_011f3a38 = 0;
        if (DAT_012058d0 < 0xf) {
            DAT_012058d0 = 0xf;
        }
        if (0xf < DAT_00f15988) {
            DAT_00f15988 = 0xf;
        }
        _DAT_011f3a14 = 0;
        if (DAT_012058d0 < 0x1b) {
            DAT_012058d0 = 0x1b;
        }
        if (0x1a < DAT_00f15988) {
            DAT_00f15988 = 0x1b;
        }
        _DAT_011f3a44 = 0;

        FUN_00417cf0(1, 2, 1); // Renderer setting?

        FUN_0053d950();  // Audio update?
        FUN_00612a60();  // Input update?

        // If bit 2 is set (flag 0x4)
        if ((flags >> 2 & 1) != 0) {
            FUN_00514890(&local_30);  // Get current settings data
            FUN_0053dc00(&local_30);  // Apply audio settings
            FUN_0053dc50();           // Commit audio changes

            // Prepare a matrix or vector for sound positioning
            local_30 = DAT_01219200;
            local_2c = (float)DAT_01219204;
            local_28 = DAT_01219208;
            local_24 = DAT_01219224;

            if ((&DAT_01198eb4)[DAT_0121bf30 * 0x1b] != 0) {
                FUN_0060add0(DAT_0121be9c, (&DAT_01198eb4)[DAT_0121bf30 * 0x1b], &local_30);
            }

            local_30 = DAT_01219210;
            local_2c = DAT_01219214;
            local_28 = DAT_01219218;
            local_24 = DAT_01219228;

            if ((&DAT_01198eb8)[DAT_0121bf30 * 0x1b] != 0) {
                FUN_0060add0(DAT_0121be9c, (&DAT_01198eb8)[DAT_0121bf30 * 0x1b], &local_30);
            }

            FUN_00515d70(); // Finalize audio updates
        }

        // Handle display/rendering settings based on bit 4 (flag 0x10)
        if ((flags >> 4 & 1) == 0) {
            // If bit not set, apply a specific state
            FUN_00606e60(iVar2, ((-(uint)bHasBothParams & 0xffef0000) + 0x210000));
            iVar3 = DAT_012054dc;
        }
        else {
            // Bit 4 set: handle resolution/scaling data
            uVar4 = DAT_012058a4;
            if (DAT_012054dc != 0) {
                uVar4 = *(uint *)(DAT_012054dc + 0x16c); // Player struct +0x16c
            }
            if (uVar4 < 0x1000) {
                puVar5 = &DAT_011a0f28 + uVar4 * 0x38; // Array of structs size 0x38
            }
            else {
                puVar5 = (undefined1 *)0x0;
            }

            local_30 = DAT_01197d74 / (float)*(ushort *)(puVar5 + 2);
            uVar4 = DAT_012058a4;
            if (DAT_012054dc != 0) {
                uVar4 = *(uint *)(DAT_012054dc + 0x16c);
            }
            if (uVar4 < 0x1000) {
                puVar5 = &DAT_011a0f28 + uVar4 * 0x38;
            }
            else {
                puVar5 = (undefined1 *)0x0;
            }
            local_2c = DAT_01197d74 / (float)*(ushort *)(puVar5 + 4);
            local_28 = DAT_01197d70;
            local_24 = DAT_01197d78;

            if ((&DAT_01198ebc)[DAT_0121bf30 * 0x1b] != 0) {
                FUN_0060add0(DAT_0121be9c, (&DAT_01198ebc)[DAT_0121bf30 * 0x1b], &local_30);
            }

            iVar3 = DAT_012054dc;
            DAT_01197d70 = 0;
            DAT_01197d74 = 0.0;
            DAT_01197d78 = 0;
            _DAT_01197d7c = 0;
            _DAT_01197d80 = DAT_00e2b118;
            _DAT_01197d84 = DAT_00e2b1a4;
            _DAT_01197d88 = DAT_00e446c4;
            _DAT_01197d8c = DAT_00e2b1a4;
            DAT_01197d90 = 0;

            FUN_00606e60(iVar2, ((-(uint)bHasBothParams & 0xfff00000) + 0x200000));
        }

        // Handle other sub-features based on flags bits
        if ((flags & 1) != 0) {
            FUN_0053de00(DAT_01125290);
            DAT_01125290 = 0;
            iVar3 = DAT_012054dc;
        }
        if ((flags >> 5 & 1) != 0) {
            FUN_00518510();
            uVar7 = DAT_012058a8;
            uVar6 = DAT_012058a8;
            if (iVar3 != 0) {
                uVar6 = *(undefined4 *)(iVar3 + 0x170);
            }
            FUN_00606e60(uVar6, 0x210000);
            FUN_00606e60(*(undefined4 *)(&DAT_01218e88 + (-(uint)(DAT_012192f0 != 0x4000000) & 10) * 8),
                         0x200000);
            if (iVar3 != 0) {
                uVar7 = *(undefined4 *)(iVar3 + 0x170);
            }
            FUN_0053de70(uVar7);
            if ((&DAT_01198ec8)[DAT_0121bf30 * 0x1b] != 0) {
                FUN_0060add0(DAT_0121be9c, (&DAT_01198ec8)[DAT_0121bf30 * 0x1b], local_20);
            }
            FUN_0053df00();
            FUN_0053deb0();
            FUN_00517f50();
        }

        if ((flags & 0x700) != 0) {
            FUN_0053dac0(&DAT_0121930c, DAT_01219344);
            FUN_0053db50();
        }

        if ((flags >> 1 & 1) != 0) {
            FUN_0052a170();
            if ((&DAT_01198ed8)[DAT_0121bf30 * 0x1b] != 0) {
                FUN_0060add0(DAT_0121be9c, (&DAT_01198ed8)[DAT_0121bf30 * 0x1b], extraout_ECX);
            }
        }

        // Common cleanup and final clamping
        FUN_0053d9d0();
        FUN_00609810(1);

        if (bHasBothParams) {
            FUN_0052ae50();
        }
        else {
            FUN_00528070();
        }

        FUN_00612e00();

        // Repeat clamping for second set of settings
        if (DAT_012058d0 < 0x16) {
            DAT_012058d0 = 0x16;
        }
        if (0x16 < DAT_00f15988) {
            DAT_00f15988 = 0x16;
        }
        _DAT_011f3a30 = 1;
        if (DAT_012058d0 < 7) {
            DAT_012058d0 = 7;
        }
        if (7 < DAT_00f15988) {
            DAT_00f15988 = 7;
        }
        _DAT_011f39f4 = 1;
        if (DAT_012058d0 < 0xe) {
            DAT_012058d0 = 0xe;
        }
        if (0xe < DAT_00f15988) {
            DAT_00f15988 = 0xe;
        }
        _DAT_011f3a10 = 1;
        if (DAT_012058d0 < 0x19) {
            DAT_012058d0 = 0x19;
        }
        if (0x19 < DAT_00f15988) {
            DAT_00f15988 = 0x19;
        }
        _DAT_011f3a3c = 7;
        if (DAT_012058d0 < 0x18) {
            DAT_012058d0 = 0x18;
        }
        if (0x18 < DAT_00f15988) {
            DAT_00f15988 = 0x18;
        }
        _DAT_011f3a38 = 0;
        if (DAT_012058d0 < 0xf) {
            DAT_012058d0 = 0xf;
        }
        if (0xf < DAT_00f15988) {
            DAT_00f15988 = 0xf;
        }
        _DAT_011f3a14 = 0;
        if (DAT_012058d0 < 0x1b) {
            DAT_012058d0 = 0x1b;
        }
        if (0x1a < DAT_00f15988) {
            DAT_00f15988 = 0x1b;
        }
        _DAT_011f3a44 = 0;

        FUN_00417cf0(1, 5, 6);
    }
    return;
}