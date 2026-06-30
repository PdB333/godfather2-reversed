// FUNC_NAME: ChaseCamera::updateSmoothTransform
void __fastcall ChaseCamera::updateSmoothTransform() // param_1 = this
{
    // Offsets used:
    // +0x10: input dual quaternion (8 floats) or transform data
    // +0x30: pointer to source object (e.g., target entity with transformation)
    // +0x34: pointer to output transform structure (iVar8)
    // +0x38: counter for smoothing (skips first 3 frames)
    // globals: _DAT_01218d40, _DAT_01218d44, _DAT_01218d48, _DAT_01218d50, _DAT_01218d54, _DAT_01218d58, _DAT_01218d60, _DAT_01218d64, _DAT_01218d68, _DAT_01218d70, _DAT_01218d74, _DAT_01218d78 (3x3 rotation matrix)
    // +0x90: pointer to another 4x4 matrix in output structure

    float fVar1, fVar2, fVar3;
    undefined4 *puVar4;
    undefined4 uVar5, uVar6, uVar7;
    int iVar8;
    undefined4 local_30, uStack_2c, local_28, uStack_24, local_20;
    float fStack_1c, local_18, fStack_14;

    // Get output pointer from this+0x34
    iVar8 = *(int *)(this + 0x34);
    if (iVar8 == 0)
    {
        // If output pointer is null, try to get it from the source object via a function
        iVar8 = FUN_00426a90(*(undefined4 *)(this + 0x30));
        if (iVar8 == 0)
        {
            return; // No output target available
        }
    }

    // Initialize local transform data (likely identity dual quaternion or zero)
    local_28 = DAT_00e2e230;  // initial value for first component of second half?
    uStack_24 = 0;
    local_20 = 0;
    fStack_1c = 0.0f;
    local_18 = 0.0f;
    fStack_14 = 0.0f;

    if (*(uint *)(this + 0x38) < 3)
    {
        // First 3 calls: increment counter and zero out first 2 floats of output (initial frame skip)
        *(uint *)(this + 0x38) = *(uint *)(this + 0x38) + 1;
        local_30 = 0;
        uStack_2c = 0;
    }
    else
    {
        // Normal update: read input transform from this+0x10 to this+0x2c
        // Input is treated as 8 floats: [q0, q1, q2, q3, v0, v1, v2, v3] (perhaps dual quaternion)
        local_30 = *(undefined4 *)(this + 0x10);
        uStack_2c = *(undefined4 *)(this + 0x14);
        local_28 = *(undefined4 *)(this + 0x18);
        uStack_24 = *(undefined4 *)(this + 0x1c);
        local_20 = *(undefined4 *)(this + 0x20);
        fVar1 = *(float *)(this + 0x24);
        fVar2 = *(float *)(this + 0x28);
        fVar3 = *(float *)(this + 0x2c);

        // Rotate the last 3 floats (v1,v2,v3) by a fixed 3x3 matrix (global rotation)
        // This transforms the vector part of the second quaternion (or position)
        fStack_1c = fVar2 * _DAT_01218d50 + fVar1 * _DAT_01218d40 + fVar3 * _DAT_01218d60 + _DAT_01218d70 * 0.0f;
        local_18 = fVar2 * fRam01218d54 + fVar1 * fRam01218d44 + fVar3 * _DAT_01218d64 + fRam01218d74 * 0.0f;
        fStack_14 = fVar2 * fRam01218d58 + fVar1 * fRam01218d48 + fVar3 * _DAT_01218d68 + fRam01218d78 * 0.0f;
    }

    // Write 8 floats to output structure (iVar8) as a dual quaternion or matrix
    // Offsets: +0xb0, +0xb8, +0xc0, +0xc8 (each writing 2 floats)
    *(ulonglong *)(iVar8 + 0xb0) = CONCAT44(uStack_2c, local_30);   // first two floats
    *(ulonglong *)(iVar8 + 0xb8) = CONCAT44(uStack_24, local_28);   // next two
    *(ulonglong *)(iVar8 + 0xc0) = CONCAT44(fStack_1c, local_20);   // next two
    *(ulonglong *)(iVar8 + 200) = CONCAT44(fStack_14, local_18);   // last two (offset 0xc8)

    // If the output pointer is non-zero (already checked), copy additional matrix data
    if (*(int *)(this + 0x34) != 0)
    {
        int src = *(int *)(this + 0x30);  // source object
        // Get pointer to matrix inside output structure at +0x90
        puVar4 = *(undefined4 **)(*(int *)(this + 0x34) + 0x90);
        if (puVar4 != (undefined4 *)0x0)
        {
            // Copy 16 floats (4x4 matrix) from source+0x30 to puVar4
            uVar5 = *(undefined4 *)(src + 0x34);
            uVar6 = *(undefined4 *)(src + 0x38);
            uVar7 = *(undefined4 *)(src + 0x3c);
            *puVar4 = *(undefined4 *)(src + 0x30);
            puVar4[1] = uVar5;
            puVar4[2] = uVar6;
            puVar4[3] = uVar7;

            uVar5 = *(undefined4 *)(src + 0x44);
            uVar6 = *(undefined4 *)(src + 0x48);
            uVar7 = *(undefined4 *)(src + 0x4c);
            puVar4[4] = *(undefined4 *)(src + 0x40);
            puVar4[5] = uVar5;
            puVar4[6] = uVar6;
            puVar4[7] = uVar7;

            uVar5 = *(undefined4 *)(src + 0x54);
            uVar6 = *(undefined4 *)(src + 0x58);
            uVar7 = *(undefined4 *)(src + 0x5c);
            puVar4[8] = *(undefined4 *)(src + 0x50);
            puVar4[9] = uVar5;
            puVar4[10] = uVar6;
            puVar4[0xb] = uVar7;

            uVar5 = *(undefined4 *)(src + 100);
            uVar6 = *(undefined4 *)(src + 0x68);
            uVar7 = *(undefined4 *)(src + 0x6c);
            puVar4[0xc] = *(undefined4 *)(src + 0x60);
            puVar4[0xd] = uVar5;
            puVar4[0xe] = uVar6;
            puVar4[0xf] = uVar7;
        }
    }
    return;
}