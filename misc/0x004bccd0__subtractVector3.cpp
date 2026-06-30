// FUNC_NAME: subtractVector3
// Function at 0x004bccd0: Vector subtraction (preserves w component)
// __fastcall: destination pointer in EAX (first argument), source A in param_2, source B in param_3
void __fastcall subtractVector3(float* outVec, float* inVecA, float* inVecB)
{
    float tempW; // saved original w of destination

    // Load components from source B (param_3)
    float b1 = inVecB[1];
    float b2 = inVecB[2];
    float b3 = inVecB[3];
    // Load components from source A (param_2)
    float a1 = inVecA[1];
    float a2 = inVecA[2];
    float a3 = inVecA[3];

    // Save destination's w component before overwriting
    tempW = outVec[3];

    // Compute and store x difference
    outVec[0] = inVecA[0] - inVecB[0];
    // Compute and store y difference
    outVec[1] = a1 - b1;
    // Compute and store z difference
    outVec[2] = a2 - b2;
    // Compute w difference (but it will be overwritten with original w)
    outVec[3] = a3 - b3;
    // Restore original w, effectively leaving w unchanged
    outVec[3] = tempW;
}