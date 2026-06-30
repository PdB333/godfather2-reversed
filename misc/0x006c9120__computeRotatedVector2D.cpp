// FUNC_NAME: computeRotatedVector2D
// Address: 0x006c9120
// Computes a 2D vector transformation: takes two input vectors (or points) and produces a result vector stored in outVector.
// outVector.x = kScreenCenterY - (inB.y - inA.y)
// outVector.y = inB.x - inA.x
// outVector.z = 0.0f
// Possibly used for 90-degree rotation in screen space or a minimap transform.
// Calls unknown helper function twice (likely FPU state management or error checking).

extern const float kScreenCenterY; // DAT_00e44564 – likely Y center of screen or a constant offset

// Unknown helper function – called between computations, void and no arguments.
void unknownHelperFunction(); // FUN_00b9a9fa

void computeRotatedVector2D(float* outVector, const float* vecA, const float* vecB)
{
    float dx = vecB[0] - vecA[0];   // B.x - A.x
    float dy = vecB[1] - vecA[1];   // B.y - A.y

    unknownHelperFunction();        // first call – unknown purpose

    outVector[0] = kScreenCenterY - dy; // (constant - dy) → rotates and offsets
    unknownHelperFunction();        // second call

    outVector[1] = dx;              // original x difference becomes y in output
    outVector[2] = 0.0f;           // z component always zero
}