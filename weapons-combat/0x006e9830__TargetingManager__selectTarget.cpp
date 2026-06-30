// FUNC_NAME: TargetingManager::selectTarget
// Address: 0x006e9830
// Selects the best target from an internal list based on distance, facing, and probability.
// param_1: this pointer (TargetingManager)
// param_2: entity ID or pointer for the source (e.g., NPC that is targeting)
// param_3: if zero – normal selection; nonzero – release target (decrement aggro)
// param_4: optional filter callback (can be null)
// Returns: pointer to the best target entity, or 0 if none found.

int __thiscall TargetingManager::selectTarget(int thisPtr, int sourceEntity, char releaseFlag, undefined4* filterCallback)
{
    float* pfVar1;
    float fVar2;
    float fVar3;
    char cVar4;
    int* piVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    int iVar10;
    float* pfVar11;
    float10 fVar12;
    int bestTarget = 0;
    float bestDistance = g_maxTargetDistance; // DAT_00d5f6f0

    if (sourceEntity == 0) {
        return 0;
    }

    // Check if sourceEntity has a current target (offset 0x24c4)
    if (*(int*)(sourceEntity + 0x24c4) == 0) {
        iVar10 = 0;
    } else {
        iVar10 = *(int*)(sourceEntity + 0x24c4) - 0x48; // Convert to interior pointer
        if (iVar10 != 0) goto LAB_006e988e;
    }

    // Fallback: try to get player's current target via some global
    piVar5 = (int*)getPlayer(); // FUN_00722220
    if (piVar5 != (int*)0x0) {
        if (*piVar5 == 0) {
            iVar10 = 0;
        } else {
            iVar10 = *piVar5 - 0x48;
        }
    }

LAB_006e988e:
    // Get the view/camera position from the game manager (global at 0x012233a0)
    piVar5 = (int*)**(int**)(g_gameManager + 4); // Assume g_gameManager is a pointer
    if ((piVar5 == (int*)0x0) || (piVar5 == (int*)0x1f30)) {
        return 0;
    }
    iVar6 = (**(code**)(*piVar5 + 0xc))(); // Call virtual function at vtable+0xc (likely getCurrentCamera or getViewer)

    if ((iVar6 != 0) && (iVar10 != 0)) {
        // Get viewer (camera) position
        iVar7 = getViewerPosition(); // FUN_00471610
        pfVar11 = (float*)(iVar7 + 0x30); // Assume vector3 at offset 0x30

        iVar8 = getViewerPosition(); // FUN_00471610 again (maybe different view?)
        float dx1 = *(float*)(iVar8 + 0x30) - *pfVar11;
        float dy1 = *(float*)(iVar8 + 0x34) - *(float*)(iVar7 + 0x34);
        float dz1 = *(float*)(iVar8 + 0x38) - *(float*)(iVar7 + 0x38);
        vectorNormalize(&dx1, &dx1); // FUN_0043a210 – normalize direction

        iVar8 = getViewerPosition(); // yet another? Or same?
        float dx2 = *(float*)(iVar8 + 0x30) - *pfVar11;
        float dy2 = *(float*)(iVar8 + 0x34) - *(float*)(iVar7 + 0x34);
        float dz2 = *(float*)(iVar8 + 0x38) - *(float*)(iVar7 + 0x38);
        vectorNormalize(&dx2, &dx2);

        uint uIndex = 0;
        if (*(int*)(thisPtr + 0x1c) == 0) {
            return 0;
        }
        do {
            // Get current target from the list (offset 0x18)
            iVar8 = *(int*)(*(int*)(thisPtr + 0x18) + uIndex * 4);
            pfVar1 = (float*)(iVar8 + 0x6c); // target position (x,y,z)

            if (releaseFlag == '\0') {
                // Normal selection branch
                if (iVar8 != 0 &&
                    isValidTarget(sourceEntity) && // FUN_006e9300
                    isVisible(pfVar1) && // FUN_00718d40
                    (filterCallback == 0 || (**(code**)*filterCallback)(iVar8) == '\0'))
                {
                    // Compute distance
                    fVar12 = (float10)vectorDistance(pfVar11, pfVar1); // FUN_0045c470
                    fVar3 = (float)fVar12;

                    if (fVar12 < (float10)1.0f) {
                        // Very close – return immediately
                        return iVar8;
                    }

                    // Check angle and probability
                    float dy = *(float*)(iVar7 + 0x34) - *(float*)(iVar8 + 0x70);
                    float mask = *(float*)(&g_angleMask); // DAT_00e44680
                    float angleDiff = (float)((uint)dy & (uint)mask); // Funky angle check
                    if (angleDiff < g_angleThreshold // DAT_00d5eee4
                        && (fVar2 = *(float*)(iVar8 + 0xa0), iVar9 = _rand(), (float)iVar9 * g_randMultiplier < fVar2) // DAT_00e44590
                        && (fVar3 < *(float*)(iVar8 + 0xa4) && fVar3 < bestDistance))
                    {
                        // Compute dot product between target direction and viewer direction
                        float tx = *pfVar1 - *pfVar11;
                        float ty = *(float*)(iVar8 + 0x70) - *(float*)(iVar7 + 0x34);
                        float tz = *(float*)(iVar8 + 0x74) - *(float*)(iVar7 + 0x38);
                        vectorNormalize(&tx, &tx);

                        float dot1 = ty * dy1 + tx * dx1 + tz * dz1;
                        float dot2 = dy2 * ty + dx2 * tx + dz2 * tz;

                        if (dot1 < g_dotThreshold // DAT_00d5fb04
                            && (iVar10 == iVar6 || dot2 < g_dotThreshold))
                        {
                            bestTarget = iVar8;
                            bestDistance = fVar3;
                        }
                    }
                }
            } else {
                // Release target branch
                piVar5 = (int*)(iVar8 + 0x98); // owner pointer
                if (*(int*)(iVar8 + 0x98) == 0) {
                    iVar9 = 0;
                } else {
                    iVar9 = *(int*)(iVar8 + 0x98) - 0x48;
                }
                if (iVar9 == sourceEntity) {
                    // This target is owned by sourceEntity – clear ownership and decrement aggro count
                    if (*piVar5 != 0) {
                        clearTarget(piVar5); // FUN_004daf90
                        *piVar5 = 0;
                    }
                    *(char*)(iVar8 + 0xa8) = *(char*)(iVar8 + 0xa8) - 1;
                }
            }
            uIndex++;
        } while (uIndex < *(uint*)(thisPtr + 0x1c));
    }

    return bestTarget;
}