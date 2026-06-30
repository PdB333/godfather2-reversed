// FUNC_NAME: Component::setClampedFloat
// Address: 0x004706f0
// Sets a float field at this+0x150, clamped to [0, g_fMaxClampValue].
// If the value changes, sets a dirty flag at this+0x15e (bit 0x100).
// g_fMaxClampValue is a global variable at 0x00e2b1a4.
void __thiscall Component::setClampedFloat(float value)
{
    float fClamped;

    // Default clamp to 0
    fClamped = 0.0f;

    // Clamp value to range [0, g_fMaxClampValue]
    if (value < 0.0f || value > g_fMaxClampValue)
    {
        // If value is negative, clamp to 0; if above max, clamp to max
        value = (value < 0.0f) ? 0.0f : g_fMaxClampValue;
    }

    // Update field if changed and mark dirty
    if (*(float *)(this + 0x150) != value)
    {
        *(float *)(this + 0x150) = value;
        *(unsigned short *)(this + 0x15e) |= 0x100;    // set dirty flag (bit 8)
    }
}