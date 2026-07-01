// FUNC_NAME: MathUtils::scaleAndNormalizeVector
void scaleAndNormalizeVector(char bScale, float* inVec, float* outVec) {
    // Copy input vector to output
    outVec[0] = inVec[0];
    outVec[1] = inVec[1];
    outVec[2] = inVec[2];

    // Global scale factor (address 0x00d5ccf8) — may represent time step or unit conversion
    float globalScale = *reinterpret_cast<float*>(0x00d5ccf8);

    if (bScale) {
        outVec[0] *= globalScale;
        outVec[1] *= globalScale;
        outVec[2] *= globalScale;
    }

    // Normalize the vector in-place via helper
    float tempVec[3];
    tempVec[0] = outVec[0];
    tempVec[1] = outVec[1];
    tempVec[2] = outVec[2];
    int unused = 0;

    mathNormalizeVector3(tempVec);  // FUN_0056afa0 – normalizes a 3D vector

    outVec[0] = tempVec[0];
    outVec[1] = tempVec[1];
    outVec[2] = tempVec[2];
}