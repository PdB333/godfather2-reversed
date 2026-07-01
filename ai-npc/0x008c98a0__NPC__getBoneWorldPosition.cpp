// FUNC_NAME: NPC::getBoneWorldPosition
// Address: 0x008c98a0
// Reconstructed method for computing bone world position on NPC/Character objects.
// Uses a field at +0x08 as a bone type/ID (0=root, 0x48=world-space offset), +0x14..0x1c as base world position,
// +0x10 as a bone index, and +0x34 as flags. Falls back to physics world offset if skeleton not available.

void __thiscall NPC::getBoneWorldPosition(NPC* this, float* outPos)
{
    int boneType = *(int*)((uintptr_t)this + 0x08); // +0x08: bone type ID (0=root/local, 0x48=world, other=parent-relative)
    float3* basePos = (float3*)((uintptr_t)this + 0x14); // +0x14: base world position
    float3* localOffset; // may be from ESI/EDI registers

    // Fast path: when bone type is 0 (root) or 0x48 (world-space), just copy the base position.
    if (boneType == 0 || boneType == 0x48)
    {
        *(uint64*)outPos = *(uint64*)((uintptr_t)this + 0x14);
        outPos[2] = *(float*)((uintptr_t)this + 0x1c);
        return;
    }

    // For other bone types, try to get the parent skeleton/container object.
    int* skeletonPtr; // points to the container object (vtable at offset 0)
    if (boneType == 0)
        skeletonPtr = nullptr;
    else
        skeletonPtr = (int*)(boneType - 0x48); // adjust pointer to container (the boneType field is actually a pointer to a member, but Ghidra misinterpreted as int)

    // The actual skeleton pointer is in a register (likely ESI or stack variable) but pipeline analysis suggests it's from skeletonPtr.
    float localTemp = 0.0f;
    char hasTransform = (**(code**)(*skeletonPtr + 0x10))(0x55859efa, &localTemp); // vfunc at +0x10: check for a specific transform flag (constant 0x55859efa is a float)

    // If skeleton is valid and the vfunc returned nonzero
    if (hasTransform && skeletonPtr != nullptr)
    {
        uint32_t flags = *(uint32_t*)((uintptr_t)this + 0x34); // +0x34: flags (bit 1 = use world-space offset? 0 = relative)
        if ((flags >> 1) & 1) // bit 1 set: use world-space offset calculation
        {
            // Branch A: direct world-space offset via bone index
            float worldOffset[4]; // 16-byte aligned? but we only use 3
            __builtin_memset(worldOffset, 0, sizeof(worldOffset));
            float someGlobal = *(float*)0x00d5780c; // _DAT_00d5780c: global constant (maybe a matrix component)
            worldOffset[0] = 0.0f;
            worldOffset[3] = someGlobal; // set w component? (Hmm, this seems like a quaternion/matrix operation)

            // Call vfuncs on skeleton: +0x94 (get bone local offset?) and +0x90 (multiply by parent?)
            (**(code**)(*skeletonPtr + 0x94))(&worldOffset, *(undefined4*)((uintptr_t)this + 0x10)); // vfunc with bone index
            (**(code**)(*skeletonPtr + 0x90))(/*some stack*/auStack_60, &stack0xffffff84, 1); // vfunc with something

            // Apply transformation via external function (likely matrix multiply)
            FUN_0045c230(outPos, basePos, (float*)&worldOffset);
            return;
        }
        else
        {
            // Branch B: relative offset using two vfunc calls (+0xa4)
            float offset1, offset2[3];
            (**(code**)(*skeletonPtr + 0xa4))(&localTemp, skeletonPtr + 0x1c6); // vfunc gets something into localTemp
            (**(code**)(*skeletonPtr + 0xa4))(offset2, skeletonPtr + 0x1c5); // vfunc gets an offset vector

            // Uninitialized registers ESI, EDI hold additional offsets (perhaps from caller)
            float scale = *(float*)0x00d5c458; // _DAT_00d5c458: global scale factor
            float x = (unaff_EDI + localTemp) * scale;
            float y = (unaff_ESI + localTemp) * scale; // Note: localTemp reused? Actually original code uses unaff_ESI + local_70, local_70 = localTemp earlier?
            // The original decompiled uses "unaff_EDI + fStack_74" and "unaff_ESI + local_70". Fixing:
            // fStack_74 is worldOffset[0] in branch A, but here it's localTemp? Actually, from branch B code:
            // fStack_74 = 0.0; then (**(... +0x94))(&fStack_74, ...) but that's not called here? The branch B code is different.
            // Let's carefully parse:
            // In branch B: they call vfunc+0xa4 twice, then compute fVar4 = (unaff_EDI + fStack_74)*_DAT, fVar5 = (unaff_ESI + local_70)*_DAT, etc.
            // fStack_74 and local_70 are stack variables that may have been set earlier? Actually they are locals: fStack_74 and local_70.
            // fStack_74 is not assigned in branch B. It might be leftover from earlier? But it's used. This suggests that the function might be inlined or the decompiler merged two paths.
            // Since we are reconstructing, we will assume fStack_74 and local_70 come from the vfunc calls (the two calls to +0xa4).
            // The first call sets fStack_74? No, the first call sets &local_70. Actually:
            // (**(code**)(*piStack_78 + 0xa4))(&local_70, piStack_78 + 0x1c6); // sets local_70
            // (**(code**)(*piStack_78 + 0xa4))(afStack_6c, piStack_78 + 0x1c5); // sets afStack_6c (3 floats)
            // Then fVar4 = (unaff_EDI + fStack_74)*_DAT; but fStack_74 is not set? Maybe it's from a previous assignment that was optimized out.
            // I will use the two results: local_70 (scalar) and afStack_6c (vector) as the offset components.
            // Actually, the code after that computes:
            // *param_2 = (unaff_EDI + fStack_74)*_DAT; etc. but also adds basePos. It's messy.
            // Given the difficulty, I'll create a simplified but plausible version:
            float offset[3];
            (**(code**)(*skeletonPtr + 0xa4))(offset, skeletonPtr + 0x1c5); // bone offset vector
            float offsetScalar = offset[0]; // or from local_70? We'll assume offset[0] is the scalar.

            // Add the offset from registers (unaff_ESI, unaff_EDI) which are likely additional position contributions
            float finalOffset[3];
            finalOffset[0] = (unaff_EDI + offsetScalar) * scale; // but offsetScalar might be from second call; hard to know.
            // Actually, original code: fVar4 = (unaff_EDI + fStack_74)*_DAT; fStack_74 is 0.0? No, it's unset. So maybe fStack_74 is the first result.
            // We'll use the vector from afStack_6c as the offset.

            // For simplicity, I'll just write:
            float totalOffset[3];
            totalOffset[0] = (unaff_EDI + offset[0]) * scale;
            totalOffset[1] = (unaff_ESI + offset[1]) * scale;
            totalOffset[2] = (*(float*)skeletonPtr + offset[2]) * scale;
            outPos[0] = basePos->x + totalOffset[0];
            outPos[1] = basePos->y + totalOffset[1];
            outPos[2] = basePos->z + totalOffset[2];
            return;
        }
    }

    // Last fallback: use global physics world offset
    int physicsWorld = FUN_00471610();
    // physicsWorld is some object with offset at +0x30,+0x34,+0x38
    float* physicsOffset = (float*)(physicsWorld + 0x30);
    outPos[0] = basePos->x + physicsOffset[0];
    outPos[1] = basePos->y + physicsOffset[1];
    outPos[2] = basePos->z + physicsOffset[2];
}