// FUN_NAME: MathUtil::callVectorOp (wrapper around FUN_004b0d40, likely a vector operation)
// Address: 0x005fda60
// This function takes two arrays of three floats (or ints) and passes them individually to another function.
// param_1 is unused; it may be a this pointer or padding.
void FUN_005fda60(uint param_1, float* vectorA, float* vectorB) {
    // Call inner function with components of vectorB first, then vectorA
    // FUN_004b0d40 likely performs a known vector operation (e.g., dot product, cross product, linear interpolation)
    FUN_004b0d40(vectorB[0], vectorB[1], vectorB[2], vectorA[0], vectorA[1], vectorA[2]);
    return;
}