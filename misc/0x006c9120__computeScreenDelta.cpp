//FUNC_NAME: computeScreenDelta
// Address: 0x006c9120
// Role: Computes a 2D vector from pointA to pointB, with y-axis inverted and offset by a global constant.
// Likely converts world-space delta to screen-space delta (y inverted, x unchanged, z=0).
// The two calls to someMathFunc() are unknown; possibly debug or inlined math operations.

void computeScreenDelta(float* outVec, float* pointA, float* pointB)
{
    float dx = *pointB - *pointA;                     // pointB.x - pointA.x
    float dy = pointB[1] - pointA[1];                 // pointB.y - pointA.y

    someMathFunc();                                   // unknown function call (no args)
    outVec[0] = DAT_00e44564 - dy;                    // x = globalConstant - dy
    someMathFunc();                                   // unknown function call (no args)
    outVec[1] = dx;                                   // y = dx
    outVec[2] = 0.0f;                                 // z = 0
}