// FUNC_NAME: Vector2D::applyAngularOffset
void Vector2D::applyAngularOffset(float angle, float *outX, float *outY)
{
    float sinComp;
    float cosComp; // local_8 is sin, param_1 (angle) is reused as cos after call

    // Compute sine and cosine of the given angle
    // FUN_0056d810: likely sin-cos table lookup or SSE intrinsic
    sinCosComputation(angle, &sinComp, &cosComp, nullptr);

    // Global offsets for coordinate system (likely adjusted for camera tilt or world orientation)
    float cosOffset = gCosAngleBias - cosComp; // DAT_00e44564

    // Perform difference from input vector (outX, outY are read initially)
    float diffX = *outX - cosOffset;
    float diffY = *outY - sinComp;

    // Normalize or scale by world unit factor
    // FUN_0056aee0: likely float division by a constant (e.g., convert to game units)
    *outX = (float)scaleFloat(diffX, gWorldUnitScale); // DAT_00d5d70c
    *outY = (float)scaleFloat(diffY, gWorldUnitScale);
}