// FUNC_NAME: AnimationBlender::blendPoses
// Address: 0x584240
// Blends two animation poses (param_1, param_2) into the global blend result, with flags (param_3) controlling behavior.
// Supports blending of float arrays (size 0x20 per bone), integer arrays (8 bytes per bone), and additional transform data.
// The result object is obtained from FUN_0056fdd0 (likely getBlenderContext).
// Returns pointer to the result object.

int AnimationBlender::blendPoses(int param_1, int param_2, byte param_3)
{
    void *pvVar1;
    int iVar2;
    int iVar3;
    float fVar4, fVar5, fVar6, fVar7, fVar8, fVar9, fVar10;
    float *pfVar11, *pfVar12, *pfVar13;
    int iVar14;
    float *pfVar15, *pfVar16, *pfVar17;
    int *_Dst, *_Src;
    int *piVar18;
    void *pvVar19;
    size_t sVar20;
    int iVar21, iVar22;
    void *_Src_00;
    int iVar23;
    uint uVar24;
    int local_50;          // min bone count
    int local_40;          // loop counter
    // Local pointers for block processing
    void *local_3c, *local_38, *local_34;
    void *local_30, *local_2c, *local_28;
    void *local_24, *local_20, *local_1c, *local_18;
    void *local_14;

    // Null checks and get blender context
    if ((param_1 == 0) || (param_2 == 0)) return 0;
    iVar14 = FUN_0056fdd0();  // getBlenderContext()
    if (iVar14 == 0) return 0;

    // If flag 4 is set, skip the main blend and go to the end section
    if ((param_3 & 4) != 0) goto LAB_00584805;

    // Get bone counts from each pose (stored at +0x38+0xc)
    iVar22 = *(int *)(*(int *)(param_1 + 0x38) + 0xc);  // count1
    iVar3 = *(int *)(*(int *)(param_2 + 0x38) + 0xc);   // count2
    local_50 = iVar22;
    if (iVar3 <= iVar22) local_50 = iVar3;  // min count

    // Reorder poses based on count to always have larger count as first input? (for later copy of excess)
    FUN_0056f800(param_2);  // likely refcount or reset function
    FUN_0056f800(param_1);
    iVar23 = param_2;
    if (iVar3 <= iVar22) iVar23 = param_1;
    FUN_0056f800(iVar23);

    // Get pointer to third array (offset +0x3c) from result context
    local_3c = *(void **)(iVar14 + 0x3c);
    iVar23 = *(int *)(param_1 + 0x34);
    _Src_00 = (void *)(*(int *)(param_1 + 0x38) + 0x10);
    pvVar1 = (void *)(iVar23 + 0x14);

    if (local_3c == (void *)0x0) {
        // Branch: third array is not present in result -> use simpler blending
        local_3c = (void *)(*(int *)(param_2 + 0x34) + 0x14);
        local_38 = (void *)(*(int *)(param_2 + 0x38) + 0x10);
        local_34 = (void *)(*(int *)(iVar14 + 0x34) + 0x14);
        pvVar19 = (void *)(*(int *)(iVar14 + 0x38) + 0x10);
        local_28 = pvVar1;
        iVar21 = local_50;

        if ((*(char *)(iVar23 + 0x10) == '\0') || (*(char *)(*(int *)(param_2 + 0x34) + 0x10) == '\0')) {
            // Either input has no blend mask: simple copy per bone
            for (; local_30 = pvVar19, local_24 = _Src_00, 0 < iVar21; iVar21--) {
                FUN_005841c0(&local_3c);            // copy/blend one bone's float data (0x20 bytes)
                local_38 = (void *)((int)local_38 + 0x20);
                local_3c = (void *)((int)local_3c + 1);
                local_34 = (void *)((int)local_34 + 1);
                _Src_00 = (void *)((int)local_24 + 0x20);
                pvVar19 = (void *)((int)local_30 + 0x20);
                local_28 = (void *)((int)local_28 + 1);
            }
        } else {
            // Both inputs have blend masks: use linear interpolation function (FUN_0056f620) and per-bone blend
            local_30 = pvVar19;
            local_24 = _Src_00;
            FUN_0056f620();      // init linear interpolation state?
            local_40 = local_50;
            if (0 < local_50) {
                local_28 = (void *)((int)local_28 + local_50);
                local_34 = (void *)((int)local_34 + local_50);
                local_3c = (void *)((int)local_3c + local_50);
                do {
                    FUN_00582b70();      // perform one element of linear blend
                    local_38 = (void *)((int)local_38 + 0x20);
                    local_40--;
                    _Src_00 = (void *)((int)_Src_00 + 0x20);
                    pvVar19 = (void *)((int)pvVar19 + 0x20);
                } while (0 < local_40);
            }
        }

        if (local_50 < iVar22) {
            // Copy remaining bones from param_1 (source1) to result (local_34)
            _memcpy(local_34, local_28, iVar22 - local_50);
            sVar20 = (iVar22 - local_50) * 0x20;
            goto LAB_005845e9;
        }
        if (local_50 < iVar3) {
            // Copy remaining bones from param_2 (source2) to result
            _memcpy(local_34, local_3c, iVar3 - local_50);
            sVar20 = (iVar3 - local_50) * 0x20;
            _Src_00 = local_38;
            goto LAB_005845e9;
        }
    } else {
        // Branch: result has third array (more data per bone, possibly offsets or normals)
        local_14 = (void *)(*(int *)(param_1 + 0x3c) + 0x10);
        local_28 = (void *)(*(int *)(param_2 + 0x34) + 0x14);
        local_24 = (void *)(*(int *)(param_2 + 0x38) + 0x10);
        local_20 = (void *)(*(int *)(param_2 + 0x3c) + 0x10);
        local_34 = (void *)(*(int *)(iVar14 + 0x34) + 0x14);
        pvVar19 = (void *)(*(int *)(iVar14 + 0x38) + 0x10);
        local_2c = (void *)((int)local_3c + 0x10);
        local_1c = pvVar1;
        iVar21 = local_50;

        if ((*(char *)(iVar23 + 0x10) == '\0') || (*(char *)(*(int *)(param_2 + 0x34) + 0x10) == '\0')) {
            for (; local_30 = pvVar19, local_18 = _Src_00, 0 < iVar21; iVar21--) {
                FUN_005864d0(&local_34, &local_1c, &local_28);  // copy/blend three arrays
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
        } else {
            local_30 = pvVar19;
            local_18 = _Src_00;
            FUN_0056f620();
            for (iVar23 = local_50; 0 < iVar23; iVar23--) {
                FUN_00582b70();
                FUN_00582fd0(&local_1c);   // blend additional data type
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

        if (local_50 < iVar22) {
            sVar20 = iVar22 - local_50;
            _memcpy(local_34, local_1c, sVar20);
            _memcpy(pvVar19, _Src_00, sVar20 * 0x20);
            sVar20 = sVar20 * 0x10;
            pvVar19 = local_2c;
            _Src_00 = local_14;
        } else {
            if (iVar3 <= local_50) goto LAB_005845f1;
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
    // Blend the float array (offset +0x40) – typically bone blend weights or additional floats
    if (*(int *)(iVar14 + 0x40) != 0) {
        fVar4 = (*(float **)(iVar14 + 0x40))[3];  // element count (floats) packed in a float? Or fourth element is count? Possibly stride.
        iVar23 = (int)fVar4 >> 2;                 // count of 4-float vectors
        pfVar11 = *(float **)(iVar14 + 0x40);
        pfVar12 = *(float **)(param_1 + 0x40);
        pfVar13 = *(float **)(param_2 + 0x40);
        // Subtract source2 from source1 and store to result (difference for later linear blend?)
        while (true) {
            pfVar16 = pfVar13 + 4;
            pfVar15 = pfVar12 + 4;
            pfVar17 = pfVar11 + 4;
            if (iVar23 < 1) break;
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
        // Process remaining floats (non-vector part)
        uVar24 = (uint)fVar4 & 3;
        if (3 < uVar24) {
            iVar23 = (uVar24 - 4 >> 2) + 1;
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
        for (; 0 < (int)uVar24; uVar24--) {
            *pfVar17 = *pfVar15 - *pfVar16;
            pfVar15++;
            pfVar16++;
            pfVar17++;
        }
    }

    // Blend the integer array (offset +0x44) – bone indices or mapping
    if (*(int *)(iVar14 + 0x44) != 0) {
        piVar18 = (int *)(*(int *)(param_1 + 0x44) + 0x10);
        _Src = (int *)(*(int *)(param_2 + 0x44) + 0x10);
        _Dst = (int *)(*(int *)(iVar14 + 0x44) + 0x10);
        iVar23 = local_50;
        if (3 < local_50) {
            // Process 4 pairs at a time (8 ints per iteration)
            iVar21 = (local_50 - 4U >> 2) + 1;
            local_3c = (void *)(iVar21 * 4);
            iVar23 = local_50 + iVar21 * -4;
            do {
                // Pair 0
                if (*_Src == -1) { *_Dst = *piVar18; iVar2 = piVar18[1]; }
                else { *_Dst = *_Src; iVar2 = _Src[1]; }
                _Dst[1] = iVar2;
                // Pair 1
                if (_Src[2] == -1) { _Dst[2] = piVar18[2]; iVar2 = piVar18[3]; }
                else { _Dst[2] = _Src[2]; iVar2 = _Src[3]; }
                _Dst[3] = iVar2;
                // Pair 2
                if (_Src[4] == -1) { _Dst[4] = piVar18[4]; iVar2 = piVar18[5]; }
                else { _Dst[4] = _Src[4]; iVar2 = _Src[5]; }
                _Dst[5] = iVar2;
                // Pair 3
                if (_Src[6] == -1) { _Dst[6] = piVar18[6]; iVar2 = piVar18[7]; }
                else { _Dst[6] = _Src[6]; iVar2 = _Src[7]; }
                _Dst[7] = iVar2;
                piVar18 += 8;
                _Src += 8;
                _Dst += 8;
                iVar21--;
            } while (iVar21 != 0);
        }
        // Process remaining pairs
        for (; 0 < iVar23; iVar23--) {
            if (*_Src == -1) { *_Dst = *piVar18; iVar21 = piVar18[1]; }
            else { *_Dst = *_Src; iVar21 = _Src[1]; }
            _Dst[1] = iVar21;
            piVar18 += 2;
            _Src += 2;
            _Dst += 2;
        }
        // Copy remaining integer pairs if counts differ
        if (local_50 < iVar22) {
            iVar22 -= local_50;
            _Src = piVar18;
        } else {
            if (iVar3 <= local_50) goto LAB_00584805;
            iVar22 = iVar3 - local_50;
        }
        _memcpy(_Dst, _Src, iVar22 * 8);
    }

LAB_00584805:
    // Final blending of transform data at offsets +0x30 and +0x10 (if flag 8 not set)
    if ((param_3 & 8) == 0) {
        local_28 = (void *)(param_2 + 0x30);
        local_34 = (void *)(param_1 + 0x30);
        local_3c = (void *)(iVar14 + 0x30);
        local_38 = (void *)(iVar14 + 0x10);
        local_30 = (void *)(param_1 + 0x10);
        local_24 = (void *)(param_2 + 0x10);
        FUN_005841c0(&local_28);  // blend additional transform arrays
    }

    return iVar14;  // pointer to the result blender context
}