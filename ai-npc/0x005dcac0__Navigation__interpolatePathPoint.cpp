// FUNC_NAME: Navigation::interpolatePathPoint
// Address: 0x005dcac0
// Role: Performs linear interpolation between two path control points (2D) based on interpolation factor.
// Uses two control points retrieved from internal data: point A (index 0) and point B (via global identifier).
// The interpolation is performed only if a validity check (isPathValid) passes.
// Outputs the interpolated (x, y) coordinates via output pointers.

bool __thiscall Navigation::interpolatePathPoint(float aX, float *outX, float *outY, float t)
{
    bool isValid;
    float bX, aY, bY; // The decompiler showed bX, aY, bY as locals.
    // bX corresponds to local_c, aY to local_8, bY to local_4.

    isValid = this->isPathValid(); // FUN_005dc670(this)
    if (isValid) {
        // Get control point A (index 0) – note: overwrites aX with the retrieved A.x? Actually the call uses &aX,
        // meaning it writes the return value into aX on the stack. aX is both input (original A.x) and becomes output.
        // This is unusual, but we preserve the decompiled logic.
        getControlPoint(0, &aX); // FUN_005dd8a0(0, &param_1)
        // Get control point B (index stored in global 0x012056c0) – writes into (bX, aY?) Actually the function
        // call writes to &bX, but due to stack layout it likely also sets aY and bY (three floats) – here we
        // assume it fills bX, aY, bY sequentially. In the original, only bX is explicitly set; the others are
        // side effects from the function writing multiple floats.
        getControlPoint(DAT_012056c0, &bX); // FUN_005dd8a0(DAT_012056c0, &local_c)

        // Interpolation factor: fVar2 = 1.0 - t (global constant DAT_00e2b1a4 is 1.0f)
        float oneMinusT = 1.0f - t; // fVar2

        // Interpolate X: (1-t)*A.x + t*B.x
        *outX = oneMinusT * aX + bX * t;

        // Interpolate Y: (1-t)*A.y + t*B.y
        // A.y is stored in aY (local_8), B.y in bY (local_4) – both set by the second getControlPoint call.
        *outY = oneMinusT * aY + bY * t;
    }
    return isValid;
}