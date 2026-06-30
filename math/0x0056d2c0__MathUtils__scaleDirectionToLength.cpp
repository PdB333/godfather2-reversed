// FUNC_NAME: MathUtils::scaleDirectionToLength
// Address: 0x0056d2c0
// Role: Scales a direction vector (x,y,z) to have length equal to a scaled scalar value, preserving the scalar in the 4th component.
void __cdecl MathUtils::scaleDirectionToLength(float dirX, float dirY, float dirZ, float scalar, float out[4])
{
    // External constant, likely a conversion factor (e.g., degrees to radians)
    // Address: 0x00e2cd54
    const float kAngleScale = *(float*)0x00e2cd54;

    // Initialize output with raw direction
    out[0] = dirX;
    out[1] = dirY;
    out[2] = dirZ;

    // Apply scale factor to the scalar (e.g., convert angle to radians)
    float scaledScalar = scalar * kAngleScale;

    // Call to unknown math routine (possibly sin setup for later use)
    FUN_00b99e20();

    // Set 4th component to scaled scalar
    out[3] = scaledScalar;

    // Save the 4th component before potential overwrite
    float savedW = out[3];

    // Call to another unknown math routine (possibly cos setup)
    FUN_00b99fcb();

    // Compute normalization factor: (scaledScalar) / length of direction
    float length = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
    float normFactor = scaledScalar / length;

    // Scale the direction components to have magnitude = scaledScalar
    out[0] = dirX * normFactor;
    out[1] = dirY * normFactor;
    out[2] = dirZ * normFactor;

    // Restore the 4th component (the original scaled scalar, not affected by normalization)
    out[3] = savedW;
}