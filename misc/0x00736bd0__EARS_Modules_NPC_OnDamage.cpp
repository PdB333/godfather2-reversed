// Xbox PDB: EARS::Modules::NPC::OnDamage
// FUNC_NAME: CombatComponent::updateAttackState
void __thiscall CombatComponent::updateAttackState(int thisPtr, int targetInfo, uint attackType)
{
    // thisPtr: points to CombatComponent (offset 0x394 from parent Character/Player)
    // targetInfo: pointer to some target state struct (offset 0x48 from base)
    // attackType: 0,1,2,3 - type of attack/action

    char cVar1;
    int *targetBasePtr;
    int iVar3;
    uint uVar4;
    uint uVar5;
    int iVar6;
    int *piVar7;
    bool bIsTargetValid;
    float fTime;
    uint uStack_68;
    uint uStack_64;
    uint uStack_60;
    undefined4 uStack_5c;
    undefined ***pppuStack_58;
    undefined1 uStack_54;
    int aiStack_48[2];
    undefined1 auStack_40[16];
    byte bStack_30;
    int aiStack_2c[2];
    undefined **ppuStack_24;
    undefined4 uStack_20;
    int iStack_1c;
    undefined4 uStack_18;
    undefined8 uStack_14;
    undefined4 uStack_c;
    undefined1 uStack_8;
    undefined4 uStack_4;

    // Compute parent object (character) pointer
    // parent character is located 0x394 bytes before this component
    int *character = (int *)(thisPtr - 0x394);
    if (character == (int *)0x0) {
        piVar7 = (int *)0x0;
    } else {
        // Access some global manager? Maybe getTimeManager or similar
        piVar7 = (int *)getGlobalManager(DAT_01131018);
    }

    // Get current frame time from virtual func at vtable+0x28
    // This is likely a method of a time manager or game state
    fTime = (float)(**(code **)(*piVar7 + 0x28))();

    piVar7 = (int *)0x0;
    // Check the target object pointer from targetInfo+0x0c
    // If null or the special value 0x48, treat as no target
    if ((*(int *)(targetInfo + 0x0c) == 0) || (*(int *)(targetInfo + 0x0c) == 0x48)) {
        uStack_68 = 0;
    } else {
        // Compute base pointer: target object - 0x48
        if (*(int *)(targetInfo + 0x0c) != 0) {
            piVar7 = (int *)(*(int *)(targetInfo + 0x0c) - 0x48);
        }
        uStack_64 = 0;
        // Call virtual function at vtable+0x10 (likely some identification) with hash 0x383225a1
        cVar1 = (**(code **)(*piVar7 + 0x10))(0x383225a1, &uStack_64);
        uStack_68 = -(uint)(cVar1 != '\0') & uStack_64;
    }

    bIsTargetValid = uStack_68 != 0;
    if (bIsTargetValid) {
        // If time <= 0 (e.g., dead or inactive?), set flags
        if (fTime <= (float)0) {
            *(uint *)(thisPtr + 0x1bc8) = *(uint *)(thisPtr + 0x1bc8) | 0x2000000;
            *(uint *)(thisPtr + 0x1bc8) = *(uint *)(thisPtr + 0x1bc8) & 0xf3ffffff;
        } else if (*(int *)(targetInfo + 0x30) == 3) {
            // Attack type 3 (heavy attack?)
            *(uint *)(thisPtr + 0x1bc8) = *(uint *)(thisPtr + 0x1bc8) | 0x8000000;
        } else {
            // Other attack types
            *(uint *)(thisPtr + 0x1bc8) = *(uint *)(thisPtr + 0x1bc8) | 0x4000000;
        }
    }

    // Delegate to another update function (maybe animation update) with targetInfo and attackType
    FUN_00806590(targetInfo, attackType);

    // Check if currently attacking (bit 8 of +0x1bc0)
    if ((*(uint *)(thisPtr + 0x1bc0) >> 8 & 1) != 0) {
        if (*(int *)(targetInfo + 0x0c) == 0) {
            iStack_1c = 0;
        } else {
            iStack_1c = *(int *)(targetInfo + 0x0c) - 0x48;
        }
        ppuStack_24 = &PTR_FUN_00d5dbbc; // Some global function pointer array
        uStack_20 = 0x4e268f5b; // Hash for something
        if (iStack_1c == 0) {
            iStack_1c = 0;
        } else {
            iStack_1c = iStack_1c + 0x48;
        }
        uStack_18 = 0;
        if (iStack_1c != 0) {
            uStack_18 = *(undefined4 *)(iStack_1c + 4);
            *(int **)(iStack_1c + 4) = &iStack_1c;
        }
        uStack_c = 0;
        uStack_14 = 0;
        uStack_8 = 0;
        uStack_4 = DAT_01205228;
        // Get some system object
        iVar3 = FUN_00471610();
        uStack_8 = 1;
        uStack_14 = *(undefined8 *)(iVar3 + 0x30);
        uStack_c = *(undefined4 *)(iVar3 + 0x38);
        pppuStack_58 = &ppuStack_24;
        uStack_5c = DAT_0112ad8c;
        uStack_54 = 0;
        // Log or send message with these parameters
        FUN_00408a00(&uStack_5c, 0);
        if (iStack_1c != 0) {
            FUN_004daf90(&iStack_1c);
        }
    }

    // Check health/state via virtual function at vtable+0xc0 (e.g., isAlive?)
    fTime = (float)(**(code **)(*character + 0xc0))();
    if (fTime <= (float)0) {
        // If health <= 0, call virtual at +0xc4 (maybe die/cleanup)
        (**(code **)(*character + 0xc4))();
    }

    // Get current action (0 = idle, 1 = attack, 2 = block, etc.)
    uStack_60 = FUN_007f41e0();
    if ((uStack_60 != 0) && (attackType != 3)) {
        fTime = (float)(**(code **)(*character + 0xc0))();
        if (fTime <= (float)0) {
            // If dead, force idle animation
            FUN_004abc20(1);
        }

        // If in attack state (targetInfo+0x30 == 1) and target is valid
        if ((((*(int *)(targetInfo + 0x30) == 1) && (bIsTargetValid)) &&
            (iVar3 = FUN_00625050(0xc4bc3ce7, 0), iVar3 != 0)) && // Check some condition
            (iVar3 = FUN_007e24b0(), iVar3 == thisPtr - 0x394)) {
            // Play a sound or effect
            uVar4 = 0;
            uVar5 = FUN_006fbc40(0, 0);
            FUN_007f96a0(0x20eb8823, 0x40, uVar5, uVar4);
            FUN_006fbc70();
        }

        // Check if blocking/parrying is allowed (bit 6 of +0x54c)
        if ((*(uint *)(thisPtr + 0x54c) >> 6 & 1) == 0) {
            // Resolve target's base pointer
            if ((*(int *)(targetInfo + 0x0c) == 0) || (*(int *)(targetInfo + 0x0c) == 0x48)) {
                iVar3 = 0;
            } else {
                if (*(int *)(targetInfo + 0x0c) == 0) {
                    iVar3 = 0;
                } else {
                    iVar3 = *(int *)(targetInfo + 0x0c) - 0x48;
                }
                iVar3 = FUN_006b1c70(iVar3, 0x55859efa); // Check if target is a specific type
            }

            int attackState = *(int *)(targetInfo + 0x30);
            if (attackState == 1) {
                // Light attack handling
                if (((*(uint *)(thisPtr + 0x54c) >> 0xb & 1) == 0) ||
                    (cVar1 = FUN_00690150(0xf), cVar1 != '\0')) {
                    if ((*(uint *)(thisPtr + 0x550) >> 0xd & 1) == 0) {
                        if ((*(uint *)(thisPtr + 0x1800) >> 0xd & 1) == 0) {
                            uVar4 = 1;
                            if (((*(char *)(thisPtr + 0x17f8) == '\0') && (iVar3 != 0)) &&
                                (cVar1 = FUN_007f7c50(), cVar1 == '\0')) {
                                uVar5 = FUN_00690150(0x10);
                                cVar1 = FUN_00719550(uVar5);
                                if (cVar1 != '\0') {
                                    uVar4 = 0x20000;
                                }
                            }
                            FUN_004abc20(uVar4);
                        }
                    } else {
                        // If can block and target is valid
                        if (iVar3 != 0) {
                            iVar6 = FUN_00691810();
                            if ((iVar6 != 0) && ((*(uint *)(iVar3 + 0x8e0) >> 10 & 1) != 0)) {
                                cVar1 = FUN_00736b20(targetInfo);
                                uVar4 = 1;
                                if (cVar1 == '\0') {
                                    FUN_004abc20(uVar4);
                                } else {
                                    FUN_0072cb30(targetInfo, 1);
                                }
                            }
                        }
                        *(undefined4 *)(thisPtr + 0x1d94) = 0;
                    }
                } else {
                    FUN_0072cb30(targetInfo, 0);
                    (**(code **)(*character + 500))("exertion_grunt"); // Play grunt sound
                    if ((iVar3 == 0) || (cVar1 = FUN_00690150(0x37), cVar1 == '\0')) {
                        *(undefined4 *)(thisPtr + 0x1d94) = 0;
                    } else {
                        *(int *)(thisPtr + 0x1d94) = *(int *)(thisPtr + 0x1d94) + 1;
                    }
                }

                // Random chance to set stagger/stun flags
                if ((((*(uint *)(thisPtr + 0x1bc0) >> 0x16 & 1) == 0) &&
                    ((*(uint *)(thisPtr + 0x1800) >> 4 & 1) == 0)) &&
                   (((iVar3 = _rand(), iVar3 % 100 < 0x19 && ((*(uint *)(targetInfo + 0x44) >> 5 & 1) != 0)) ||
                    (((((*(uint *)(thisPtr + 0x1bc8) >> 0xb & 1) != 0 &&
                       (cVar1 = FUN_00690150(0x2d), cVar1 == '\0')) &&
                      ((cVar1 = FUN_00690150(0xb), cVar1 == '\0' ||
                       (cVar1 = FUN_00690150(0xf), cVar1 != '\0')))) &&
                     ((bIsTargetValid && ((*(uint *)(targetInfo + 0x44) >> 5 & 1) == 0)))))))) {
                    *(uint *)(thisPtr + 0x1800) = *(uint *)(thisPtr + 0x1800) | 0x18;
                    *(uint *)(thisPtr + 0x1800) = *(uint *)(thisPtr + 0x1800) & 0xfffffffd;
                    FUN_00800010();
                }
                *(uint *)(thisPtr + 0x1bc8) = *(uint *)(thisPtr + 0x1bc8) & 0xfffff7ff;
            } else if (attackState != 6) {
                // Not light attack, not block state
                if (((attackType == 2) || (*(char *)(thisPtr + 0x17f8) == '\0')) ||
                   ((attackState == 4 || (*(int *)(thisPtr + 0x1b40) != 0x637b907)))) {
                    cVar1 = FUN_00736b20(targetInfo);
                    if (cVar1 == '\0') {
                        // Fall through to set idle
                        FUN_004abc20(1);
                    } else {
                        FUN_0072cb30(targetInfo, 1);
                    }
                } else {
                    FUN_0072cb30(targetInfo, 1);
                }
            }
        } else {
            // Blocking enabled, check if attack type is 4 or has certain flag
            if ((*(int *)(targetInfo + 0x30) == 4) ||
                (uVar5 = FUN_0084d420(*(int *)(targetInfo + 0x30)), (uVar5 & 8) != 0)) {
                FUN_004abc20(1);
            }
        }

        // Track consecutive hits on same target
        if (bIsTargetValid) {
            iVar3 = *(int *)(uStack_68 + 0x3094); // Target ID/hash
            if ((iVar3 == *(int *)(thisPtr + 0x1d9c)) && (iVar3 != -1)) {
                *(int *)(thisPtr + 0x1d98) = *(int *)(thisPtr + 0x1d98) + 1;
            } else {
                *(undefined4 *)(thisPtr + 0x1d98) = 0;
            }
            *(int *)(thisPtr + 0x1d9c) = iVar3;
        }
    }

    // Get flags for current attack type
    uVar5 = FUN_0084d420(*(undefined4 *)(targetInfo + 0x30));

    // Re-check target validity (bVar8 again)
    if (((bIsTargetValid) && (*(int *)(targetInfo + 0x0c) != 0)) && (*(int *)(targetInfo + 0x0c) != 0x48)) {
        if (*(int *)(targetInfo + 0x0c) == 0) {
            piVar7 = (int *)0x0;
        } else {
            piVar7 = (int *)(*(int *)(targetInfo + 0x0c) - 0x48);
        }
        uStack_60 = 0;
        cVar1 = (**(code **)(*piVar7 + 0x10))(0x383225a1, &uStack_60);
        attackType = -(uint)(cVar1 != '\0') & uStack_60;
    } else {
        attackType = 0;
    }

    // Handle target object (targetInfo+4) if valid and has flags
    if (((*(int *)(targetInfo + 4) != 0) && (*(int *)(targetInfo + 4) != 0x48)) && (uVar5 != 0)) {
        if (attackType != 0) {
            // Check if we should cancel current attack due to new target
            if ((((uVar5 & 2) != 0) && (iVar3 = thisPtr + 0x1d4c, *(int *)(thisPtr + 0x1d4c) != 0)) ||
               (((uVar5 & 4) == 0 && (iVar3 = thisPtr + 0x1d54, *(int *)(thisPtr + 0x1d54) != 0)))) {
                FUN_007fff40(iVar3);
            }
            fTime = (float)(**(code **)(*(int *)(thisPtr - 0x394) + 0xc0))();
            if ((float)0 < fTime) {
                FUN_00402050(&DAT_0112b18c, 0);
            }
            if (*(int *)(thisPtr + 0x1d6c) != 0) {
                FUN_00892af0(0);
                FUN_00892ce0(thisPtr - 0x394, 1);
                FUN_00894c40(*(undefined4 *)(thisPtr + 0x1d6c), &uStack_5c);
                *(undefined4 *)(thisPtr + 0x1d6c) = 0;
                if (aiStack_48[0] != 0) {
                    FUN_004daf90(aiStack_48);
                }
            }
        }

        // If attack has block/parry flag
        if ((uVar5 & 4) != 0) {
            uVar4 = 0;
            uVar5 = FUN_006fbc40(0, 0);
            FUN_007f96a0(0xfa431824, 1, uVar5, uVar4);
            FUN_006fbc70();
            if (!bIsTargetValid) {
                fTime = (float)(**(code **)(*(int *)(thisPtr - 0x394) + 0xc0))();
                if ((fTime <= (float)0) && (cVar1 = FUN_0072c080(2), cVar1 != '\0')) {
                    FUN_0072c050(4);
                }
            } else {
                FUN_00402050(&DAT_0112b18c, 0);
                if (*(int *)(thisPtr + 0x1d54) != 0) {
                    FUN_007fff40((int *)(thisPtr + 0x1d54));
                }
                fTime = (float)(**(code **)(*(int *)(thisPtr - 0x394) + 0xc0))();
                if (fTime <= (float)0) {
                    FUN_0072c050(9);
                }
            }
        }

        // Additional cleanup if target is valid
        if ((bIsTargetValid) && (*(int *)(thisPtr + 0x1d44) != 0)) {
            FUN_007fff40(thisPtr + 0x1d44);
        }
    }

    // Finish attack processing
    FUN_00892af0(0);
    FUN_0072f1b0(auStack_40, targetInfo); // Store current target info? Possibly set current attack

    // Check for special finisher attack condition
    if ((((((attackType == 0) || (iVar3 = *(int *)(attackType + 0x74c), iVar3 == 0)) || (iVar3 == 0x48)) ||
         (((*(uint *)(attackType + 0x8e0) >> 10 & 1) == 0 || (*(char *)(iVar3 + 0x160) != '\x01')))) ||
        ((*(uint *)(thisPtr + 0x1800) >> 7 & 1) == 0)) ||
       (((*(int *)(thisPtr + 0xc5c) != 0 && (*(int *)(thisPtr + 0xc5c) != 0x48)) ||
        (cVar1 = FUN_0072c080(2), cVar1 != '\0')))) {
        // Do nothing - go to cleanup
    } else {
        uVar4 = FUN_00806440(); // Get attack type for finisher
        switch(uVar4) {
        case 0:
        case 1:
            uVar4 = 0xfe825136; // Hash for some attack animation
            FUN_00894c40(uVar4, auStack_40);
            break;
        case 2:
            uVar4 = 0x25d50973;
            FUN_00894c40(uVar4, auStack_40);
            break;
        case 3:
            if (*(int *)(thisPtr + 0x1b40) != 0x637b907) {
                uVar4 = 0xeea482af;
                FUN_00894c40(uVar4, auStack_40);
            }
        }
        if ((bStack_30 & 1) != 0) {
            FUN_0072c050(2);
        }
    }

    // Check for special weapon/state (0x637b907 hash)
    iVar3 = *(int *)(thisPtr + 0x1de4);
    if ((((iVar3 != 0) && (iVar3 != 0x48)) && ((*(uint *)(iVar3 + 0x14) >> 0x1d & 1) != 0)) &&
       (*(int *)(thisPtr + 0x1b40) == 0x637b907)) {
        if (((int *)(thisPtr - 0x394) != (int *)0x0) &&
           (iVar3 = FUN_0043b870(DAT_01131040), iVar3 != 0)) {
            *(ushort *)(iVar3 + 0x44) = *(ushort *)(iVar3 + 0x44) & 0xfeff;
            FUN_009b1970(1);
        }
        (**(code **)(*(int *)(thisPtr - 0x394) + 0x1c4))(0x1e96db07); // Execute special attack
        *(uint *)(thisPtr + 0x1bc8) = *(uint *)(thisPtr + 0x1bc8) | 0x8000;
        iVar3 = *(int *)(thisPtr + 0x1de4);
        if ((iVar3 != 0) && (iVar3 != 0x48)) {
            *(uint *)(iVar3 + 0x14) = *(uint *)(iVar3 + 0x14) | 0x40;
        }
        uVar4 = 0;
        uVar5 = FUN_006fbc40(0, 0);
        FUN_007f96a0(0x94d76d17, 0, uVar5, uVar4);
        FUN_006fbc70();
        *(undefined4 *)(thisPtr + 0x1c04) = 1;
    }

    // Clean up local memory
    if (aiStack_2c[0] != 0) {
        FUN_004daf90(aiStack_2c);
    }
    return;
}