// FUNC_NAME: Player::handleMovementCommand
// Address: 0x0087afa0
// Reconstructed from Ghidra decompilation. This function appears to process a movement command,
// potentially applying forces, checking thresholds, and triggering animations/effects for a player entity.
// It uses param_2 as a command/input object, param_4 as a transform/velocity source, and this (param_1) as the player.

uint __thiscall Player::handleMovementCommand(int* thisPtr, int* pCommand, undefined4 param3, int* pTransform)
{
    float fVar1;
    int* piVar2;
    char cVar3;
    int* piVar4;
    int iVar5;
    int iVar6;
    undefined4 uVar7;
    undefined4 uVar8;
    int* piVar9;
    float10 extraout_ST0;
    float10 fVar10;
    float fStack_10c;
    float fStack_108;
    float fStack_104;
    int* piStack_100;
    undefined*** pppuStack_fc;
    float fStack_f8;
    float fStack_f4;
    float fStack_f0;
    float fStack_ec;
    float fStack_e8;
    undefined** ppuStack_d8;
    undefined4 uStack_d4;
    undefined4 uStack_d0;
    undefined4 uStack_cc;
    undefined4 uStack_c8;
    float fStack_c4;
    float fStack_c0;
    float fStack_bc;
    float fStack_b8;
    undefined1 auStack_ac[20];
    undefined8 uStack_98;
    undefined4 uStack_90;
    undefined8 uStack_8c;
    uint uStack_84;
    float fStack_80;
    undefined4 uStack_7c;
    undefined4 uStack_74;
    uint uStack_70;
    int iStack_6c;
    undefined1 auStack_60[4];
    undefined1 auStack_5c[8];
    undefined1 auStack_54[80];

    // Check if the command is active (calling virtual at offset 0x78)
    piVar4 = (int*)(**(code**)(*pCommand + 0x78))();
    if (((char)piVar4 != '\0') &&
        // And some other condition (FUN_00543070 might be something like isPaused/disabled)
        (piVar4 = (int*)FUN_00543070(pCommand), (char)piVar4 == '\0'))
    {
        // Get a speed or magnitude from this (virtual at 0x1b0)
        piVar4 = (int*)(**(code**)(*thisPtr + 0x1b0))();
        fStack_104 = (float)extraout_ST0;
        // Compare to global threshold (e.g., minimum speed to process)
        if ((float10)_DAT_00d76490 <= extraout_ST0)
        {
            // Look up a hash value in pCommand's map (0x55859efa = Hash of "move", "input", etc.)
            cVar3 = FUN_006ccde0(pCommand, 0x55859efa, &piStack_100);
            piVar2 = piStack_100;
            if (cVar3 != '\0')
            {
                piVar4 = (int*)FUN_007ff880();
                if (piVar4 == thisPtr) goto LAB_0087b5a4;

                iVar5 = FUN_00471610(); // Possibly get player index or transform
                iVar6 = FUN_00471610();
                if ((*(float*)(iVar6 + 0x34) <= *(float*)(iVar5 + 0x34) &&
                     *(float*)(iVar5 + 0x34) != *(float*)(iVar6 + 0x34)) &&
                    // Check a flag in the command object (bit 0x15 of offset 0x6e5*4 = 0x1B94)
                    (((uint)piVar2[0x6e5] >> 0x15 & 1) == 0))
                {
                    FUN_007f9340(1, 1); // Set some flag or toggle
                }
                piVar4 = (int*)FUN_006bea40(piVar2);
                iVar5 = (**(code**)(*piVar4 + 0x34))();
                if ((*(int*)(iVar5 + 0x30) == 3) &&
                    ((piVar4 = (int*)FUN_00690150(0x10), (char)piVar4 != '\0' ||
                     (*(int*)(iVar5 + 0x40) == DAT_01205224))))
                    goto LAB_0087b5a4;
            }
            // Call virtual at 0x4c to get something (e.g., position, orientation)
            (**(code**)(*thisPtr + 0x4c))(auStack_5c);
            FUN_0043a210(&piStack_100, auStack_60);
            if (piVar2 == (int*)0x0)
            {
                // No command object, use transform directly
                fStack_f4 = (float)pTransform[4];
                fStack_f0 = (float)pTransform[5];
                fStack_ec = (float)pTransform[6];
                fStack_e8 = (float)pTransform[7];
                fStack_104 = (float)pTransform[5] * (float)(int)pppuStack_fc +
                             (float)pTransform[4] * (float)piStack_100 + (float)pTransform[6] * fStack_f8;
                piVar4 = pTransform;
            }
            else
            {
                // Compute direction from two positions
                iVar5 = FUN_00471610();
                iVar6 = FUN_00471610();
                fStack_f4 = *(float*)(iVar6 + 0x30) - *(float*)(iVar5 + 0x30);
                fStack_f0 = *(float*)(iVar6 + 0x34) - *(float*)(iVar5 + 0x34);
                fStack_ec = *(float*)(iVar6 + 0x38) - *(float*)(iVar5 + 0x38);
                piVar4 = (int*)FUN_0054ba20(&fStack_f4, &fStack_f4, 0); // Normalize?
                fStack_104 = fStack_f0 * (float)pppuStack_fc + fStack_f4 * (float)piStack_100 +
                             fStack_ec * fStack_f8;
                fStack_e8 = _DAT_00d5780c;
            }
            // Compare dot product to a large threshold
            if (_DAT_00d76a60 < fStack_104)
            {
                FUN_005403e0(0xcd); // Begin event/sound with ID 0xCD
                FUN_0084dd20();      // Unknown
                FUN_0044b210(thisPtr); // Apply force/animation
                iVar5 = (**(code**)(*thisPtr + 0x1e4))();
                piVar4 = thisPtr;
                if (iVar5 != 0)
                {
                    piVar4 = (int*)(**(code**)(*thisPtr + 0x1e4))();
                }
                FUN_0044b210(piVar4); // Apply to child too
                iVar5 = FUN_00471610();
                uStack_98 = *(undefined8*)(iVar5 + 0x30);
                uStack_90 = *(undefined4*)(iVar5 + 0x38);
                uStack_7c = 3;
                iStack_6c = DAT_01205224;
                cVar3 = FUN_00414d50();
                if (cVar3 == '\0')
                {
                    fVar1 = (float)DAT_01205224;
                    if (DAT_01205224 < 0) {
                        fVar1 = fVar1 + _DAT_00e44578;
                    }
                    if ((float)thisPtr[0x285] <= fVar1) // Offset 0xA14: some field
                    {
                        uVar7 = FUN_00471610();
                        FUN_0044b4e0(auStack_54, uVar7);
                        uVar7 = (**(code**)(*thisPtr + 0x58))(0, 0, 0xffffffff, 0);
                        FUN_004df330(&fStack_10c, thisPtr + 0x27c, auStack_54, uVar7);
                        FUN_00414df0();
                        fVar1 = (float)DAT_01205224;
                        if (DAT_01205224 < 0) {
                            fVar1 = fVar1 + _DAT_00e44578;
                        }
                        thisPtr[0x285] = (int)(fVar1 + (float)thisPtr[0x284]); // Update field
                    }
                }
                // Determine level based on fStack_108 thresholds
                if (fStack_108 <= _DAT_00d76498) {
                    if (fStack_108 <= _DAT_00d76494) {
                        uStack_74 = 1;
                        fStack_10c = _DAT_00d5c454;
                    } else {
                        uStack_74 = 2;
                        fStack_10c = _DAT_00d5c458;
                    }
                } else {
                    uStack_74 = 3;
                    fStack_10c = _DAT_00d5780c;
                }
                piStack_100 = (int*)*pTransform;
                pppuStack_fc = (undefined***)pTransform[1];
                uStack_8c = *(undefined8*)pTransform;
                fStack_f8 = (float)pTransform[2];
                uStack_84 = (uint)fStack_f8;
                if (piVar2 == (int*)0x0) {
                    uStack_70 = 0;
                } else {
                    uStack_70 = (uint)piVar2[0x19c] >> 2; // Offset 0x670: some flag/category
                    iVar5 = FUN_006c9470(piVar2, 0x383225a1); // Hash lookup
                    if ((iVar5 == 0) && (cVar3 = (**(code**)(*piVar2 + 0x1bc))(), cVar3 == '\0')) {
                        fVar1 = *(float*)(thisPtr[0x1f0] + 0xf0); // Offset 0x7C0: speed multiplier
                    } else {
                        fVar1 = *(float*)(thisPtr[0x1f0] + 0xf4); // Offset 0x7C4: another multiplier
                    }
                    fStack_80 = fVar1 * fStack_10c * fStack_104;
                    // Check a flag at thisPtr[0x322]>>2 &1 (Offset 0xC88)
                    if (((uint)thisPtr[0x322] >> 2 & 1) != 0)
                    {
                        iVar5 = FUN_005466a0();
                        fVar10 = (float10)FUN_009efd10(); // Random?
                        fStack_108 = (float)fVar10;
                        fVar10 = (float10)FUN_006b6f90(_DAT_00d5c458);
                        fVar10 = (fVar10 + (float10)_DAT_00d5c458) * (float10)fStack_108 *
                                 (float10)_DAT_00d76a5c;
                        fStack_108 = (float)fVar10;
                        fStack_c0 = fStack_f0 * fStack_108 * _DAT_00d5f520;
                        fStack_c4 = (float)((float10)fStack_f4 * fVar10);
                        fStack_bc = (float)((float10)fStack_ec * fVar10);
                        fStack_b8 = (float)(fVar10 * (float10)fStack_e8);
                        if (*(int*)(iVar5 + 8) != 0) {
                            FUN_005417d0(*(undefined4*)(*(int*)(*(int*)(iVar5 + 8) + 0x6c) + 0x58), &fStack_c4, pTransform);
                        }
                        piVar4 = (int*)**(int**)(_DAT_012233a0 + 4);
                        if (piVar4 == (int*)0x0) {
                            piVar9 = (int*)0x0;
                        } else {
                            piVar9 = piVar4 + -0x7cc;
                            if (piVar9 != (int*)0x0) {
                                fStack_108 = _DAT_01223430;
                                uVar7 = FUN_00799100(2);
                                uVar8 = (**(code**)(*piVar4 + 8))(uVar7);
                                FUN_00444660(uVar8, uVar7);
                            }
                        }
                        uStack_d4 = 0;
                        uStack_d0 = 0;
                        uStack_cc = 0;
                        uStack_c8 = 0;
                        ppuStack_d8 = &PTR_FUN_00d76664;
                        FUN_006ccd30(piVar2);
                        FUN_006ccd30(piVar9);
                        pppuStack_fc = &ppuStack_d8;
                        piStack_100 = _DAT_0112adc0;
                        fStack_f8 = (float)((uint)fStack_f8 & 0xffffff00);
                        FUN_00408a00(&piStack_100, 0);
                        FUN_00875860();
                    }
                }
                FUN_00408bb0(&_DAT_0112dd94, pCommand + 0xf, auStack_ac, 0);
                FUN_00540410(0xcd); // End event/sound
                piVar4 = (int*)FUN_0070aaf0();
            }
        }
    }
LAB_0087b5a4:
    return (uint)piVar4 & 0xffffff00;
}