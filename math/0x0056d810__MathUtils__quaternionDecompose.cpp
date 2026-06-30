// FUNC_NAME: MathUtils::quaternionDecompose
// Address: 0x0056d810
// Extracts three scalar components from a quaternion, likely for rotation matrix rows or Euler angles.
// param_1: input quaternion (4 floats: x, y, z, w)
// param_2: output float (stores m02 or similar)
// param_3: output float (stores 1.0f - clamped(m12) or similar)
// param_4: output float (stores m10 or similar)
// Note: DAT_00e2b04c likely 2.0f (factor for matrix elements)
//       DAT_00e2eff4 and DAT_00e2b1a4 likely -1.0f and 1.0f (clamp bounds)
//       DAT_00e44564 likely 1.0f (constant for subtraction)

void __cdecl quaternionDecompose(float* param_1, float* param_2, float* param_3, float* param_4)
{
    float x = param_1[0];
    float y = param_1[1];
    float z = param_1[2];
    float w = param_1[3];

    // Likely factor = 2.0f (common for extracting matrix elements from quaternion)
    float factor = DAT_00e2b04c;

    // Compute element m02 = 2 * (w*y + x*z)
    double m02 = (double)((w * y + z * x) * factor);
    FUN_00b9a9fa(); // potential no-op or FPU state set
    *param_2 = (float)m02;

    // Compute element m12 = 2 * (y*z - w*x)
    float m12_raw = (y * z - w * x) * factor;
    float clampLow = DAT_00e2eff4;  // likely -1.0f
    float clampHigh = DAT_00e2b1a4; // likely 1.0f
    if (m12_raw <= clampLow) {
        m12_raw = clampLow;
    }
    if (clampHigh <= m12_raw) {
        m12_raw = clampHigh;
    }
    double m12_clamped = (double)m12_raw;
    FUN_00b9c766(); // potential no-op
    // Output = constant - clamped value (e.g., 1.0f - m12)
    *param_3 = DAT_00e44564 - (float)m12_clamped;

    // Compute element m10 = 2 * (x*y + w*z)
    double m10 = (double)((w * z + x * y) * factor);
    FUN_00b9a9fa();
    *param_4 = (float)m10;
}