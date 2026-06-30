// FUNC_NAME: MathUtils::scaleVectorByDistanceFactor
void __fastcall MathUtils::scaleVectorByDistanceFactor(float *this, float *inputVec) {
    // this: unused (likely a dummy this pointer or static method)
    // inputVec: pointer to 4 floats (x,y,z,w) representing a vector whose squared length is used
    // Global constants:
    //   DAT_00e44564: some constant (e.g., maxFactor)
    //   DAT_00e2b1a4: another constant (e.g., falloffStrength)
    extern float DAT_00e44564;
    extern float DAT_00e2b1a4;

    // Compute squared length of inputVec
    float sqLen = inputVec[0] * inputVec[0] + inputVec[1] * inputVec[1] + inputVec[2] * inputVec[2] + inputVec[3] * inputVec[3];
    // Compute scaling factor: maxFactor - (falloffStrength / sqLen)
    float scaleFactor = DAT_00e44564 - (DAT_00e2b1a4 / sqLen);

    // Get a vector from some internal source (e.g., velocity, position)
    // FUN_00414aa0 returns a 64-bit value: low 32 bits = float* to vector, high 32 bits = base address for w component
    uint64_t raw = FUN_00414aa0(); // returns EDX:EAX
    float *targetVec = (float *)(uint32_t)raw; // low part is pointer
    float *baseForW = (float *)((uint32_t)(raw >> 32) + 0xC); // high part + offset 0xC

    // Set w component of targetVec from baseForW
    targetVec[3] = DAT_00e44564 - *baseForW;

    // Scale all components of targetVec by scaleFactor
    targetVec[0] *= scaleFactor;
    targetVec[1] *= scaleFactor;
    targetVec[2] *= scaleFactor;
    targetVec[3] *= scaleFactor;
}