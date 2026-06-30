// FUNC_NAME: AnimationController::evaluateBlendWeights
int __thiscall FUN_00595950(void* this) {
    float fVar1;
    float* in_EAX; // this pointer
    int iVar2;
    int iVar3;
    float fVar4;
    
    // If target animation index is 0
    if (*(short*)((int)in_EAX + 6) == 0) {
        // Call function at offset 0x34 from global DAT_012055a8 (likely a rendering/transform function)
        (**(code**)(*DAT_012055a8 + 0x34))(0, 0, 0, param_1);
        return 1;
    }
    
    // If current animation index is not 1
    if (*(short*)(in_EAX + 2) != 1) {
        // Call error/default handler
        (**(code**)(*DAT_01205590 + 4))();
    }
    
    // If target animation index is 1 (single blend)
    if (*(short*)((int)in_EAX + 6) == 1) {
        fVar4 = in_EAX[3];
        // Call rendering function with animation data
        (**(code**)(*DAT_012055a8 + 0x34))
                  (*(undefined4*)((int)fVar4 + 4), *(undefined4*)((int)fVar4 + 8),
                   *(undefined4*)((int)fVar4 + 0xc), param_1);
        return 1;
    }
    
    // If current blend index equals target index (direct mapping)
    if (*(short*)(in_EAX + 1) == *(short*)((int)in_EAX + 6)) {
        iVar2 = (uint)*(ushort*)((int)in_EAX + 6) * 0x10 + (int)in_EAX[3];
        (**(code**)(*DAT_012055a8 + 0x34))
                  (*(undefined4*)(iVar2 + -0xc), *(undefined4*)(iVar2 + -8), *(undefined4*)(iVar2 + -4)
                   , param_1);
        return 1;
    }
    
    // Interpolate between two animation frames using blend weight
    fVar1 = in_EAX[3];
    iVar3 = (uint)*(ushort*)(in_EAX + 1) * 0x10;
    fVar4 = *(float*)(iVar3 + -0x10 + (int)fVar1);
    iVar2 = iVar3 + (int)fVar1;
    fVar4 = (*in_EAX - fVar4) / (*(float*)(iVar3 + (int)fVar1) - fVar4);
    
    // Clamp blend weight
    if ((fVar4 < DAT_00e2b05c) || (DAT_00e2b1a4 < fVar4)) {
        (**(code**)(*DAT_01205590 + 4))();
    }
    
    // Perform linear interpolation between two animation frames
    (**(code**)(*DAT_012055a8 + 0x34))
              ((*(float*)(iVar2 + 4) - *(float*)(iVar2 + -0xc)) * fVar4 + *(float*)(iVar2 + -0xc),
               (*(float*)(iVar2 + 8) - *(float*)(iVar2 + -8)) * fVar4 + *(float*)(iVar2 + -8),
               (*(float*)(iVar2 + 0xc) - *(float*)(iVar2 + -4)) * fVar4 + *(float*)(iVar2 + -4),
               param_1);
    return 0;
}