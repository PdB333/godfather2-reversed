// FUNC_NAME: ConstraintSolver::solveConstraint
uint __thiscall ConstraintSolver::solveConstraint(void* this, int constraintIndex, float* quatFrom, float* quatTo, float blendFactor)
{
    int iVar1;
    uint uVar2;
    int iVar3;
    bool bVar4;
    uint uVar5;
    // Thread-local storage pointer (from FS segment)
    // +0x2c points to a TLS structure, then dereference +8 to get base pointer
    int basePtr = *(int*)(*(int*)(__readfsdword(0x2c) + 8));
    // param_1 (passed as int*) is actually a pointer to an offset into an array of size 0x50
    iVar1 = basePtr + constraintIndex * 0x50 + *thisPtr; // thisPtr is the passed int pointer param_1 reinterpreted
    // +0xac in this (unaff_EDI) is a pointer to a table of pointers indexed by a short at iVar1+0x56
    uint uVar2 = *(uint*)(*(int*)(this + 0xac) + (uint)(*(ushort*)(iVar1 + 0x56)) * 4);
    uVar5 = uVar2;
    // Check flags: bit0 of +0x48 must be set
    if ((((*(byte*)(uVar2 + 0x48) & 1) != 0) &&
         // +0x24 points to some state; +0x155 signed > -1
         (iVar3 = *(int*)(this + 0x24), *(char*)(iVar3 + 0x155) > -1) &&
         // Global time threshold
         (DAT_00e44598 < blendFactor))) {
        FUN_00414aa0();
        // Store a global random value (maybe seed)
        local_34 = DAT_00e2b1a4;
        // Compare squared length of vector at iVar1+0x30 with global threshold
        bVar4 = DAT_00e2e780 <
                (*(float*)(iVar1 + 0x30) * *(float*)(iVar1 + 0x30) +
                 *(float*)(iVar1 + 0x34) * *(float*)(iVar1 + 0x34) +
                 *(float*)(iVar1 + 0x38) * *(float*)(iVar1 + 0x38));
        // Copy quatTo into local quat (4 floats)
        float localQuat[4];
        localQuat[0] = *quatTo;
        localQuat[1] = quatTo[1];
        localQuat[2] = quatTo[2];
        localQuat[3] = quatTo[3];
        // Normalize or conjugate quaternion? (in-place)
        FUN_0044d680(&localQuat, &localQuat);
        if (bVar4) {
            // If vector length is large, override with quatFrom
            localQuat[0] = *quatFrom;
            localQuat[1] = quatFrom[1];
            localQuat[2] = quatFrom[2];
            localQuat[3] = quatFrom[3];
        }
        else {
            // Blend quaternions: result = blendFactor * localQuat + quatFrom
            localQuat[0] = blendFactor * localQuat[0] + *quatFrom;
            localQuat[1] = blendFactor * localQuat[1] + quatFrom[1];
            localQuat[2] = blendFactor * localQuat[2] + quatFrom[2];
            localQuat[3] = blendFactor * localQuat[3] + quatFrom[3];
        }
        // Call solver with output buffer, blended quat, and other parameters
        char buf1[12];  // local_40
        char buf2[16];  // local_30
        char buf3[28];  // local_20
        uVar5 = FUN_004afee0(buf1, &localQuat, buf3, buf2, *(undefined4*)(iVar3 + 0x114), 0, 0);
        if ((char)uVar5 != 0) {
            if (bVar4) {
                // Reset some state if vector length was large
                FUN_00509590(this); // param_1 passed as this?
            }
            // Update flags: clear bit0, set bit1
            *(uint*)(uVar2 + 0x48) = (*(uint*)(uVar2 + 0x48) & 0xFFFFFFFE) | 2;
            uVar5 = uVar2;
        }
    }
    // Return the pointer with lower byte zeroed (likely flag/status)
    return uVar5 & 0xFFFFFF00;
}