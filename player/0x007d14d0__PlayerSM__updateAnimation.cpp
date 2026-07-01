// FUNC_NAME: PlayerSM::updateAnimation 
void __thiscall PlayerSM::updateAnimation(int thisPtr, int param_2)
{
    char cVar1;
    int uVar2;
    float10 fVar3;
    float fVar4;

    // Check state at +0x94 (likely an enum for animation state)
    if (*(int*)(thisPtr + 0x94) != 3) {
        if (*(int*)(thisPtr + 0x94) != 2) goto LAB_007d1509;
        uVar2 = getControllerIndex(0); // FUN_00798f50
        cVar1 = isControllerConnected(uVar2); // FUN_0079e920
        if (cVar1 == '\0') goto LAB_007d1509;
    }
    setAnimationState(0, 0); // FUN_007ab9a0
LAB_007d1509:
    updateSkeleton(*(int*)(thisPtr + 0x74)); // FUN_007ac4f0
    updateModel(); // FUN_007d0750

    // Check blend conditions: either time threshold exceeded or animation force flag
    if (( (float)((uint)*(float*)(thisPtr + 0x7c) & g_animationTimeMask) <= g_animationBlendThreshold ) ||
        ((*(uint*)(*(int*)(thisPtr + 0x58) + 0x8e0) >> 1 & 1) != 0)) {
        fVar4 = *(float*)(thisPtr + 0x88);
        uVar2 = 0;
        fVar3 = (float10)lerp(*(float*)(thisPtr + 0x7c) * g_animationBlendSpeed + fVar4, fVar4, 0.0f); // FUN_006d6350
        applyAnimationLayer((float)fVar3, fVar4, uVar2); // FUN_007d09f0
    }
    finalizeAnimation(param_2); // FUN_007d0940
    return;
}