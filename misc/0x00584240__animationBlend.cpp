// FUNC_NAME: animationBlend
// Address: 0x00584240
// Blends two source poses (sourceA, sourceB) into a result pose, with optional weight blending and bone remapping.
// sourceA: pointer to first pose object
// sourceB: pointer to second pose object
// flags: bit 4 skip pose blending, bit 8 skip final transform blending

struct PoseInternal {
    // +0x00: unknown
    // +0x10: transform data (maybe a 4x4 matrix or quaternion/translation)
    // +0x30: additional blend data
    // +0x34: pointer to bone count? (array of bytes?)
    // +0x38: pointer to structure with count at +0x0C and data at +0x10 (array of 0x20-byte elements)
    // +0x3C: pointer to secondary data (another array)
    // +0x40: pointer to float array (velocity? torque?) with count at index 3
    // +0x44: pointer to int array (bone index remap) each element is two ints (maybe source/target index)
};

int animationBlend(int sourceA, int sourceB, byte flags)
{
    void *pvVar1;
    int iVar2;
    int iVar3;
    float fVar4, fVar5, fVar6, fVar7, fVar8, fVar9, fVar10;
    float *pfVar11, *pfVar12, *pfVar13, *pfVar15, *pfVar16, *pfVar17;
    int iVar14;
    int *_Dst, *_Src;
    void *pvVar19;
    size_t sVar20;
    int iVar21, iVar22, iVar23;
    void *_Src_00;
    uint uVar24;
    int local_50;
    int local_40;
    void *local_3c, *local_38, *local_34, *local_30, *local_2c, *local_28, *local_24, *local_20, *local_1c, *local_18, *local_14;

    // Get the result buffer (pool manager)
    iVar14 = FUN_0056fdd0(); // likely getResultBuffer()
    if (sourceA == 0 || sourceB == 0 || iVar14 == 0)
        return 0;

    // If bit 4 set, skip pose blending
    if ((flags & 4) != 0)
        goto LAB_00584805;

    // Get element counts from source objects (at +0x38 -> +0x0C)
    iVar22 = *(int *)(*(int *)(sourceA + 0x38) + 0xC); // sourceA bone count
    iVar3 = *(int *)(*(int *)(sourceB + 0x38) + 0xC);  // sourceB bone count
    local_50 = iVar22;
    if (iVar3 < iVar22)
        local_50 = iVar3; // use min count

    // Fetch data pointers (maybe initialize array iterators)
    FUN_0056f800(sourceB); // likely getDataPtr(sourceB)
    FUN_0056f800(sourceA); // getDataPtr(sourceA)
    iVar23 = sourceB;
    if (iVar3 <= iVar22)
        iVar23 = sourceA;
    FUN_0056f800(iVar23); // getDataPtr(whichIsSmaller)

    // Determine which blend path to take based on presence of secondary data
    local_3c = *(void **)(iVar14 + 0x3C); // result secondary data pointer
    iVar23 = *(int *)(sourceA + 0x34);    // sourceA bone weights pointer
    _Src_00 = (void *)(*(int *)(sourceA + 0x38) + 0x10); // sourceA transform array
    pvVar1 = (void *)(iVar23 + 0x14);    // sourceA weight array offset

    if (local_3c == (void *)0x0)
    {
        // No secondary data in result – simple blend path
        local_3c = (void *)(*(int *)(sourceB + 0x34) + 0x14); // sourceB weight array offset
        local_38 = (void *)(*(int *)(sourceB + 0x38) + 0x10); // sourceB transform array
        local_34 = (void *)(*(int *)(iVar14 + 0x34) + 0x14);  // result weight array offset
        pvVar19 = (void *)(*(int *)(iVar14 + 0x38) + 0x10);   // result transform array
        local_28 = pvVar1;
        iVar21 = local_50;

        if (*(char *)(iVar23 + 0x10) == '\0' || *(char *)(*(int *)(sourceB + 0x34) + 0x10) == '\0')
        {
            // No blending weights – copy sourceB transforms directly
            for (; local_30 = pvVar19, local_24 = _Src_00, 0 < iVar21; iVar21--)
            {
                FUN_005841c0(&local_3c); // blendOneWeight?
                local_38 = (void *)((int)local_38 + 0x20);
                local_3c = (void *)((int)local_3c + 1);
                local_34 = (void *)((int)local_34 + 1);
                _Src_00 = (void *)((int)local_24 + 0x20);
                pvVar19 = (void *)((int)local_30 + 0x20);
                local_28 = (void *)((int)local_28 + 1);
            }
        }
        else
        {
            // Blend with weights
            local_30 = pvVar19;
            local_24 = _Src_00;
            FUN_0056f620(); // startWeightBlend?
            local_40 = local_50;
            if (0 < local_50)
            {
                local_28 = (void *)((int)local_28 + local_50);
                local_34 = (void *)((int)local_34 + local_50);
                local_3c = (void *)((int)local_3c + local_50);
                do {
                    FUN_00582b70(); // doWeightBlend?
                    local_38 = (void *)((int)local_38 + 0x20);
                    local_40--;
                    _Src_00 = (void *)((int)_Src_00 + 0x20);
                    pvVar19 = (void *)((int)pvVar19 + 0x20);
                } while (0 < local_40);
            }
        }

        // Copy remaining transforms if one source has more bones
        if (local_50 < iVar22)
        {
            _memcpy(local_34, local_28, iVar22 - local_50);
            sVar20 = (iVar22 - local_50) * 0x20;
            goto LAB_005845e9;
        }
        if (local_50 < iVar3)
        {
            _memcpy(local_34, local_3c, iVar3 - local_50);
            sVar20 = (iVar3 - local_50) * 0x20;
            _Src_00 = local_38;
            goto LAB_005845e9;
        }
    }
    else
    {
        // Result has secondary data – complex blend path with two arrays
        local_14 = (void *)(*(int *)(sourceA + 0x3C) + 0x10); // sourceA secondary array
        local_28 = (void *)(*(int *)(sourceB + 0x34) + 0x14); // sourceB weight array offset
        local_24 = (void *)(*(int *)(sourceB + 0x38) + 0x10); // sourceB transform array
        local_20 = (void *)(*(int *)(sourceB + 0x3C) + 0x10); // sourceB secondary array
        local_34 = (void *)(*(int *)(iVar14 + 0x34) + 0x14);  // result weight array
        pvVar19 = (void *)(*(int *)(iVar14 + 0x38) + 0x10);   // result transform array
        local_2c = (void *)((int)local_3c + 0x10);            // result secondary array start
        local_1c = pvVar1;                                     // sourceA weight array
        iVar21 = local_50;

        if (*(char *)(iVar23 + 0x10) == '\0' || *(char *)(*(int *)(sourceB + 0x34) + 0x10) == '\0')
        {
            // No weights – copy sourceB
            for (; local_30 = pvVar19, local_18 = _Src_00, 0 < iVar21; iVar21--)
            {
                FUN_005864d0(&local_34, &local_1c, &local_28); // blendOneTransformAndSecondary?
                local_24 = (void *)((int)local_24 + 0x20);
                local_28 = (void *)((int)local_28 + 1);
                local_34 = (void *)((int)local_34 + 1);
                local_14 = (void *)((int)local_14 + 0x10);
                local_20 = (void *)((int)local_20 + 0x10);
                local_2c = (void *)((int)local_2c + 0x10);
                _Src_00 = (void *)((int)local_18 + 0x20);
                pvVar19 = (void *)((int)local_30 + 0x20);
                local_1c = (void *)((int)local_1c + 1);
            }
        }
        else
        {
            // Blend with weights
            local_30 = pvVar19;
            local_18 = _Src_00;
            FUN_0056f620();
            for (iVar23 = local_50; 0 < iVar23; iVar23--)
            {
                FUN_00582b70(); // doWeightCalculation?
                FUN_00582fd0(&local_1c); // applyWeightSecondary?
                local_24 = (void *)((int)local_24 + 0x20);
                local_1c = (void *)((int)local_1c + 1);
                local_28 = (void *)((int)local_28 + 1);
                local_34 = (void *)((int)local_34 + 1);
                local_14 = (void *)((int)local_14 + 0x10);
                local_20 = (void *)((int)local_20 + 0x10);
                local_2c = (void *)((int)local_2c + 0x10);
                _Src_00 = (void *)((int)_Src_00 + 0x20);
                pvVar19 = (void *)((int)pvVar19 + 0x20);
                local_30 = pvVar19;
                local_18 = _Src_00;
            }
        }

        // Copy remaining if one source longer
        if (local_50 < iVar22)
        {
            sVar20 = iVar22 - local_50;
            _memcpy(local_34, local_1c, sVar20); // weights
            _memcpy(pvVar19, _Src_00, sVar20 * 0x20); // transforms
            sVar20 = sVar20 * 0x10;
            pvVar19 = local_2c;  // secondary array
            _Src_00 = local_14;
        }
        else
        {
            if (iVar3 <= local_50)
                goto LAB_005845f1;
            sVar20 = iVar3 - local_50;
            _memcpy(local_34, local_28, sVar20);
            _memcpy(pvVar19, local_24, sVar20 * 0x20);
            sVar20 = sVar20 * 0x10;
            pvVar19 = local_2c;
            _Src_00 = local_20;
        }

LAB_005845e9:
        _memcpy(pvVar19, _Src_00, sVar20);
    }

LAB_005845f1:
    // Blend velocity/torque data (array at +0x40)
    if (*(int *)(iVar14 + 0x40) != 0)
    {
        fVar4 = (*(float **)(iVar14 + 0x40))[3]; // count of items (fourth float)
        iVar23 = (int)fVar4 >> 2;
        pfVar11 = *(float **)(iVar14 + 0x40);
        pfVar12 = *(float **)(sourceA + 0x40);
        pfVar13 = *(float **)(sourceB + 0x40);
        while (true)
        {
            pfVar16 = pfVar13 + 4;
            pfVar15 = pfVar12 + 4;
            pfVar17 = pfVar11 + 4;
            if (iVar23 < 1) break;
            // Subtract sourceB from sourceA for each component (maybe torque/velocity)
            fVar5 = pfVar13[5];
            fVar6 = pfVar13[6];
            fVar7 = pfVar13[7];
            fVar8 = pfVar12[5];
            fVar9 = pfVar12[6];
            fVar10 = pfVar12[7];
            *pfVar17 = *pfVar15 - *pfVar16;
            pfVar11[5] = fVar8 - fVar5;
            pfVar11[6] = fVar9 - fVar6;
            pfVar11[7] = fVar10 - fVar7;
            iVar23--;
            pfVar11 = pfVar17;
            pfVar12 = pfVar15;
            pfVar13 = pfVar16;
        }
        uVar24 = (uint)fVar4 & 3;
        if (3 < uVar24)
        {
            iVar23 = ((uVar24 - 4) >> 2) + 1;
            uVar24 = uVar24 + iVar23 * -4;
            do {
                *pfVar17 = *pfVar15 - *pfVar16;
                pfVar17[1] = pfVar15[1] - pfVar16[1];
                pfVar17[2] = pfVar15[2] - pfVar16[2];
                pfVar17[3] = pfVar15[3] - pfVar16[3];
                pfVar15 += 4;
                pfVar16 += 4;
                pfVar17 += 4;
                iVar23--;
            } while (iVar23 != 0);
        }
        for (; (int)uVar24 > 0; uVar24--)
        {
            *pfVar17 = *pfVar15 - *pfVar16;
            pfVar15++;
            pfVar16++;
            pfVar17++;
        }
    }

    // Blend bone index mapping (array at +0x44)
    if (*(int *)(iVar14 + 0x44) != 0)
    {
        piVar18 = (int *)(*(int *)(sourceA + 0x44) + 0x10); // sourceA mapping
        _Src = (int *)(*(int *)(sourceB + 0x44) + 0x10);    // sourceB mapping
        _Dst = (int *)(*(int *)(iVar14 + 0x44) + 0x10);     // result mapping
        iVar23 = local_50; // number of entries based on pose count
        if (3 < local_50)
        {
            iVar21 = ((local_50 - 4U) >> 2) + 1;
            local_3c = (void *)(iVar21 * 4);
            iVar23 = local_50 + iVar21 * -4;
            do {
                // For each entry of 2 ints, if first int is -1, copy from sourceA, else from sourceB
                if (*_Src == -1) {
                    *_Dst = *piVar18;
                    iVar2 = piVar18[1];
                } else {
                    *_Dst = *_Src;
                    iVar2 = _Src[1];
                }
                _Dst[1] = iVar2;
                // repeat for next three entries
                if (_Src[2] == -1) {
                    _Dst[2] = piVar18[2];
                    iVar2 = piVar18[3];
                } else {
                    _Dst[2] = _Src[2];
                    iVar2 = _Src[3];
                }
                _Dst[3] = iVar2;
                if (_Src[4] == -1) {
                    _Dst[4] = piVar18[4];
                    iVar2 = piVar18[5];
                } else {
                    _Dst[4] = _Src[4];
                    iVar2 = _Src[5];
                }
                _Dst[5] = iVar2;
                if (_Src[6] == -1) {
                    _Dst[6] = piVar18[6];
                    iVar2 = piVar18[7];
                } else {
                    _Dst[6] = _Src[6];
                    iVar2 = _Src[7];
                }
                _Dst[7] = iVar2;
                piVar18 += 8;
                _Src += 8;
                _Dst += 8;
                iVar21--;
            } while (iVar21 != 0);
        }
        for (; iVar23 > 0; iVar23--)
        {
            if (*_Src == -1) {
                *_Dst = *piVar18;
                iVar21 = piVar18[1];
            } else {
                *_Dst = *_Src;
                iVar21 = _Src[1];
            }
            _Dst[1] = iVar21;
            piVar18 += 2;
            _Src += 2;
            _Dst += 2;
        }
        // Copy remaining mappings if one source has more
        if (local_50 < iVar22)
        {
            iVar22 = iVar22 - local_50;
            _Src = piVar18;
        }
        else
        {
            if (iVar3 <= local_50)
                goto LAB_00584805;
            iVar22 = iVar3 - local_50;
        }
        _memcpy(_Dst, _Src, iVar22 * 8);
    }

LAB_00584805:
    // Final transform blend (if bit 8 not set)
    if ((flags & 8) == 0)
    {
        local_28 = (void *)(sourceB + 0x30);
        local_34 = (void *)(sourceA + 0x30);
        local_3c = (void *)(iVar14 + 0x30);
        local_38 = (void *)(iVar14 + 0x10);
        local_30 = (void *)(sourceA + 0x10);
        local_24 = (void *)(sourceB + 0x10);
        FUN_005841c0(&local_28); // blendFinalTransform
    }

    return iVar14;
}