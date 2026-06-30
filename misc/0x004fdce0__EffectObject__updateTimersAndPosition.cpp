// FUNC_NAME: EffectObject::updateTimersAndPosition

void __thiscall EffectObject::updateTimersAndPosition(void *pOwner, float deltaTime)
{
    float *pTransform;
    int iVar2;
    bool bIsLocalSpace;
    float fVar4;
    float fVar5;
    float posOffset[4];
    float finalPos[4];

    // Check if object is active (bit0 of flags at +0x78)
    if ((*(byte *)(this + 0x78) & 1) == 0) {
        // Decrement timer1 using owner's Y scale and deltaTime
        fVar4 = *(float *)(this + 0x6c) - *(float *)((int)pOwner + 0x44) * deltaTime;
        *(float *)(this + 0x6c) = fVar4;
        if (fVar4 <= 0.0f) {
            // Timer expired: decrement owner's counter and call a secondary function
            *(int *)((int)pOwner + 0x38) = *(int *)((int)pOwner + 0x38) - 1;
            FUN_004fd2c0(); // likely spawn or remove child
        }

        // Update timer2 with damping to a minimum
        fVar4 = DAT_00e3ac58; // global min value (likely 0.0)
        if ((DAT_00e3ac58 < *(float *)(this + 0x70)) &&
            (fVar5 = *(float *)(this + 0x70) - *(float *)((int)pOwner + 0x40) * deltaTime,
             bIsLocalSpace = fVar5 <= DAT_00e3ac58, *(float *)(this + 0x70) = fVar5, bIsLocalSpace)) {
            *(float *)(this + 0x70) = fVar4;
        }

        // Decrement timer3 and reset when it reaches zero
        deltaTime = *(float *)(this + 0x74) - deltaTime;
        *(float *)(this + 0x74) = deltaTime;
        if (deltaTime <= 0.0f) {
            fVar5 = *(float *)(*(int *)((int)pOwner + 0x28) + 0x90); // owner's scale
            fVar4 = fVar5;
            FUN_004e41b0(); // random function
            fVar5 = (fVar4 + DAT_00e2b1a4) * fVar5;
            *(float *)(this + 0x74) = fVar5;
            FUN_004e41b0(); // random function
            *(float *)(this + 0x70) = fVar5 * DAT_00e2cd54 + DAT_00e2cd54;
        }

        // Determine if the owner's owner is in world space (bit0 of its flags)
        bIsLocalSpace = (*(byte *)(*(int *)((int)pOwner + 0x28) + 0x24) & 1) == 0;
        if (bIsLocalSpace) {
            // Local space: use stored offset directly
            posOffset[0] = *(float *)(this + 0x40);
            posOffset[1] = *(float *)(this + 0x44);
            posOffset[2] = *(float *)(this + 0x48);
            posOffset[3] = *(float *)(this + 0x4c);
        } else {
            // World space: add parent world transform translation
            pTransform = (float *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x80 +
                                   *(int *)((int)pOwner + 0x10));
            posOffset[3] = pTransform[3];
            posOffset[0] = *(float *)(this + 0x40) + pTransform[0];
            posOffset[1] = *(float *)(this + 0x44) + pTransform[1];
            posOffset[2] = *(float *)(this + 0x48) + pTransform[2];
        }

        // Check for linked child object (at +0x7c)
        iVar2 = *(int *)(this + 0x7c);
        if ((iVar2 == 0) || ((*(byte *)(*(int *)(iVar2 + 0x28) + 0x24) & 1) == 0)) {
            // No child or in local space: use local second offset
            finalPos[0] = *(float *)(this + 0x50);
            finalPos[1] = *(float *)(this + 0x54);
            finalPos[2] = *(float *)(this + 0x58);
            finalPos[3] = *(float *)(this + 0x5c);
            if (bIsLocalSpace) {
                return; // early exit in local space case
            }
        } else {
            // Child exists and is in world space: add its parent's world transform
            pTransform = (float *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x80 +
                                   *(int *)(iVar2 + 0x10));
            finalPos[3] = pTransform[3];
            finalPos[0] = *(float *)(this + 0x50) + pTransform[0];
            finalPos[1] = *(float *)(this + 0x54) + pTransform[1];
            finalPos[2] = *(float *)(this + 0x58) + pTransform[2];
        }

        // Final processing of the position (opposite offset addition)
        FUN_004fd350(finalPos); // likely applies the offset to world position
    }
}