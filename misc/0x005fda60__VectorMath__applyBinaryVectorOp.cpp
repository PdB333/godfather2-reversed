// FUNC_NAME: VectorMath::applyBinaryVectorOp
void VectorMath::applyBinaryVectorOp(void* thisOrUnused, float* vecA, float* vecB) {
    // Wrapper that extracts two 3D vectors from pointer params and calls a binary operation (FUN_004b0d40)
    // The called function likely computes something like dot/cross/distance between the two vectors.
    // param_3 points to vecB, param_2 points to vecA; components passed individually.
    // The 'this' pointer (param_1) appears unused.
    FUN_004b0d40(vecB[0], vecB[1], vecB[2], vecA[0], vecA[1], vecA[2]);
}