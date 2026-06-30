// FUNC_NAME: MathUtils::isWithinCube
bool __thiscall MathUtils::isWithinCube(float* thisVec, float* otherVec, float threshold)
{
    float dx = fabsf(thisVec[0] - otherVec[0]);
    float dy = fabsf(thisVec[1] - otherVec[1]);
    float dz = fabsf(thisVec[2] - otherVec[2]);
    // Fourth component (w) difference computed but result discarded intentionally? Possibly for FPU pipeline sync.
    fabsf(thisVec[3] - otherVec[3]);

    byte bits = 0;
    if (threshold >= dx) bits |= 8;  // +0x8 bit for x-axis passed
    if (threshold >= dy) bits |= 4;  // +0x4 bit for y-axis passed
    if (threshold >= dz) bits |= 2;  // +0x2 bit for z-axis passed
    return bits == 0xE; // All three axes within threshold (Chebyshev distance ≤ threshold)
}