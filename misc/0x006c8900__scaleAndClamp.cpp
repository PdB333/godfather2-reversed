// FUNC_NAME: scaleAndClamp
// Function at 0x006c8900: Scales a factor by a ratio of a value to a global maximum, then clamps to a global cap.
// Used for damage/stat scaling where the input value is normalized before multiplication.
// Globals: g_maxStatValue (0x0112a7a8), g_maxClampValue (0x00d5780c)

float scaleAndClamp(float value, float factor)
{
    // Normalize factor: factor * (value / g_maxStatValue)
    float scaled = (value / g_maxStatValue) * factor;
    
    // Clamp to maximum allowed value
    if (g_maxClampValue < scaled) {
        return g_maxClampValue;
    }
    return scaled;
}