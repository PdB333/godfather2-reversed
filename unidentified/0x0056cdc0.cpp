// FUN_0056cdc0: QuaternionMath::scaleFromInput
void __fastcall QuaternionMath::scaleFromInput(void* unusedThis, float* inputQuat) {
    // Compute squared norm of the input quaternion (x, y, z, w)
    float normSq = inputQuat[0] * inputQuat[0] + inputQuat[1] * inputQuat[1] +
                   inputQuat[2] * inputQuat[2] + inputQuat[3] * inputQuat[3];

    // Scale factor: kScaleBase - kScaleDiv / normSq
    // These globals are likely constants (e.g., 1.0f and 0.0f or similar)
    float scale = kScaleBase - kScaleDiv / normSq;

    // Retrieve a 64-bit handle from the engine; low 32 bits point to a quaternion,
    // high 32 bits point to additional data with a float at offset 0x0C
    uint64_t handle = FUN_00414aa0();  // Returns eax:edx (low: high)
    float* targetQuat = reinterpret_cast<float*>(handle & 0xFFFFFFFF);
    float* extra = reinterpret_cast<float*>(handle >> 32);  // Actually offset from base (int)

    // Set target quaternion's w component to kScaleBase minus extra's third float
    // extra[3] is at byte offset 0x0C (since each float is 4 bytes)
    targetQuat[3] = kScaleBase - extra[3];

    // Scale all components of the target quaternion by 'scale'
    targetQuat[0] *= scale;
    targetQuat[1] *= scale;
    targetQuat[2] *= scale;
    targetQuat[3] *= scale;
}