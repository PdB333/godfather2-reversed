// FUNC_NAME: MathUtils::computeHorizontalDirection
void __cdecl computeHorizontalDirection(float* outDir, const float* from, const float* to)
{
    // Compute horizontal difference (X and Z only, Y ignored)
    float dx = to[0] - from[0];
    float dz = to[2] - from[2];
    float dy = 0.0f; // Unused Y component, always zero

    // Compute squared length of the horizontal vector
    // FUN_0056afa0 likely computes dot product of (dx, 0, dz) with itself
    float squaredLen = /* FUN_0056afa0(&dx, &dx) */; // Placeholder: actually called with &local_20

    if (squaredLen <= 0.0f)
    {
        // Zero-length vector: set result to (0,0,0)
        // FUN_00425060 zeroes the vector
        // FUN_00b99fcb and FUN_00b99e20 are floating-point control ops (rounding mode)
        outDir[0] = 0.0f;
        outDir[1] = 0.0f;
        outDir[2] = 0.0f;
    }
    else
    {
        // Positive length: return the horizontal direction (not normalized)
        outDir[0] = dx;
        outDir[1] = 0.0f;
        outDir[2] = dz;
    }
}