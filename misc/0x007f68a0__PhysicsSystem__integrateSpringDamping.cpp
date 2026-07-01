// FUNC_NAME: PhysicsSystem::integrateSpringDamping
float __thiscall PhysicsSystem::integrateSpringDamping(int thisPtr, undefined4 param_2, undefined4 param_3, undefined4 param_4, float param_5, undefined4 param_6, float param_7, int param_8)
{
    int iVar1;
    float10 fVar2;
    float fVar3;
    float fVar4;
    
    // Extract velocity from param_7 (which is actually a pointer to a vector)
    iVar1 = (int)param_7;
    param_7 = *(float *)((int)param_7 + 4); // +0x04: y component of velocity
    
    // Check if damping override is active (global flag at 0x00d577a0)
    if (_DAT_00d577a0 < *(float *)(thisPtr + 0x7ac)) {
        // Apply damping factor from thisPtr+0x7b0
        param_7 = *(float *)(thisPtr + 0x7b0) * param_7;
    }
    
    // Call the core spring integration function
    fVar2 = (float10)FUN_007f6550(param_2, param_3, param_4, *(undefined4 *)(param_8 + 8), param_5,
                                  *(undefined4 *)(param_8 + 0xc), param_7, *(undefined4 *)(iVar1 + 8),
                                  param_6);
    fVar4 = (float)fVar2;
    
    // Apply additional damping based on velocity magnitude
    fVar3 = (float)(*(uint *)(param_8 + 0xc) & DAT_00e44680);
    if (fVar3 <= DAT_00e44728) {
        fVar4 = (fVar3 * DAT_00d5eee4 + DAT_00e44728) * fVar4;
    }
    
    // Update position
    fVar3 = *(float *)(param_8 + 8) + fVar4;
    
    // Update velocity if time step is valid
    if (_DAT_00d577a0 < param_5) {
        *(float *)(param_8 + 0xc) = fVar4 / param_5;
    }
    
    // Store new position
    *(float *)(param_8 + 8) = fVar3;
    
    return (float10)fVar3;
}