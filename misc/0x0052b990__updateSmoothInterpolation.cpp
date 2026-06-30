// FUNC_NAME: updateSmoothInterpolation
/* Address: 0x0052b990
 * Role: Applies a scaling factor to interpolation target values, calls a smoothing function,
 *       then resets timer and state variables. Likely part of a camera or object smoothing system.
 * Global state: g_smoothFactor, g_duration, g_elapsed, g_defaultValue, g_target[4], g_flags.
 */

void updateSmoothInterpolation(void)
{
    float scale;

    if ((g_smoothFactor != 0.0f) && (0.0f < g_duration) && (g_elapsed != 0.0f)) {
        scale = g_defaultValue / g_smoothFactor;
        g_targetX = scale * g_targetX;
        g_targetY = scale * g_targetY;
        g_targetZ = scale * g_targetZ;
        g_targetW = scale * g_targetW;

        // Call smoothing update function with pointer to target vector, duration, elapsed, and flags
        FUN_0052cbd0(&g_targetX, g_duration, g_elapsed,
                     g_flags & 1,                         // bit 0 of flags
                     (g_flags >> 1) & 0xffffff01,         // shifted flags, masked (possibly a bitfield issue)
                     0, 0, 0);                            // additional unused parameters

        // Clear the two lowest bits of flags (signal completion)
        g_flags = g_flags & 0xfffffffc;

        // Reset timing
        g_duration = 0.0f;
        g_elapsed = 0.0f;

        // Reset target vector to default values
        g_targetX = g_defaultValue;
        g_targetY = g_defaultValue;
        g_targetZ = g_defaultValue;
        g_targetW = 0.0f;  // fourth component resets to 0, not default

        // Clear smooth factor
        g_smoothFactor = 0.0f;
    }
    return;
}