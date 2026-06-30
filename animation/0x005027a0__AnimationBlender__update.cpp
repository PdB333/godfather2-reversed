// FUNC_NAME: AnimationBlender::update
// Address: 0x005027a0
// This function updates an animation blend state with ghost interpolation for network smoothing.
// It manages a sliding window of keyframes, computes interpolated positions/rotations,
// and handles blending between ghost (predicted) and authoritive (server) data.

void __thiscall AnimationBlender::update(int* thisPtr, float deltaTime)
{
    float* frameData;
    int* fsPtr;
    short sVar3;
    undefined4 uVar4;
    float fVar5;
    float fVar6;
    bool bVar7;
    char cVar8;
    short sVar9;
    short sVar10;
    int iVar11;
    uint* puVar12;
    float* pfVar13;
    undefined8* puVar14;
    int iVar15;
    int iVar16;
    float* pfVar17;
    int unaff_FS_OFFSET;
    float fVar18;
    float fVar19;
    float fVar20;
    float fVar21;
    float fVar22;
    float local_50;
    float local_40;
    float fStack_3c;
    float fStack_38;

    // Accumulate delta time into the timer (offset 0x34)
    thisPtr[0xd] = (int)(deltaTime + (float)thisPtr[0xd]);

    // Get pointer to thread-local storage for exception handling
    fsPtr = *(int**)(unaff_FS_OFFSET + 0x2c);

    // Decrease blend time (offset 0x38) by character speed * delta (characterInfo+0x30)
    thisPtr[0xe] = (int)((float)thisPtr[0xe] - *(float*)(thisPtr[9] + 0x30) * deltaTime);

    // Handle action timer (offset 0x44)
    if ((0.0 < (float)thisPtr[0x11]) &&
        (deltaTime = (float)thisPtr[0x11] - deltaTime, thisPtr[0x11] = (int)deltaTime, deltaTime < 0.0))
    {
        iVar11 = *fsPtr;
        thisPtr[0x11] = 0;
        // Set a flag to indicate action ended
        puVar12 = (uint*)(thisPtr[4] + *(int*)(iVar11 + 8));
        *puVar12 = *puVar12 | 1;
    }

    // If the accumulated time (offset 0x34) exceeds max time (characterInfo+0x28), set termination flag
    if ((0.0 < *(float*)(thisPtr[9] + 0x28)) && (*(float*)(thisPtr[9] + 0x28) < (float)thisPtr[0xd]))
    {
        puVar12 = (uint*)(thisPtr[4] + *(int*)(*fsPtr + 8));
        *puVar12 = *puVar12 | 1;
    }

    fVar22 = DAT_00e2e210; // Min blend threshold constant
    if ((float)thisPtr[0xe] <= DAT_00e2e210)
    {
        // If blend time <= min, signal termination
        puVar12 = (uint*)(*(int*)(*fsPtr + 8) + thisPtr[4]);
        *puVar12 = *puVar12 | 1;
    }

    fVar19 = DAT_00e2b1a4; // Some other constant
    iVar15 = *fsPtr;
    iVar16 = *(int*)(iVar15 + 8);
    iVar11 = iVar16 + thisPtr[4];
    if ((*(byte*)(iVar16 + thisPtr[4]) & 1) != 0)
    {
        return; // Early exit if flag set
    }

    // Get max allowed frames from characterInfo+0x26 (short)
    sVar10 = *(short*)(thisPtr[9] + 0x26);
    iVar16 = thisPtr[0xc]; // Current frame count (offset 0x30)
    bVar7 = false;
    local_50 = fVar22;

    // Compute blend factor (local_50) based on current frame count and frame index
    if (iVar16 < sVar10)
    {
        local_50 = (float)thisPtr[0xe];
        if (1 < iVar16)
        {
            local_50 = local_50 -
                       (*(float*)(*(short*)((int)thisPtr + 0x2e) * 0x20 + 0x1c + thisPtr[10]) -
                        *(float*)((short)thisPtr[0xb] * 0x20 + 0x1c + thisPtr[10]));
        }
        local_50 = local_50 / (float)(sVar10 - iVar16);
        if (local_50 < fVar22)
        {
            local_50 = fVar22;
        }
    }

    // Determine next frame index (sVar10)
    if (*(short*)((int)thisPtr + 0x2e) < sVar10)
    {
        sVar10 = *(short*)((int)thisPtr + 0x2e) + 1;
    }
    else
    {
        sVar10 = 0; // Wrap around
    }

    // Get pointer to the frame data for the new index (each frame is 0x20 bytes = 8 floats)
    pfVar17 = (float*)(sVar10 * 0x20 + thisPtr[10]);

    // Check if we should use ghost interpolation (flag 0x200 in characterInfo+0x20)
    if ((*(uint*)(thisPtr[9] + 0x20) & 0x200) == 0)
    {
        // No ghost: copy directly from internal storage (position+rotation)
        fVar22 = *(float*)(iVar11 + 0x84);
        fVar18 = *(float*)(iVar11 + 0x88);
        fVar20 = *(float*)(iVar11 + 0x8c);
        *pfVar17 = *(float*)(iVar11 + 0x80);
        pfVar17[1] = fVar22;
        pfVar17[2] = fVar18;
        pfVar17[3] = fVar20;
        iVar11 = thisPtr[9];
        if ((*(byte*)(iVar11 + 0x20) & 6) == 0)
        {
            // Apply character translation offset if flags 1/2 not set
            *pfVar17 = *(float*)(iVar11 + 0x54) + *pfVar17;
            pfVar17[1] = *(float*)(iVar11 + 0x58) + pfVar17[1];
            pfVar17[2] = *(float*)(iVar11 + 0x5c) + pfVar17[2];
        }
        // Handle rotation data based on bone count (characterInfo+0x25)
        if (*(char*)(thisPtr[9] + 0x25) < '\x03')
        {
            pfVar13 = (float*)((*(char*)(thisPtr[9] + 0x25) + 5) * 0x10 + *(int*)(iVar15 + 8) + thisPtr[4]);
            fVar22 = pfVar13[1];
            fVar18 = pfVar13[2];
            fVar20 = pfVar13[3];
            pfVar17[4] = *pfVar13;
            pfVar17[5] = fVar22;
            pfVar17[6] = fVar18;
            pfVar17[7] = fVar20;
        }
        else
        {
            // No rotation data for high bone counts
            pfVar17[7] = 0.0;
            pfVar17[6] = 0.0;
            pfVar17[5] = 0.0;
            pfVar17[4] = 0.0;
        }
    }
    else
    {
        // Ghost interpolation path
        iVar11 = *(int*)(thisPtr[1] + 0x20);
        if (iVar11 != 0)
        {
            *(int*)(iVar11 + 4) = *(int*)(iVar11 + 4) + 1; // Ref count increment
        }
        iVar11 = getGhostSource(iVar11); // FUN_00503490
        fVar22 = DAT_00e2cd54; // Interpolation factor constant
        if (iVar11 == 0)
        {
            bVar7 = true; // No ghost source available
        }
        else
        {
            // Copy ghost frame data (position and target)
            fVar19 = *(float*)(iVar11 + 0x14);
            fVar18 = *(float*)(iVar11 + 0x18);
            fVar20 = *(float*)(iVar11 + 0x1c);
            *pfVar17 = *(float*)(iVar11 + 0x10);
            pfVar17[1] = fVar19;
            pfVar17[2] = fVar18;
            pfVar17[3] = fVar20;
            fVar19 = *(float*)(iVar11 + 0x24);
            fVar18 = *(float*)(iVar11 + 0x28);
            fVar20 = *(float*)(iVar11 + 0x2c);
            pfVar17[4] = *(float*)(iVar11 + 0x20);
            pfVar17[5] = fVar19;
            pfVar17[6] = fVar18;
            pfVar17[7] = fVar20;

            // Blend position with target using factor fVar22
            fVar19 = *(float*)(iVar11 + 0x30);
            fVar18 = (pfVar17[4] - *pfVar17) * fVar22 + *pfVar17;
            fVar20 = (pfVar17[5] - pfVar17[1]) * fVar22 + pfVar17[1];
            fVar21 = (pfVar17[6] - pfVar17[2]) * fVar22 + pfVar17[2];
            fVar22 = (pfVar17[7] - pfVar17[3]) * fVar22 + pfVar17[3];

            // Store residual (target - blended) for later use
            pfVar17[4] = pfVar17[4] - fVar18;
            pfVar17[5] = pfVar17[5] - fVar20;
            pfVar17[6] = pfVar17[6] - fVar21;
            pfVar17[7] = pfVar17[7] - fVar22;

            // Store blended position
            *pfVar17 = fVar18;
            pfVar17[1] = fVar20;
            pfVar17[2] = fVar21;
            pfVar17[3] = fVar22;
        }
    }

    fVar22 = 0.0;
    pfVar17[3] = fVar19; // Store some value (maybe rotation component)

    // If no frames in window, reset distance
    if (thisPtr[0xc] == 0)
    {
        pfVar17[7] = 0.0;
    }
    else
    {
        // Compute distance from previous frame and accumulate
        iVar11 = *(short*)((int)thisPtr + 0x2e) * 0x20;
        pfVar13 = (float*)(thisPtr[10] + iVar11);
        local_40 = *pfVar17 - *pfVar13;
        fStack_3c = pfVar17[1] - pfVar13[1];
        fStack_38 = pfVar17[2] - pfVar13[2];
        pfVar17[7] = *(float*)(thisPtr[10] + iVar11 + 0x1c) +
                     SQRT(fStack_3c * fStack_3c + fStack_38 * fStack_38 + local_40 * local_40);
    }

    // Handle frame advancement logic
    if ((*(uint*)(thisPtr[9] + 0x20) & 0x80000000) == 0)
    {
        if (thisPtr[0xc] < 2)
        {
            if (0 < thisPtr[0xc])
            {
                // Single frame: compute difference and call normalize function
                fVar19 = pfVar17[7];
                pfVar13 = (float*)(*(short*)((int)thisPtr + 0x2e) * 0x20 + thisPtr[10]);
                fVar18 = pfVar13[1];
                fVar20 = pfVar13[2];
                fVar21 = pfVar13[3];
                pfVar17[4] = *pfVar17 - *pfVar13;
                pfVar17[5] = pfVar17[1] - fVar18;
                pfVar17[6] = pfVar17[2] - fVar20;
                pfVar17[7] = pfVar17[3] - fVar21;
                pfVar17[7] = fVar19;
                normalizeQuatOrVec(); // FUN_00414aa0
            }
        }
        else
        {
            // Multiple frames: compute differences for smooth interpolation
            sVar3 = *(short*)((int)thisPtr + 0x2e);
            if (sVar3 == 0)
            {
                sVar9 = *(short*)(thisPtr[9] + 0x26); // Wrap around to max
            }
            else
            {
                sVar9 = sVar3 + -1;
            }
            fVar19 = pfVar17[7];
            pfVar13 = (float*)(sVar3 * 0x20 + thisPtr[10]);
            fVar18 = pfVar13[1];
            fVar20 = pfVar13[2];
            fVar21 = pfVar13[3];
            pfVar17[4] = *pfVar17 - *pfVar13;
            pfVar17[5] = pfVar17[1] - fVar18;
            pfVar17[6] = pfVar17[2] - fVar20;
            pfVar17[7] = pfVar17[3] - fVar21;
            pfVar17[7] = fVar19;
            iVar11 = thisPtr[10];
            pfVar13 = (float*)(sVar9 * 0x20 + iVar11);
            fVar19 = pfVar13[1];
            fVar18 = pfVar13[2];
            fVar20 = pfVar13[3];
            iVar15 = *(short*)((int)thisPtr + 0x2e) * 0x20;
            pfVar1 = (float*)(iVar11 + iVar15);
            uVar4 = *(undefined4*)(iVar11 + 0x1c + iVar15);
            iVar11 = iVar11 + iVar15;
            fVar21 = pfVar17[5];
            fVar5 = pfVar17[6];
            fVar6 = pfVar17[7];
            *(float*)(iVar11 + 0x10) = pfVar17[4] + (*pfVar1 - *pfVar13);
            *(float*)(iVar11 + 0x14) = fVar21 + (pfVar1[1] - fVar19);
            *(float*)(iVar11 + 0x18) = fVar5 + (pfVar1[2] - fVar18);
            *(float*)(iVar11 + 0x1c) = fVar6 + (pfVar1[3] - fVar20);
            *(undefined4*)(iVar11 + 0x1c) = uVar4;
        }
    }

    // Check for frame advancement conditions
    if (thisPtr[0xc] < 2) goto LAB_00502c46;
    sVar3 = *(short*)((int)thisPtr + 0x2e);
    if (sVar3 == 0)
    {
        sVar9 = *(short*)(thisPtr[9] + 0x26);
    }
    else
    {
        sVar9 = sVar3 + -1;
    }
    puVar14 = (undefined8*)(sVar3 * 0x20 + thisPtr[10]);
    local_50 = *(float*)(sVar9 * 0x20 + 0x1c + thisPtr[10]) + local_50;
    if (local_50 < *(float*)((int)puVar14 + 0x1c) || local_50 == *(float*)((int)puVar14 + 0x1c))
    {
        // No advancement if local_50 <= current distance
LAB_00502beb:
        if ((bVar7) || (DAT_00e2af44 < pfVar17[3] || DAT_00e2af44 == pfVar17[3])) goto LAB_00502c46;
        iVar11 = thisPtr[10];
        iVar15 = *(short*)((int)thisPtr + 0x2e) * 0x20;
        pfVar13 = (float*)(iVar15 + 0xc + iVar11);
        puVar14 = (undefined8*)(iVar15 + iVar11);
        if ((DAT_00e2af44 < *pfVar13 || DAT_00e2af44 == *pfVar13) ||
            (pfVar13 = (float*)(sVar9 * 0x20 + 0xc + iVar11),
             DAT_00e2af44 < *pfVar13 || DAT_00e2af44 == *pfVar13)) goto LAB_00502c46;
        // Copy frame data into the frame array
        *puVar14 = *(undefined8*)pfVar17;
        puVar14[1] = *(undefined8*)(pfVar17 + 2);
        puVar14[2] = *(undefined8*)(pfVar17 + 4);
        puVar14[3] = *(undefined8*)(pfVar17 + 6);
    }
    else
    {
        if (local_50 < pfVar17[7])
        {
            // Call some advancement handling function
            onFrameAdvance(); // FUN_00501a30
            fVar22 = 0.0;
            goto LAB_00502beb;
        }
        // Else copy frame data
        *puVar14 = *(undefined8*)pfVar17;
        puVar14[1] = *(undefined8*)(pfVar17 + 2);
        puVar14[2] = *(undefined8*)(pfVar17 + 4);
        puVar14[3] = *(undefined8*)(pfVar17 + 6);
    }
    bVar7 = true;

LAB_00502c46:
    // Check if we need to advance the frame window
    if ((((*(uint*)(thisPtr[9] + 0x20) & 0x20000) == 0) ||
         (fVar19 = pfVar17[7] - *(float*)((short)thisPtr[0xb] * 0x20 + 0x1c + thisPtr[10]),
          fVar19 < (float)thisPtr[0xe] || fVar19 == (float)thisPtr[0xe])) && (!bVar7))
    {
        thisPtr[0xc] = thisPtr[0xc] + 1; // Increment frame count
        *(short*)((int)thisPtr + 0x2e) = sVar10; // Update current frame index
        sVar10 = *(short*)(thisPtr[9] + 0x26);
        if ((int)sVar10 <= thisPtr[0xc])
        {
            if ((short)thisPtr[0xb] < sVar10)
            {
                sVar10 = (short)thisPtr[0xb] + 1;
            }
            else
            {
                sVar10 = 0;
            }
            *(short*)(thisPtr + 0xb) = sVar10; // Update next frame index
            thisPtr[0xc] = thisPtr[0xc] + -1;
        }
    }

    // Update next frame index and maintain sliding window
    iVar11 = thisPtr[0xc];
    if (iVar11 != 0)
    {
        iVar15 = thisPtr[10];
        fVar19 = (float)thisPtr[0xe];
        iVar16 = *(short*)((int)thisPtr + 0x2e) * 0x20;
        pfVar17 = (float*)(iVar16 + 0x1c + iVar15);
        if (*(float*)((short)thisPtr[0xb] * 0x20 + 0x1c + iVar15) + fVar19 <
            *(float*)(iVar16 + 0x1c + iVar15))
        {
            do
            {
                sVar10 = (short)thisPtr[0xb];
                if (*pfVar17 <= *(float*)(sVar10 * 0x20 + 0x1c + thisPtr[10]) + fVar19) break;
                if (sVar10 < *(short*)(thisPtr[9] + 0x26))
                {
                    sVar10 = sVar10 + 1;
                }
                else
                {
                    sVar10 = 0;
                }
                thisPtr[0xc] = thisPtr[0xc] + -1;
                *(short*)(thisPtr + 0xb) = sVar10;
            } while (thisPtr[0xc] != 0);
            if (1 < iVar11)
            {
                iVar11 = thisPtr[0xb];
                sVar10 = findPreviousFrameIndex(thisPtr); // FUN_00502480
                fVar22 = *(float*)(sVar10 * 0x20 + 0x1c + thisPtr[10]);
                fVar22 = ((*pfVar17 - fVar19) - fVar22) /
                         (*(float*)(thisPtr[10] + 0x1c + (short)iVar11 * 0x20) - fVar22);
                if ((DAT_00e2e210 < fVar22) && (fVar22 < DAT_00e44854))
                {
                    onFrameAdvance(); // FUN_00501a30
                    thisPtr[0xc] = thisPtr[0xc] + 1;
                    *(short*)(thisPtr + 0xb) = sVar10;
                }
                fVar22 = 0.0;
            }
        }
    }

    // Compute final output values
    iVar11 = thisPtr[9];
    fVar19 = *(float*)(iVar11 + 0x68) * (float)thisPtr[0xd] + (float)thisPtr[0x10];
    thisPtr[0xf] = (int)fVar19; // Store integer part
    if ((*(byte*)(iVar11 + 0x20) & 0x40) == 0)
    {
        fVar19 = (float)(int)((fVar19 - (float)(int)fVar19) * *(float*)(iVar11 + 0x60)) *
                 *(float*)(iVar11 + 100);
        thisPtr[0xf] = (int)fVar19; // Modified by fractional part and multipliers
    }

    fVar18 = fVar22;
    if ((*(uint*)(iVar11 + 0x20) & 0x200) != 0)
    {
        // Ghost path: compute maximum distance between frames in window
        iVar15 = thisPtr[0xc];
        if (iVar15 != 0)
        {
            computeDistanceAccumulation(); // FUN_0051b5c0
            sVar10 = *(short*)((int)thisPtr + 0x2e);
            do
            {
                iVar15 = iVar15 + -1;
                pfVar17 = (float*)(sVar10 * 0x20 + thisPtr[10]);
                if (sVar10 == 0)
                {
                    sVar10 = *(short*)(iVar11 + 0x26);
                }
                else
                {
                    sVar10 = sVar10 + -1;
                }
                fVar19 = (pfVar17[2] - fStack_38) * (pfVar17[2] - fStack_38) +
                         (pfVar17[1] - fStack_3c) * (pfVar17[1] - fStack_3c) +
                         (*pfVar17 - local_40) * (*pfVar17 - local_40);
                if (fVar22 < fVar19)
                {
                    fVar22 = fVar19;
                }
            } while (iVar15 != 0);
            fVar18 = 0.0;
            fVar22 = SQRT(fVar22);
        }
        // Compare with min distance from another source
        fVar19 = *(float*)(*(int*)(thisPtr[1] + 0x10) + 0x20);
        if (fVar22 < fVar19)
        {
            fVar22 = fVar19;
        }
        *(float*)(thisPtr[1] + 0x88) = fVar22; // Store radius or speed limit
    }

    // Update animation speed/multiplier
    thisPtr[0x12] = *(int*)(thisPtr[9] + 0x50);
    if ((thisPtr[0x13] != 1) || (thisPtr[0x14] != 0))
    {
        computeAnimationSpeedMultiplier(); // FUN_004ebc00
        fVar18 = 0.0;
        thisPtr[0x12] = (int)(fVar19 * (float)thisPtr[0x12]);
    }

    // Clamp based on action timer and min speed
    if ((fVar18 <= (float)thisPtr[0x11]) && (fVar18 < *(float*)(thisPtr[9] + 0x88)))
    {
        thisPtr[0x12] =
            (int)(((float)thisPtr[0x12] / *(float*)(thisPtr[9] + 0x88)) * (float)thisPtr[0x11]);
    }

    // Call virtual function (through vtable) to see if we should send animation
    cVar8 = (**(code**)(*thisPtr + 0xc))();
    if (cVar8 != '\0')
    {
        sendAnimationUpdate(thisPtr, // FUN_00502380
                            *(undefined8*)(thisPtr + 0xb),          // nextFrame, currentFrameIndex
                            CONCAT44(thisPtr[0xf], thisPtr[0xd]),   // output values
                            thisPtr[0x12],                          // speed
                            CONCAT44(*(short*)(thisPtr[9] + 0x26) + 1, thisPtr[10]), // maxFrames+1, frameData
                            0x10);                                  // some flag
    }
    return;
}