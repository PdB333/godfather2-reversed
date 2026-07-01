// FUNC_NAME: Vector3::computeNormalizedDirection (global utility)
// Address: 0x00851c60
// Computes the normalized direction vector from pointB to pointA (if param_1 is false) or from pointA to pointB (if param_1 is true).
// Stores result in outDirection. Assumes outDirection points to a 3-float array.

void normalizedDirection(bool swap, const float* pointA, const float* pointB, float* outDirection)
{
    const float* from;
    const float* to;

    if (swap) {
        from = pointB;
        to = pointA;
    } else {
        from = pointA;
        to = pointB;
    }

    outDirection[0] = from[0] - to[0];
    outDirection[1] = from[1] - to[1];
    outDirection[2] = from[2] - to[2];

    // Call vector normalization function (FUN_0056afa0)
    vectorNormalize(outDirection);
}