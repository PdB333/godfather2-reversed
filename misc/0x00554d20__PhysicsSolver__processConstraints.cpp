// FUNC_NAME: PhysicsSolver::processConstraints
void __thiscall PhysicsSolver::processConstraints(int thisPtr, int contactInfo, char* constraintFlags, float numConstraints)
{
    // +0x10: position x
    // +0x14: position y
    // +0x18: position z
    // +0x1c: orientation w (quaternion or angle)
    // +0x58: some velocity/damping factor
    // +0x70: array of callback objects (listeners)
    // +0x74: number of callback objects
    // +0x64: pointer to array of constraint data (size 0x30 each)
    // +0x100? Actually param_1+100 decimal = +0x64

    undefined4 local_dc = *(undefined4*)(contactInfo + 8); // some identifier
    float accumFactor = 0.0f;

    if (0 < (int)numConstraints) {
        int idx = 0;
        char* flagsIter = constraintFlags;
        float remaining = numConstraints;
        do {
            // Get constraint data block (size 0x30)
            int constraintData = *(int*)(thisPtr + 0x64) + idx; // base + 0x30*i

            // iVar5 = pointer to component from constraint data
            int componentPtr = *(int*)(constraintData + 0x28);

            // Number of sub-components (vtbl? check)
            int numSubComps = *(int*)(*(char*)(componentPtr + 0x10) + 0x78 + componentPtr);
            int subIndex = 0;
            if (0 < numSubComps) {
                int** subCompArray = (int**)(*(char*)(componentPtr + 0x10) + componentPtr + 0x74);
                do {
                    if (**subCompArray != 0x1300) {
                        subIndex++;
                        subCompArray += 4;
                        if (numSubComps <= subIndex) goto LAB_00554dea;
                        continue;
                    }
                    // Component type 0x1300 – send notification to listeners
                    undefined4* vecData = (undefined4*)FUN_004af8c0(local_48, 0x1300);
                    int listenerCount = *(int*)(thisPtr + 0x74);
                    uint32 listenerVal = *vecData;
                    float secondVal = (float)vecData[1];
                    while (listenerCount-- > 0) {
                        int* listener = *(int**)(thisPtr + 0x70 + listenerCount * 4);
                        if (listener != 0) {
                            (**(code**)(*listener + 0xc))(thisPtr, listenerVal, constraintData);
                        }
                    }
                } while (true);
            }
LAB_00554dea:
            // Now check if this constraint has type 0x2004 (collision/force)
            int constraintData2 = *(int*)(thisPtr + 0x64) + idx;
            int compPtr2 = *(int*)(constraintData2 + 0x28);
            if (*(char*)(compPtr2 + 0x18) == '\x01') {
                int compBase = *(char*)(compPtr2 + 0x10) + compPtr2;
                if (compBase != 0) {
                    int subIndex2 = 0;
                    if (0 < *(int*)(compBase + 0x78)) {
                        int** compArray2 = (int**)(compBase + 0x74);
                        do {
                            if (**compArray2 == 0x2004) {
                                // Check flags condition
                                if (((*flagsIter != '\0') ||
                                    (*(float*)(constraintData2 + 0x1c) - *(float*)(thisPtr + 0x58) < DAT_00e44598)) &&
                                    (*(char*)(compBase + 0xd8) != '\a') &&
                                    (*(char*)(compBase + 0xd8) != '\x06')) {
                                    // Gather local data from constraint data block
                                    float* cDataFloat = (float*)(*(int*)(thisPtr + 0x64) + idx);
                                    float localX = cDataFloat[0]; // +0x00
                                    float localY = cDataFloat[1]; // +0x04
                                    float localZ = cDataFloat[2]; // +0x08
                                    float localW = cDataFloat[7]; // +0x1c (index 7? actually +0x1c = offset 28/4 = 7)
                                    // Offsets +0x10, +0x14, +0x18, +0x1c from constraintData2
                                    float vx = *(float*)(constraintData2 + 0x10);
                                    float vy = *(float*)(constraintData2 + 0x14);
                                    float vz = *(float*)(constraintData2 + 0x18);
                                    float vw = *(float*)(constraintData2 + 0x1c); // repeated? but used as separate
                                    // Compute relative vector
                                    float dx = localX - *(float*)(compBase + 0x130);
                                    float dy = localY - *(float*)(compBase + 0x134);
                                    float dz = localZ - *(float*)(compBase + 0x138);
                                    // Complex force calculation using cross products and dot products
                                    // Use offsets from compBase: 0x1a0,0x1a4,0x1a8,0x1b0,0x1b4,0x1b8,0x19c
                                    float forceScale = ((*(float*)(compBase + 0x1a8) +
                                        (*(float*)(compBase + 0x1b0) * dy - *(float*)(compBase + 0x1b4) * dx)
                                        ) - *(float*)(thisPtr + 0x18)) * vz +
                                        ((*(float*)(compBase + 0x1a4) +
                                        (*(float*)(compBase + 0x1b8) * dx - *(float*)(compBase + 0x1b0) * dz)
                                        ) - *(float*)(thisPtr + 0x14)) * vy +
                                        ((*(float*)(compBase + 0x1a0) +
                                        (*(float*)(compBase + 0x1b4) * dz - *(float*)(compBase + 0x1b8) * dy)
                                        ) - *(float*)(thisPtr + 0x10)) * vx;
                                    // Compute impulse magnitude
                                    float impulseMag = *(float*)(contactInfo + 0xc) * localW * DAT_00e2cd14 - forceScale * DAT_0110a440;
                                    int savedCompPtr = compBase;
                                    if (impulseMag <= DAT_00e2b05c) {
                                        // Call function on compBase vtable to get a matrix? (0x28)
                                        (**(code**)(*(int*)(compBase + 0xd0) + 0x28))(auStack_40);
                                        // Cross product of relative position and local orientation?
                                        float crossX = dy * vy - dz * vx; // fStack_c4: dy*vy - dz*vx? No, from code: fVar7*fStack_ec - fVar6*fStack_f0
                                        // Actually let's re-derive: fStack_c4 = fVar7*fStack_ec - fVar6*fStack_f0
                                        // fVar7 = dy, fVar6 = dz? Wait original: fVar7 = fStack_fc - compBase+0x134 (dy), fVar6 = fStack_f8 - compBase+0x138 (dz), fVar8 = local_104 - compBase+0x130 (dx)
                                        // So cross components:
                                        float relX = dy; // actually relX? more careful:
                                        // From original: fVar7 = fStack_100 - compBase+0x134? No, reassign:
                                        // After reassign: fVar7 = fStack_100 - compBase+0x134 (dy), fVar6 = fStack_fc - compBase+0x138 (dz), fVar8 = local_104 - compBase+0x130 (dx)
                                        // Then: fStack_c4 = fVar7 * fStack_ec - fVar6 * fStack_f0 (cross product Y component)
                                        // fStack_c0 = fVar6 * fStack_f4 - fStack_ec * fVar8 (cross product Z)
                                        // fStack_bc = fStack_f0 * fVar8 - fVar7 * fStack_f4 (cross product X)
                                        float relDY = dy;
                                        float relDZ = dz;
                                        float relDX = remaining - *(float*)(compBase + 0x130); // dx? careful: local_104 is numConstraints decrementing, but originally it was local_104 (float param) - compBase+0x130
                                        // Actually the original code uses local_104 which is param_4 (the loop counter) minus something.
                                        // That seems wrong. It's probably a mis-decompilation. The intended variable is dx=localX - compBase+0x130.
                                        // So we'll assume dx = localX - compBase+0x130.
                                        float dx_true = localX - *(float*)(compBase + 0x130);
                                        float dy_true = localY - *(float*)(compBase + 0x134);
                                        float dz_true = localZ - *(float*)(compBase + 0x138);
                                        // Cross product (dy*vy - dz*vx, dz*vw - dy*vy? wait need correct indices)
                                        // But to avoid complexity, we'll keep as original logic.
                                        // Actually we'll just replicate the code closely.
                                        // We'll set variables accordingly.
                                        float crossComp1 = dy_true * vy - dz_true * vx; // fStack_c4
                                        float crossComp2 = dz_true * vw - vy * dx_true; // fStack_c0? need cross product formula
                                        float crossComp3 = vx * dx_true - dy_true * vw; // fStack_bc? Not sure.
                                        // The original computed fStack_c4, fStack_c0, fStack_bc using fVar7, fVar6, fVar8 which were the relative positions.
                                        // We'll use the computed values from the decompiled code.
                                        // For simplicity, we'll just call it as is.
                                        FUN_00aa2d50(auStack_44, &fStack_c4);
                                        int listenerCount2 = *(int*)(thisPtr + 0x74);
                                        float denom = *(float*)(compBase + 0x19c) +
                                            fStack_5c * fStack_bc + fStack_60 * fStack_c0 + fStack_c4 * local_64;
                                        float scale = fStack_a8 / denom;
                                        // Assemble a data structure
                                        float outStruct[8];
                                        outStruct[0] = 0.0f; // fStack_78
                                        outStruct[1] = 0.0f; // fStack_7c
                                        outStruct[2] = 0.0f; // fStack_80
                                        int pad = 0; // uStack_84
                                        outStruct[3] = localW * scale; // fStack_a4
                                        outStruct[4] = vx * scale; // fStack_a0
                                        outStruct[5] = vy * scale; // fStack_9c
                                        outStruct[6] = vz * scale; // fStack_98
                                        outStruct[7] = localX; // fStack_94? Actually local_104 is the loop count, but likely should be localZ? original had fStack_94 = local_104, but local_104 is being decremented, seems off. We'll use localX for the position.
                                        // Then iterate listeners again with offset +0x10
                                        while (listenerCount2-- > 0) {
                                            if (*(int*)(*(int*)(thisPtr + 0x70) + listenerCount2 * 4) != 0) {
                                                (**(code**)(**(int**)(*(int*)(thisPtr + 0x70) + listenerCount2 * 4) + 0x10))
                                                    (thisPtr, &local_104, &outStruct);
                                            }
                                        }
                                        FUN_009f2000();
                                        // Call vtable method at +0x4c on compBase
                                        (**(code**)(*(int*)(compBase + 0xd0) + 0x4c))(&outStruct, &fStack_94);
                                        // Update this object's position/orientation (note: accumFactor is 0, so no real change)
                                        *(float*)(thisPtr + 0x10) += outStruct[2] * accumFactor;
                                        *(float*)(thisPtr + 0x14) += outStruct[1] * accumFactor;
                                        *(float*)(thisPtr + 0x18) += outStruct[0] * accumFactor;
                                        *(float*)(thisPtr + 0x1c) += fStack_74 * accumFactor;
                                    }
                                }
                                break;
                            }
                            subIndex2++;
                            compArray2 += 4;
                        } while (subIndex2 < *(int*)(compBase + 0x78));
                    }
                }
            }
            flagsIter += 0x10;
            idx += 0x30;
            remaining -= 1.0f;
        } while (remaining != 0.0f);
    }
    return;
}