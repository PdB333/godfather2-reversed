// FUNC_NAME: Math::computeHorizontalDirection
void computeHorizontalDirection(const float* from, const float* to, float* directionOut)
{
    // Compute horizontal (XZ plane) difference vector
    float diffX = to[0] - from[0];
    float diffZ = to[2] - from[2];
    float diffY = 0.0f;

    // Compute squared length of the horizontal vector
    // FUN_0056afa0 is likely vec3DotProduct(diff, diff) -> length squared
    float lenSq = vec3DotProduct(&diffX, &diffX);  // result returned as float10? Decompiler uses fVar1

    // Store the raw difference vector as the initial output
    directionOut[0] = diffX;
    directionOut[1] = 0.0f;
    directionOut[2] = diffZ;

    // If squared length is zero (or negative) handle the degenerate case
    if (lenSq <= 0.0f) {
        // FUN_00425060 likely sets the vector to a safe default (e.g., zero)
        vec3SetZero(&diffX, 0);  // second param might be a flag; result stored back in diffX/diffY/diffZ?

        // The following sequence appears to extract the (now modified) diffY as the new direction
        // Note: diffY remains 0.0f throughout, so direction ends up being all zeros.
        // The FPU calls (FUN_00b99fcb, FUN_00b99e20) are stack management; we skip them.
        directionOut[0] = diffY;  // diffY is 0.0f
        directionOut[2] = diffY;
        directionOut[1] = 0.0f;
    }
}