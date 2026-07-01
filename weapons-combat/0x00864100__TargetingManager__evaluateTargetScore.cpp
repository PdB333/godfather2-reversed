// FUNC_NAME: TargetingManager::evaluateTargetScore

// Reconstructed from Ghidra at 0x00864100
// This function evaluates the desirability/score of a potential target (or action) for the AI.
// It compares the target's heuristic score against alternative offers and decides whether to select it.
// Returns: 0x7f (high priority) if target is excellent, -4 if below minimum threshold,
//          or a clamped score in [0, 0x7f] based on weighted calculations.

int __thiscall TargetingManager::evaluateTargetScore(
    int thisPtr,               // this (offsets: +0xFD4, +0xFD0, +0xC88)
    int offerDataPtr,          // +0x7c, +0x84, +0x88, +0x90 – position/entity data
    const OfferDescriptor* offer1, // *offer1 = int id, offer1[2] = int count? 
    const OfferDescriptor* offer2  // *offer2 = int id, offer2[2] = float someValue
)
{
    float score1;
    float fVar4;
    float fVar9;
    float fVar13;
    uint uVar10;
    int iVar6;
    int iVar7;
    float* pfVar2;
    float* pfVar8;
    bool bVar3;
    char cVar5;
    float local_34;
    float local_38;
    uint local_30;
    int local_2c;
    float local_28;
    // The following represent a 3x4 transform matrix (probably camera or world-to-local)
    struct TransformMatrix {
        undefined8 m0;  // +0x00
        undefined4 m8;  // +0x08
    } localTransform;   // from worldContext + 0x20
    float local_18;
    float local_14;
    float local_10;     // delta vector
    float local_18_dup; // reused

    // Default initial value
    fVar9 = 0.0f;

    // Check target count? (offset 0xFD4)
    if ((*(uint*)(thisPtr + 0xFD4) & 0x7FFFFFFF) < 2) {
        return 0;
    }

    // Get global world/context pointer (FUN_00471610 likely returns a singleton WorldManager)
    iVar6 = WorldManager::getInstance();
    // Copy camera/world transform from context +0x20
    localTransform = *(undefined8*)(iVar6 + 0x20);
    // local_4 = *(undefined4*)(iVar6 + 0x28); not used later

    // Retrieve two position arrays from offerDataPtr
    // +0x7c: count of positions, +0x84: pointer to first array, +0x88: count of second? +0x90: pointer to second
    if (*(int*)(offerDataPtr + 0x7c) == 0) {
        pfVar8 = (float*)0x0;
    } else {
        pfVar8 = *(float**)(offerDataPtr + 0x84);
    }
    if (*(int*)(offerDataPtr + 0x88) != 0 &&
        (pfVar2 = *(float**)(offerDataPtr + 0x90), pfVar2 != (float*)0x0) &&
        *(int*)(offerDataPtr + 0x7c) != 0 && pfVar8 != (float*)0x0)
    {
        // Compute delta between the two positions
        local_18 = *pfVar2 - *pfVar8;
        local_14 = pfVar2[1] - pfVar8[1];
        local_10 = pfVar2[2] - pfVar8[2];
        // Transform delta into local coordinate system
        TransformVector(&localTransform, &local_18); // FUN_0043a210
    }

    // Extract data from offer descriptors
    iVar6 = *offer1;  // first int (some ID)
    if (iVar6 == 0) {
        iVar11 = 0;
    } else {
        iVar11 = offer1[2]; // third int? Possibly pointer to sub-offer
    }
    iVar7 = *offer2;
    if (iVar7 != 0) {
        fVar9 = (float)offer2[2]; // float value from offer2
    }

    if (iVar6 == 0 || iVar11 == 0 || iVar7 == 0 || fVar9 == 0.0f) {
        return 0;
    }

    // Compute initial heuristic score via FUN_0085f560
    float score = (float)FUN_0085f560(iVar6, iVar11, iVar7, fVar9, &localTransform);
    float scoreMasked = (float)((uint)score & s_scoreMask); // DAT_00e44680 (mask for low bits?)
    if (s_minThreshold < scoreMasked) { // DAT_00d757e4
        return -4;
    }

    // Special case: sum of three bytes equals 1 -> immediate high priority
    if ((uint)*(byte*)(iVar11 + 0x1c) +
        (uint)*(byte*)(iVar11 + 0x15) +
        (uint)*(byte*)(iVar11 + 0x14) == 1)
    {
        return 0x7F;
    }

    // Mode check: single target mode (offset 0xFD0 == 1)
    if (*(int*)(thisPtr + 0xFD0) == 1) {
        int evalResult = FUN_008628e0(iVar6, iVar11, iVar7, fVar9);
        if (evalResult == 2 && scoreMasked < s_upperThreshold) { // DAT_00e447a4
            return 0x7F;
        }
        // Weighted scaling using global constants
        fVar9 = (score + s_offsetConst) * s_factorConst * s_clampUpper; // DAT_00d5eeec, _DAT_00d5eee8, DAT_00d7589c
        if (fVar9 > 0.0f) {
            if (s_clampUpper <= fVar9) {
                fVar9 = s_clampUpper;
            }
            return (int)fVar9;
        }
        return 0;
    }

    // Multi-target comparison mode
    int evalResult = FUN_008628e0(iVar6, iVar11, iVar7, fVar9);
    if (evalResult == 2 && scoreMasked < s_upperThreshold) {
        return 0x7F;
    }

    uVar10 = 0;
    bVar3 = false;
    int* countBetter = (int*)0x0; // reused param_3 as counter of better offers

    // First loop: if byte at iVar11+0x14 is non-zero (primary offer/action list)
    if (*(char*)(iVar11 + 0x14) != '\0') {
        do {
            int index = (uint)(ushort)(*(short*)(iVar11 + 0x10) + (short)uVar10) * 0x10 +
                        *(int*)(iVar6 + 0x24);
            float otherVal = (float)(*(int*)(iVar6 + 0x20) + (uint)*(ushort*)(index + 4) * 0x24);
            if (otherVal != fVar9 && (*(byte*)(index + 10) & 1) == 0) {
                float checkVal = 0.0f;
                // Call with a magic number 0xc2e43267 (approx -45.689) – maybe distance max squared?
                cVar5 = FUN_005fd340(*(undefined2*)(index + 8), 0xc2e43267, &checkVal);
                if (cVar5 == '\0' ||
                    (cVar5 = FUN_006a7fd0(&local_30), cVar5 == '\0' || local_30 == 0) ||
                    (*(uint*)(thisPtr + 0xC88) & 0x802) != 0)
                {
                    // Evaluate alternative score
                    float altScore = (float)FUN_0085f560(iVar6, iVar11, iVar6, otherVal, &localTransform);
                    float altMasked = (float)((uint)altScore & s_scoreMask);
                    if (altMasked <= s_minThreshold) {
                        int altEval = FUN_008628e0(iVar6, iVar11, iVar6, otherVal);
                        if (altEval == 2 && altMasked < s_upperThreshold) {
                            bVar3 = true;
                            break;
                        }
                        if (score < altScore) {
                            countBetter = (int*)((int)countBetter + 1);
                        }
                        if ((int)countBetter > 1) {
                            goto LAB_00864452;
                        }
                    }
                }
            }
            uVar10 += 1;
        } while (uVar10 < *(byte*)(iVar11 + 0x14));

        if ((int)countBetter < 2) {
            if (bVar3) {
                return 0;
            }
            // Fall through to second loop
        } else {
            goto LAB_00864452;
        }
    }

    // Second loop (when primary list is empty)
    if (*(char*)(iVar11 + 0x14) == '\0') {
LAB_0086443e:
        local_30 = 0;
        if ((uint)*(byte*)(iVar11 + 0x1c) + (uint)*(byte*)(iVar11 + 0x15) == 0) goto LAB_00864452;
        do {
            int index2 = (uint)(ushort)(*(short*)(iVar11 + 0x16) + (short)local_30) * 0x10 +
                         *(int*)(iVar6 + 0x30);
            if ((*(byte*)(index2 + 10) & 1) == 0) {
                // Use local variables for temporary computation
                // (local_20, local_1c are unused except for passing to functions)
                cVar5 = FUN_005fd340(*(undefined2*)(index2 + 8), 0xc2e43267, &local_20);
                if (cVar5 == '\0' ||
                    (cVar5 = FUN_006a7fd0(&local_2c), cVar5 == '\0') ||
                    local_2c == 0 ||
                    (*(uint*)(thisPtr + 0xC88) & 0x802) != 0)
                {
                    // Get additional data from index2? Possibly a link to another object
                    FUN_005fd1c0(&local_18, index2);
                    local_34 = 0.0f;
                    local_38 = 0.0f;
                    cVar5 = FUN_005f5cb0(&local_34, &local_38);
                    fVar4 = local_34;
                    fVar13 = local_38;
                    if (cVar5 != '\0' && local_38 != fVar9) {
                        float altScore2 = (float)FUN_0085f560(iVar6, iVar11, local_34, local_38, &localTransform);
                        local_34 = altScore2;
                        float altMasked2 = (float)((uint)altScore2 & s_scoreMask);
                        if (altMasked2 <= s_minThreshold) {
                            int altEval2 = FUN_008628e0(iVar6, iVar11, fVar4, fVar13);
                            if (altEval2 == 2 && altMasked2 < s_upperThreshold) {
                                bVar3 = true;
                            }
                            if (fVar1 < local_34) {
                                countBetter = (int*)((int)countBetter + 1);
                            }
                            if ((int)countBetter > 1) {
                                if (local_18 != 0.0f) {
                                    FUN_004daf90(&local_18);
                                }
                                break;
                            }
                        }
                    }
                    if (local_18 != 0.0f) {
                        FUN_004daf90(&local_18);
                    }
                }
            }
            local_30 += 1;
        } while (local_30 < (uint)*(byte*)(iVar11 + 0x1c) + (uint)*(byte*)(iVar11 + 0x15));
    }

    if (bVar3) {
        return 0;
    }

LAB_00864452:
    // Final return: if countBetter == 1, return 0x7F; else 0x7F - (countBetter != 1 ? 0x81 : 0)
    return (-(uint)(countBetter != (int*)0x1) & 0xFFFFFF81) + 0x7F;
}