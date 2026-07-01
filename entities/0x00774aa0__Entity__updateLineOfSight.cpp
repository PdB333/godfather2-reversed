// FUNC_NAME: Entity::updateLineOfSight
void __thiscall Entity::updateLineOfSight(Entity* thisPtr)
{
    undefined8 *pVec3;
    char cVar2;
    int iVar3;
    int iVar4;
    undefined4 uVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    int hitHandle;
    int bResult;
    undefined4 rayDir;
    undefined4 rayOrigin;
    undefined4 rayEnd;
    undefined1 matrix[12];

    // Check if entity type is valid (not 0 or 0x48 (72))
    if (((*(int *)(thisPtr + 0xc) != 0) && (*(int *)(thisPtr + 0xc) != 0x48)) &&
        // Check target entity type at current target index (array of 8-byte entries at +0x1c)
        ((iVar4 = *(int *)(thisPtr + 0x1c + *(int *)(thisPtr + 0x18) * 8), iVar4 == 0 ||
            // If target type is 0 or 0x48, or if distance to singleton object is too large
            ((iVar4 == 0x48 ||
                (iVar3 = getSingletonObject(),
                 fVar6 = *(float *)(thisPtr + 0x34 + *(int *)(thisPtr + 0x18) * 0xc) -
                         *(float *)(iVar3 + 0x30),
                 iVar4 = thisPtr + 0x34 + *(int *)(thisPtr + 0x18) * 0xc,
                 fVar7 = *(float *)(iVar4 + 4) - *(float *)(iVar3 + 0x34),
                 fVar8 = *(float *)(iVar4 + 8) - *(float *)(iVar3 + 0x38),
                 // Compare distance squared against global threshold
                 gMaxSightDistance <= fVar8 * fVar8 + fVar7 * fVar7 + fVar6 * fVar6))))))
    {
        // Perform line‑of‑sight check
        iVar4 = getSingletonObject();
        bResult = thisPtr + (-0x70); // offset to base object? unused in logic
        setupMatrix(matrix);
        uVar5 = 2;
        rayDir = allocVector();  // FUN_0043b490
        rayOrigin = allocVector();
        rayEnd = 0;

        // Get pointer to the target entity (offset by -0x48 from entityType)
        if (*(int *)(thisPtr + 0xc) == 0) {
            iVar3 = 0;
        }
        else {
            iVar3 = *(int *)(thisPtr + 0xc) + (-0x48);
        }
        // If this target has a sub‑target (at +0xe8) that is valid
        if ((*(int *)(iVar3 + 0xe8) != 0) && (*(int *)(iVar3 + 0xe8) != 0x48)) {
            rayEnd = allocVector();
            uVar5 = 3;
        }

        hitHandle = 0;
        // Raycast from singleton position (iVar4+0x30) using matrix, with collision flags 0x40136 and 0x2020000
        cVar2 = performRaycast(iVar4 + 0x30, matrix, 0x40136, 0x2020000, &rayDir, uVar5, &hitHandle, 0, 0);
        if (cVar2 == 0) {
            // No obstruction: clear flag and copy final ray position to target position
            if (hitHandle != 0) {
                cleanUpHitHandle(hitHandle);
                iVar4 = getSingletonObject();
                pVec3 = (undefined8 *)(thisPtr + 0x34 + *(int *)(thisPtr + 0x18) * 0xc);
                *pVec3 = *(undefined8 *)(iVar4 + 0x30);
                *(undefined4 *)(pVec3 + 1) = *(undefined4 *)(iVar4 + 0x38);
            }
            resetRaycastState();
            return;
        }
        // Obstruction found: set flag 8 (line of sight blocked)
        *(uint *)(thisPtr + 0x14) = *(uint *)(thisPtr + 0x14) | 8;
    }
    return;
}