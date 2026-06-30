// FUNC_NAME: ParticleSystem::updateParticles
void __thiscall ParticleSystem::updateParticles(void *this, void *pCamera)
{
    float fVar1;
    float fVar2;
    int iVar3;
    short sVar4;
    uint uVar5;
    int iVar6;
    float *pfVar7;
    float *pfVar8;
    uint unaff_FS_OFFSET;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    float fVar16;
    float fVar17;
    float fVar18;
    float fVar19;
    float fVar20;
    float fVar21;
    undefined4 local_a0;
    int particleCount;          // local_9c
    int currentIndex;           // local_98
    undefined4 *pBuffer;        // local_94
    float fStack_84;
    float local_78;             // fraction
    undefined4 transformMatrix; // local_3c
    undefined1 local_38;        // flag
    float local_30;             // temp vector
    float fStack_2c;
    float fStack_28;
    float fStack_24;
    float local_20;             // from pCamera+0x70 (camera position?)
    float fStack_1c;
    float fStack_18;
    float fStack_14;

    // Check if time threshold passed (global speed variable)
    if (DAT_00e2af44 >= *(float *)((int)this + 0x30)) {
        goto done;
    }

    // Particle data pointer exists?
    if (*(int *)((int)this + 0x1c) == 0) {
        *(undefined4 *)((int)this + 0x1c) = 0;
        return;
    }

    // Build flag based on render state flags
    uVar5 = (*(uint *)(*(int *)((int)this + 0x10) + 0x20) >> 3) & 4;
    if (*(int *)((int)this + 0x18) != 0) {
        uVar5 = uVar5 | 2;
    }

    // Setup rendering context
    FUN_005334b0(&transformMatrix, uVar5);  // push matrix
    FUN_00535170();                         // set depth buffer?
    FUN_00534ff0(*(undefined4 *)((int)this + 0x18)); // apply material?
    fStack_84 = *(float *)((int)this + 0x30); // time step

    FUN_004ecc00(); // update animation?
    // Clamp global settings
    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }
    _DAT_011f3a10 = 0;
    FUN_004ecc40(); // reset something
    FUN_004eccc0(1); // enable something

    FUN_00533350(*(uint *)(*(int *)((int)this + 0x10) + 0x20) >> 5 & 0xffffff01); // set render flags

    // Check if rendering flag and texture enabled
    if (((*(uint *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + *(int *)((int)this + 8)) & 0x200) == 0) || (local_a0 = 1, *(int *)(DAT_012234c4 + 0x24) == 0)) {
        local_a0 = 0;
    }
    FUN_00535450(local_a0, transformMatrix); // set material

    currentIndex = (int)*(short *)((int)this + 0x22); // current particle index
    // Camera view/projection matrix rows? Actually pCamera+0x70 is a 4x4 matrix? But only used as four floats.
    local_20 = *(float *)((int)pCamera + 0x70);
    fStack_1c = *(float *)((int)pCamera + 0x74);
    fStack_18 = *(float *)((int)pCamera + 0x78);
    fStack_14 = *(float *)((int)pCamera + 0x7c);

    fVar1 = *(float *)((int)this + 0x2c); // base scale
    iVar6 = *(int *)((int)this + 0x10);   // some render state object
    fVar2 = *(float *)(iVar6 + 100);        // offset 0x64? (maybe maxSize)
    // Get particle life values from particle data block
    fVar20 = *(float *)(currentIndex * 0x20 + 0x1c + *(int *)((int)this + 0x1c)); // life or alpha? Actually at offset +0x1c? That's within the particle data? The particle data is at base + index*0x20. But 0x1c is offset 28 bytes into particle, which is last float (7th) if structure is 8 floats. 
    fVar9 = fVar20 - *(float *)(*(short *)((int)this + 0x20) * 0x20 + 0x1c + *(int *)((int)this + 0x1c)); // difference in life between current and previous particle?

    local_38 = 1;
    if (fVar9 == DAT_00e2b05c) {
        fVar9 = DAT_00e2e210;
    }
    fVar17 = *(float *)(iVar6 + 0x6c); // some velocity damping?
    fVar9 = DAT_00e2b1a4 / fVar9;     // 1.0 / delta life? Actually DAT_00e2b1a4 = 1.0f
    if ((*(uint *)(iVar6 + 0x20) & 0x100) != 0) {
        fVar17 = fVar17 * fVar9;    // scale damping by inverse life delta
    }
    local_78 = *(float *)(iVar6 + 0x70) * *(float *)((int)this + 0x28); // some multiplier
    local_78 = local_78 - (float)(int)local_78; // fractional part
    if (-1 < (char)*(uint *)(iVar6 + 0x20)) {
        local_78 = local_78 - fVar20 * fVar17; // subtract scaled life?
    }

    particleCount = *(int *)((int)this + 0x24); // number of particles to process
    if (particleCount <= 1) {
        goto cleanup;
    }

    // Main loop over particles in chunks of up to 8
    do {
        iVar6 = 8;
        if (particleCount < 8) {
            iVar6 = particleCount;
        }
        pBuffer = (undefined4 *)FUN_0060cd00(5, iVar6 * 2, 0, 1, 0); // allocate temporary buffer (2 entries per particle?)
        if (pBuffer != (undefined4 *)0x0) {
            fVar20 = 0.0f;
            if (0 < iVar6) {
                particleCount -= iVar6;
                pfVar8 = (float *)(pBuffer + 4); // pointer to second half of first particle's data?
                fVar21 = DAT_00e2b1a4; // 1.0f
                do {
                    iVar3 = *(int *)((int)this + 0x1c); // base particle data
                    iVar6--; // decrement chunk counter
                    // Life difference between current and previous particle
                    fVar10 = *(float *)(*(short *)((int)this + 0x22) * 0x20 + 0x1c + iVar3) -
                             *(float *)(currentIndex * 0x20 + 0x1c + iVar3);
                    pfVar7 = (float *)(currentIndex * 0x20 + iVar3); // pointer to current particle position
                    iVar3 = *(int *)((int)this + 0x10); // state object
                    fVar18 = fVar10 * fVar17 + local_78;
                    fVar10 = fVar10 * fVar9; // scaled delta life
                    fVar11 = fVar21 - *(float *)(iVar3 + 0x38); // 1 - some constant?
                    fVar13 = DAT_00e2e50c; // default 0? Actually some max value
                    if (DAT_00e44560 < *(float *)(iVar3 + 0x34)) {
                        fVar13 = fVar21 / *(float *)(iVar3 + 0x34); // 1 / some value
                    }
                    fVar12 = DAT_00e2e50c;
                    if (DAT_00e44560 < fVar11) {
                        fVar12 = fVar21 / fVar11;
                    }
                    fVar12 = (DAT_00e44564 - fVar12) * fVar10 + fVar12; // smooth interpolation?
                    if (fVar13 * fVar10 < fVar12) {
                        fVar12 = fVar13 * fVar10;
                    }
                    fVar13 = fVar20;
                    if ((fVar20 <= fVar12) && (fVar13 = fVar12, fVar21 < fVar12)) {
                        fVar13 = fVar21;
                    }
                    fVar11 = pfVar7[3]; // life of current particle
                    fVar10 = (fVar21 - fVar10) * *(float *)(iVar3 + 0x3c) +
                             *(float *)(iVar3 + 0x40) * fVar10; // blend between two values

                    if ((*(uint *)(iVar3 + 0x20) & 0x80000000) == 0) {
                        // Directional force: cross product
                        fVar19 = (pfVar7[1] - fStack_1c) * pfVar7[6] - (pfVar7[2] - fStack_18) * pfVar7[5];
                        fVar15 = (pfVar7[2] - fStack_18) * pfVar7[4] - (*pfVar7 - local_20) * pfVar7[6];
                        fVar16 = (*pfVar7 - local_20) * pfVar7[5] - (pfVar7[1] - fStack_1c) * pfVar7[4];
                        fVar12 = fVar15 * fVar15 + fVar16 * fVar16 + fVar19 * fVar19;
                        if (fVar12 <= DAT_00e2cbe0) {
                            fVar12 = 0.0f;
                            fVar14 = 0.0f;
                        } else {
                            fVar12 = sqrtf(fVar12);
                            fVar14 = fVar21 / fVar12; // 1/distance
                        }
                        fVar20 = 0.0f;
                        if (fVar12 < DAT_00e44560) {
                            fVar12 = fVar12 * DAT_00e44794;
                            fVar10 = (DAT_00e445ac - fVar12 * DAT_00e2b04c) * fVar12 * fVar12 * fVar10;
                        }
                        fStack_84 = fVar10 * ((pfVar7[3] - fStack_14) * pfVar7[7] - (pfVar7[3] - fStack_14) * pfVar7[7]); // zero? Actually same term subtracted gives 0!
                        fVar16 = fVar10 * fVar16 * fVar14;
                        fVar15 = fVar10 * fVar15 * fVar14;
                        fVar12 = fVar10 * fVar19 * fVar14;
                    } else {
                        // Simple directional force
                        fVar12 = fVar10 * pfVar7[4]; // velocity x
                        fVar15 = fVar10 * pfVar7[5]; // velocity y
                        fVar16 = fVar10 * pfVar7[6]; // velocity z
                    }

                    // Store forward and backward quaternion/position
                    local_30 = *pfVar7 + fVar12;
                    fStack_2c = pfVar7[1] + fVar15;
                    fStack_28 = pfVar7[2] + fVar16;
                    fStack_24 = pfVar7[3] + fStack_84; // life update? but fStack_84 is 0
                    FUN_00414aa0(); // set quaternion from translation? (assumed)
                    *pBuffer = 0;
                    pBuffer[1] = 0;
                    pBuffer[2] = 0;
                    pBuffer[3] = fVar11 * fVar13; // life * alpha?
                    *pfVar8 = fVar1;   // base scale
                    pfVar8[1] = fVar18;
                    pfVar8[2] = fVar20;
                    pfVar8[3] = fVar18;
                    // Backwards
                    local_30 = *pfVar7 - fVar12;
                    fStack_2c = pfVar7[1] - fVar15;
                    fStack_28 = pfVar7[2] - fVar16;
                    fStack_24 = pfVar7[3] - fVar10;
                    FUN_00414aa0();
                    pBuffer[8] = 0;
                    pBuffer[9] = 0;
                    pBuffer[10] = 0;
                    pBuffer[11] = fVar11 * fVar13;
                    pBuffer += 0x10; // advance buffer by 16 words (64 bytes) per particle? Actually 0x10 in 4-byte units = 64 bytes
                    pfVar8[8] = fVar2 + fVar1; // maxScale + baseScale
                    pfVar8[9] = fVar18;
                    pfVar8[10] = fVar21; // 1.0f
                    pfVar8[11] = fVar18;
                    pfVar8 += 0x10; // advance 64 bytes as well

                    // Update particle index, wrapping around
                    if ((short)currentIndex == 0) {
                        sVar4 = *(short *)(*(int *)((int)this + 0x10) + 0x26);
                    } else {
                        sVar4 = (short)currentIndex - 1;
                    }
                    currentIndex = (int)sVar4;
                } while (0 < iVar6);
            }
            FUN_0060cde0(); // free temporary buffer?
        }
        // Check if we are done with the outer loop
        if (particleCount == 0) break;
        // Wrap particle index forward for next chunk?
        if ((short)currentIndex < *(short *)(*(int *)((int)this + 0x10) + 0x26)) {
            sVar4 = (short)currentIndex + 1;
        } else {
            sVar4 = 0;
        }
        currentIndex = (int)sVar4;
    } while (true);

cleanup:
    FUN_00533720(&transformMatrix); // pop matrix
done:
    *(undefined4 *)((int)this + 0x1c) = 0; // clear particle data pointer
    return;
}