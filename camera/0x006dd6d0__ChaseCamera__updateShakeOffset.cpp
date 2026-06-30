// FUNC_NAME: ChaseCamera::updateShakeOffset
void __thiscall ChaseCamera::updateShakeOffset(float* outOffsetVec, const ShakeParameters* shakeParams, float t) {
    int* globalState = getGlobalCameraState(); // FUN_00471610
    outOffsetVec[0] = *(float*)(globalState + 0x30); // base X
    outOffsetVec[1] = *(float*)(globalState + 0x34); // base Y
    outOffsetVec[2] = *(float*)(globalState + 0x38); // base Z

    // Check if continuous shake flag is set (bit 0 at offset 0x8E3 from the manager pointed by this+0x2D0)
    if ((*(byte*)(*(int*)((char*)this + 0x2D0) + 0x8E3) & 1) != 0) {
        outOffsetVec[1] += shakeParams->continuousOffset; // +0x150
        return;
    }
    // Interpolated shake: lerp between shakeParams->minOffset and ->maxOffset
    outOffsetVec[1] += (shakeParams->maxOffset - shakeParams->minOffset) * t + shakeParams->minOffset;
}