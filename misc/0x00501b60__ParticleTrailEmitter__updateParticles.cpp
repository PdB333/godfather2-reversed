// FUNC_NAME: ParticleTrailEmitter::updateParticles
// Function address: 0x00501b60
// This function updates a particle trail emitter, spawning particles along a path defined by a ring buffer of positions.
// It is called with a pointer to the emitter object (this) and a pointer to a transform (likely orientation quaternion at +0x70).

void __thiscall ParticleTrailEmitter::updateParticles(void* thisPtr, void* transformPtr) {
    float fVar1, fVar2, fVar9, fVar10, fVar11, fVar12, fVar13, fVar14, fVar15, fVar16, fVar17, fVar18, fVar19, fVar20, fVar21;
    int iVar3, iVar6;
    short sVar4;
    uint uVar5;
    float* pfVar7, *pfVar8;
    float fStack_84;
    float local_78;
    undefined4 local_3c;
    float local_30, fStack_2c, fStack_28, fStack_24;
    float local_20, fStack_1c, fStack_18, fStack_14;
    int local_98, local_9c;
    undefined4* local_94;
    undefined4 local_a0;
    
    // Check if emitter timer (this+0x30) is above global threshold
    if (DAT_00e2af44 < *(float*)(thisPtr + 0x30)) {
        // Check if there are active particles (this+0x1c)
        if (*(int*)(thisPtr + 0x1c) == 0) {
            *(uint*)(thisPtr + 0x1c) = 0;
            return;
        }
        
        // Determine uVar5 flag based on emitter configuration
        uint* configPtr = *(uint**)(thisPtr + 0x10);
        uVar5 = (configPtr[8] >> 3) & 4; // +0x20 of config
        if (*(int*)(thisPtr + 0x18) != 0) {
            uVar5 = uVar5 | 2;
        }
        
        FUN_005334b0(&local_3c, uVar5); // Begin frame / state
        FUN_00535170(); // Set some render state
        FUN_00534ff0(*(uint*)(thisPtr + 0x18)); // Bind texture or material
        
        fStack_84 = *(float*)(thisPtr + 0x30); // Save timer
        
        FUN_004ecc00(); // Possibly set matrix
        if (DAT_012058d0 < 14) {
            DAT_012058d0 = 14;
        }
        if (14 < DAT_00f15988) {
            DAT_00f15988 = 14;
        }
        _DAT_011f3a10 = 0;
        FUN_004ecc40(); // Matrix operations
        FUN_004eccc0(1);
        FUN_00533350(configPtr[8] >> 5 & 0xffffff01); // Set shader flags
        
        // Check for condition: global flag + 0x200 and another check
        if (((*(uint*)((**(int**)(*(int*)(FS_OFFSET + 0x2c) + 8)) + *(int*)(thisPtr + 8)) & 0x200) == 0) ||
            (*(int*)(DAT_012234c4 + 0x24) == 0)) {
            local_a0 = 0;
        } else {
            local_a0 = 1;
        }
        FUN_00535450(local_a0, local_3c);
        
        // Get current index (short at this+0x22)
        local_98 = (int)*(short*)(thisPtr + 0x22);
        
        // Extract target transform quaternion from transformPtr (offset +0x70)
        local_20 = *(float*)(transformPtr + 0x70);
        fStack_1c = *(float*)(transformPtr + 0x74);
        fStack_18 = *(float*)(transformPtr + 0x78);
        fStack_14 = *(float*)(transformPtr + 0x7c);
        
        fVar1 = *(float*)(thisPtr + 0x2c); // Some emitter parameter
        configPtr = *(uint**)(thisPtr + 0x10);
        fVar2 = *(float*)(configPtr + 25); // +100 = 0x64
        float* posArray = *(float**)(thisPtr + 0x1c); // Ring buffer of positions (0x20 stride)
        int prevIndex = (int)*(short*)(thisPtr + 0x20); // Previous index
        fVar20 = *(float*)(posArray + local_98 * 8 + 7); // +0x1c within entry (float at offset 0x1c = 7th float)
        fVar9 = fVar20 - *(float*)(posArray + prevIndex * 8 + 7);
        
        local_38 = 1; // Possibly byte flag
        
        if (fVar9 == DAT_00e2b05c) {
            fVar9 = DAT_00e2e210; // Typically 0.0f
        }
        
        fVar17 = *(float*)(configPtr + 27); // +0x6c
        fVar9 = DAT_00e2b1a4 / fVar9; // 1.0f / distance
        
        if ((configPtr[8] & 0x100) != 0) {
            fVar17 = fVar17 * fVar9;
        }
        
        local_78 = *(float*)(configPtr + 28) * *(float*)(thisPtr + 0x28); // +0x70 * scale
        local_78 = local_78 - (float)(int)local_78; // Fractional part
        
        if (configPtr[8] < 0) { // Check sign bit (bit31)
            local_78 = local_78 - fVar20 * fVar17;
        }
        
        local_9c = *(int*)(thisPtr + 0x24); // Number of particles to emit
        
        if (1 < local_9c) {
            // Loop emitting particles in batches
            for (; local_9c != 0; ) {
                int batchCount = 8;
                if (local_9c < 8) {
                    batchCount = local_9c;
                }
                
                // Allocate memory: size=5, count=batchCount*2, align=0, flags=1, ???
                local_94 = (undefined4*)FUN_0060cd00(5, batchCount * 2, 0, 1, 0);
                if (local_94 != (undefined4*)0) {
                    float fVar20_saved = 0.0f;
                    if (0 < batchCount) {
                        local_9c -= batchCount;
                        pfVar8 = (float*)(local_94 + 4); // +16 bytes offset? Actually 4*4 = 16 bytes
                        fVar21 = DAT_00e2b1a4;
                        do {
                            iVar3 = *(int*)(thisPtr + 0x1c);
                            batchCount--;
                            // Current position delta
                            float* currPos = (float*)(iVar3 + *(short*)(thisPtr + 0x22) * 0x20);
                            float* prevPos = (float*)(iVar3 + local_98 * 0x20);
                            fVar10 = *(currPos + 7) - *(prevPos + 7); // W component?
                            
                            pfVar7 = (float*)(iVar3 + local_98 * 0x20); // Current entry base
                            configPtr = *(uint**)(thisPtr + 0x10);
                            fVar18 = fVar10 * fVar17 + local_78;
                            fVar10 = fVar10 * fVar9;
                            
                            fVar11 = fVar21 - *(float*)(configPtr + 14); // +0x38
                            fVar13 = DAT_00e2e50c;
                            if (DAT_00e44560 < *(float*)(configPtr + 13)) { // +0x34
                                fVar13 = fVar21 / *(float*)(configPtr + 13);
                            }
                            fVar12 = DAT_00e2e50c;
                            if (DAT_00e44560 < fVar11) {
                                fVar12 = fVar21 / fVar11;
                            }
                            fVar12 = (DAT_00e44564 - fVar12) * fVar10 + fVar12;
                            if (fVar13 * fVar10 < fVar12) {
                                fVar12 = fVar13 * fVar10;
                            }
                            fVar13 = fVar20_saved;
                            if ((fVar20_saved <= fVar12) && (fVar13 = fVar12, fVar21 < fVar12)) {
                                fVar13 = fVar21;
                            }
                            fVar11 = pfVar7[3]; // +0x0c within entry
                            fVar10 = (fVar21 - fVar10) * *(float*)(configPtr + 15) + *(float*)(configPtr + 16) * fVar10; // +0x3c, +0x40
                            
                            if ((configPtr[8] & 0x80000000) == 0) {
                                // 3D cross product to compute orthogonal vectors
                                fVar19 = (pfVar7[1] - fStack_1c) * pfVar7[6] - (pfVar7[2] - fStack_18) * pfVar7[5];
                                fVar15 = (pfVar7[2] - fStack_18) * pfVar7[4] - (*pfVar7 - local_20) * pfVar7[6];
                                fVar16 = (*pfVar7 - local_20) * pfVar7[5] - (pfVar7[1] - fStack_1c) * pfVar7[4];
                                fVar12 = fVar15 * fVar15 + fVar16 * fVar16 + fVar19 * fVar19;
                                if (fVar12 <= DAT_00e2cbe0) {
                                    fVar12 = 0.0f;
                                    fVar14 = 0.0f;
                                } else {
                                    fVar12 = SQRT(fVar12);
                                    fVar14 = fVar21 / fVar12;
                                }
                                fVar20_saved = 0.0f;
                                if (fVar12 < DAT_00e44560) {
                                    fVar12 = fVar12 * DAT_00e44794;
                                    fVar10 = (DAT_00e445ac - fVar12 * DAT_00e2b04c) * fVar12 * fVar12 * fVar10;
                                }
                                fStack_84 = fVar10 * ((pfVar7[3] - fStack_14) * pfVar7[7] -
                                                     (pfVar7[3] - fStack_14) * pfVar7[7]);
                                fVar16 = fVar10 * fVar16 * fVar14;
                                fVar15 = fVar10 * fVar15 * fVar14;
                                fVar12 = fVar10 * fVar19 * fVar14;
                            } else {
                                fVar12 = fVar10 * pfVar7[4];
                                fVar15 = fVar10 * pfVar7[5];
                                fVar16 = fVar10 * pfVar7[6];
                            }
                            
                            // Update particle positions
                            local_30 = *pfVar7 + fVar12;
                            fStack_2c = pfVar7[1] + fVar15;
                            fStack_28 = pfVar7[2] + fVar16;
                            fStack_24 = pfVar7[3] + fStack_84;
                            
                            fVar10 = fStack_84;
                            FUN_00414aa0(); // Transform point? (takes local_30 etc. as arguments?)
                            
                            // Write particle data: first 4 ints (flags/color), then 4 floats (position/velocity)
                            *local_94 = 0;
                            local_94[1] = 0;
                            local_94[2] = 0;
                            local_94[3] = *(int*)(&fVar11); // ?? fVar11 * fVar13 (probably alpha or lifetime)
                            *pfVar8 = fVar1;
                            pfVar8[1] = fVar18;
                            pfVar8[2] = fVar20_saved;
                            pfVar8[3] = fVar18;
                            
                            // Second particle (mirror/symmetric)
                            local_30 = *pfVar7 - fVar12;
                            fStack_2c = pfVar7[1] - fVar15;
                            fStack_28 = pfVar7[2] - fVar16;
                            fStack_24 = pfVar7[3] - fVar10;
                            FUN_00414aa0();
                            
                            local_94[8] = 0;
                            local_94[9] = 0;
                            local_94[10] = 0;
                            local_94[11] = *(int*)(&fVar11); // Same alpha
                            local_94 += 0x10; // Move to next particle pair (16 ints = 64 bytes)
                            pfVar8[8] = fVar2 + fVar1;
                            pfVar8[9] = fVar18;
                            pfVar8[10] = fVar21;
                            pfVar8[11] = fVar18;
                            pfVar8 += 0x10; // Move to next float set (16 floats = 64 bytes)
                            
                            // Update index for next iteration
                            if ((short)local_98 == 0) {
                                sVar4 = *(short*)(*(int*)(thisPtr + 0x10) + 0x26);
                            } else {
                                sVar4 = (short)(local_98 - 1);
                            }
                            local_98 = (int)sVar4;
                        } while (0 < batchCount);
                    }
                    FUN_0060cde0(); // Free allocated memory
                }
                if (local_9c == 0) break;
                
                // Wrapping index
                if ((short)local_98 < *(short*)(*(int*)(thisPtr + 0x10) + 0x26)) {
                    sVar4 = (short)(local_98 + 1);
                } else {
                    sVar4 = 0;
                }
                local_98 = (int)sVar4;
            }
        }
        
        FUN_00533720(&local_3c); // End frame / cleanup
    }
    
    *(uint*)(thisPtr + 0x1c) = 0; // Clear particle count?
    return;
}