// FUNC_NAME: computeDirectionFromTargetToReference
// Address: 0x006c0b10
// Purpose: Computes a 3D direction vector (y=0) pointing away from a given target coordinate (x, z) relative to a global reference point (DAT_00e44564).
//          The result vector is stored in outDirection[3] as (x, y, z) with y=0.
//          Uses sin/cos of an angle derived from two deltas.
// Note: DAT_00e44564 is a global float constant (likely the player's x-coordinate or some world reference).
//       param_4 is used by internal functions (likely angle range or conversion flag).

void computeDirectionFromTargetToReference(float* outDirection, float* inputX, float* inputZ, unsigned int param_4)
{
    // Compute deltas from reference point DAT to input coordinates
    float deltaX = DAT_00e44564 - *inputX;   // +0x00: target x offset from reference
    double deltaZ = (double)(DAT_00e44564 - *inputZ);  // +0x00: target z offset from reference

    // Call internal conversion/wrapping functions (possibly normalize angles or clamp)
    FUN_00b9a9fa(param_4);               // Unknown operation on the parameter
    float fDeltaZ = (float)deltaZ;       // Convert z delta to float
    double dDeltaX = (double)deltaX;     // Convert x delta to double (note: repeated conversion)
    FUN_00b9a9fa(fDeltaZ);               // Unknown operation on the z delta

    // Compute angle from the two deltas (likely atan2)
    // param_4 may specify quadrant or range
    // Fun_006c89d0 returns an angle in radians
    double angle = FUN_006c89d0((float)dDeltaX, fDeltaZ, param_4);  // atan2(deltaX, deltaZ) or similar

    // Set output direction: y = 0, x = -sin(angle), z = -cos(angle)
    // Negative signs invert the direction (pointing away from reference toward target)
    outDirection[1] = 0.0f;
    outDirection[0] = -(float)sin(angle);
    outDirection[2] = -(float)cos(angle);
}