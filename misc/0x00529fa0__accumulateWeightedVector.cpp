// FUNC_NAME: accumulateWeightedVector
void accumulateWeightedVector(float* inputVec)
{
    // Global vector (4 components) and a scalar weight factor
    // Weight factor is stored at 0x00e2b1a4
    extern float gGlobalWeight; // DAT_00e2b1a4
    extern float gGlobalVector[4]; // DAT_01125230, 01125234, 01125238, 0112523c

    // Add scaled input to global vector: gGlobalVector += weight * inputVec
    gGlobalVector[0] += gGlobalWeight * inputVec[0];
    gGlobalVector[1] += gGlobalWeight * inputVec[1];
    gGlobalVector[2] += gGlobalWeight * inputVec[2];
    gGlobalVector[3] += gGlobalWeight * inputVec[3];
}