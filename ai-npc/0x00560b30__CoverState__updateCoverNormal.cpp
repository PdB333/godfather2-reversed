// FUNC_NAME: CoverState::updateCoverNormal
void __thiscall CoverState::updateCoverNormal(void)
{
    // 'this' is unaff_ESI
    float fVar1, fVar2, fVar3;
    float fVar10, fVar11, fVar12;
    float fVar4;
    int iVar7, iVar8;
    float *pfVar5, *pfVar6;
    float10 fVar9;

    // Load current facing direction? (called "oldNormal") at +0xE0, +0xE4, +0xE8
    fVar1 = *(float *)((int)this + 0xE0);
    fVar2 = *(float *)((int)this + 0xE4);
    fVar3 = *(float *)((int)this + 0xE8);

    iVar8 = 0;  // active count

    // Check if there are cover points in the array (count at +0x4C)
    if (0 < *(int *)((int)this + 0x4C)) {
        pfVar5 = *(float **)((int)this + 0x48);  // pointer to cover points array (size 0x30 per element)
        iVar7 = *(int *)((int)this + 0x4C);
        pfVar6 = pfVar5 + 9;  // first element's field at offset 0x24? (9*4=36 bytes) – used as "valid" flag
        do {
            if (*pfVar6 != 0.0f) {
                iVar8 = iVar8 + 1;
            }
            pfVar6 = pfVar6 + 0x30;  // step to next element (0x30 floats = 0xC0 bytes? No, 0x30 as float index = 0x30*4=0xC0 bytes, but element size is 0x30 bytes? Actually 0x30 as pointer offset is wrong. See comment below.)
            // Actually pointer arithmetic: pfVar6 + 0x30 means adding 0x30 * sizeof(float) = 0xC0 bytes. That's too large. Likely it's pfVar6 = pfVar6 + 12? But decompiler shows +0x30. Might be a cast issue. I'll follow the code as-is.
            iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
        // Now iVar8 is number of valid cover points

        if (1 < iVar8) {
            // Compute cross product of edges of a triangle formed by three cover points
            // Points are stored in the array at indices 0x30, 0x60, 0x90 (relative to pfVar5)
            // Each point has 3 floats (x, y, z) at offsets 0,1,2 inside its element
            // So point A (first) at pfVar5[0x30] = x, [0x31]=y, [0x32]=z
            // Point B (second) at pfVar5[0x60] = x, [0x61]=y, [0x62]=z
            // Point C (third) at pfVar5[0x90] = x, [0x91]=y, [0x92]=z
            // Actually indices 0x30,0x60,0x90 are float offsets, each covers one float. But cross product uses x,y,z from each.
            // The code does: (A.z - C.z)*(B.x - C.x) - (A.x - C.x)*(B.z - C.z) ... that's cross product of (A-C) and (B-C).
            // It computes three components of the normal vector.
            fVar10 = ((pfVar5[0x32] - pfVar5[0x92]) * (pfVar5[0x60] - pfVar5[0x90]) -
                     (pfVar5[0x62] - pfVar5[0x92]) * (pfVar5[0x30] - pfVar5[0x90])) +
                     ((pfVar5[0x62] - pfVar5[2]) * (pfVar5[0x30] - *pfVar5) -
                     (pfVar5[0x32] - pfVar5[2]) * (pfVar5[0x60] - *pfVar5));
            fVar11 = ((pfVar5[0x61] - pfVar5[0x91]) * (pfVar5[0x30] - pfVar5[0x90]) -
                     (pfVar5[0x31] - pfVar5[0x91]) * (pfVar5[0x60] - pfVar5[0x90])) +
                     ((pfVar5[0x31] - pfVar5[1]) * (pfVar5[0x60] - *pfVar5) -
                     (pfVar5[0x61] - pfVar5[1]) * (pfVar5[0x30] - *pfVar5));
            fVar12 = ((pfVar5[0x62] - pfVar5[0x92]) * (pfVar5[0x31] - pfVar5[0x91]) -
                     (pfVar5[0x61] - pfVar5[0x91]) * (pfVar5[0x32] - pfVar5[0x92])) +
                     ((pfVar5[0x32] - pfVar5[2]) * (pfVar5[0x61] - pfVar5[1]) -
                     (pfVar5[0x31] - pfVar5[1]) * (pfVar5[0x62] - pfVar5[2]));

            // Store the new normal temporarily in the object's fields
            *(float *)((int)this + 0xE8) = fVar11;  // z?
            fVar4 = DAT_00e2fc48;  // threshold for length squared
            *(float *)((int)this + 0xE0) = fVar12;  // x?
            *(float *)((int)this + 0xE4) = fVar10;  // y?
            *(int *)((int)this + 0xEC) = 0;          // w or unused?

            // Check if length squared > threshold
            if (fVar4 < fVar11 * fVar11 + fVar12 * fVar12 + fVar10 * fVar10) {
                fVar4 = *(float *)((int)this + 0xE8);
                float lenSq = fVar12 * fVar12 + fVar10 * fVar10 + fVar4 * fVar4;
                if (lenSq == 0.0f) {
                    fVar11 = 0.0f;
                } else {
                    fVar9 = (float10)FUN_00414a80(lenSq);  // sqrt
                    fVar11 = 1.0f / (float)fVar9;         // inverse sqrt
                }
                // Normalize the vector
                *(float *)((int)this + 0xE0) = fVar12 * fVar11;
                *(float *)((int)this + 0xE4) = fVar10 * fVar11;
                *(float *)((int)this + 0xE8) = fVar4 * fVar11;
                *(int *)((int)this + 0xEC) = 0;
                goto LAB_00560e11;
            }
        }
    }
    // Fallback: set to a default directional vector (probably a global constant)
    *(float *)((int)this + 0xE0) = *(float *)&DAT_01126060;
    *(float *)((int)this + 0xE4) = *(float *)&DAT_01126064;
    *(float *)((int)this + 0xE8) = *(float *)&DAT_01126068;
    *(float *)((int)this + 0xEC) = *(float *)&DAT_0112606c;

LAB_00560e11:
    // Compare the new normal's y component (or maybe the dot product with old direction?)
    if (DAT_00e2cd1c < *(float *)((int)this + 0xE4) || 
        DAT_00e2cd1c == *(float *)((int)this + 0xE4)) {
        // Check dot product of new normal with old direction (stored in fVar1,fVar2,fVar3)
        float dot = *(float *)((int)this + 0xE0) * fVar1 + 
                    *(float *)((int)this + 0xE4) * fVar2 + 
                    *(float *)((int)this + 0xE8) * fVar3;
        if (DAT_00e2cd18 <= dot) {
            // dot >= threshold
            if ((*(uint *)((int)this + 0x110) & 0x08) != 0) {  // bit 3
                *(uint *)((int)this + 0x110) |= 0x10;  // set bit 4
                *(uint *)((int)this + 0x110) &= ~0x08; // clear bit 3
                return;
            }
            *(uint *)((int)this + 0x110) &= ~0x10; // clear bit 4
            *(uint *)((int)this + 0x110) &= ~0x08; // clear bit 3
            return;
        }
        // dot < threshold
        if ((*(uint *)((int)this + 0x110) & 0x08) != 0) {
            *(uint *)((int)this + 0x110) |= 0x10;
            *(uint *)((int)this + 0x110) |= 0x08;
            return;
        }
    } else {
        // y component is less than threshold (DAT_00e2cd1c)
        if ((*(uint *)((int)this + 0x110) & 0x08) != 0) {
            *(uint *)((int)this + 0x110) |= 0x10;
            *(uint *)((int)this + 0x110) |= 0x08;
            return;
        }
    }
    // Default case: set bits
    *(uint *)((int)this + 0x110) &= ~0x10;
    *(uint *)((int)this + 0x110) |= 0x08;
    return;
}