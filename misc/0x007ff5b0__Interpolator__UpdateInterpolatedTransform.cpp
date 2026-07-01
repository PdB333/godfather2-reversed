// FUNC_NAME: Interpolator::UpdateInterpolatedTransform
void __thiscall Interpolator::UpdateInterpolatedTransform(int* thisPtr, int* target) {
    float fVar1, fVar2, fVar4;
    int iVar3;
    float local_18, fStack_14;
    long long local_c;

    // Check interpolation enabled flag at offset +0x3D4 (0xF5 * 4)
    if (thisPtr[0xF5] != 0) {
        // Likely call to get frame delta time or update engine state
        FUN_0046f9c0(target);
        // Get current state/transform source (e.g., player position)
        iVar3 = FUN_00471610();

        fVar1 = *(float*)(target + 0x38);           // target Z or rotation
        fVar4 = _DAT_00d5780c / *(float*)(DAT_01223480 + 0x60); // time alpha factor
        fVar2 = *(float*)(iVar3 + 0x38);            // source Z or rotation

        // Extract packed 2D floats from offset +0x30
        local_18 = (float)*(long long*)(target + 0x30);       // target XY low
        local_c._0_4_ = (float)*(long long*)(iVar3 + 0x30);    // source XY low
        fStack_14 = (float)(((unsigned long long)*(long long*)(target + 0x30)) >> 32); // target XY high
        local_c._4_4_ = (float)(((unsigned long long)*(long long*)(iVar3 + 0x30)) >> 32); // source XY high

        // Compute interpolated 2D delta
        local_c = CONCAT44((fStack_14 - local_c._4_4_) * fVar4,
                          (local_18 - (float)local_c) * fVar4);
        *(long long*)(thisPtr + 0x109) = local_c;    // store interpolated XY at +0x424 (0x109*4)

        // Store interpolated Z/rotation at +0x42C (0x10b*4)
        thisPtr[0x10b] = (int)((fVar1 - fVar2) * fVar4);
        return;
    }

    // Default path: call virtual function at vtable offset 0x28 (0x28/4 = 10)
    (**(void (__thiscall**)(int*))(*(int*)thisPtr + 0x28))(target);
}