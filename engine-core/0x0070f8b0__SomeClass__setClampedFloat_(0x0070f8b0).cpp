// FUNC_NAME: SomeClass::setClampedFloat (0x0070f8b0)
void __thiscall setClampedFloat(int this, float value) {
    // Clamp the input value to the range [0.0, g_fClampMaximum].
    // Global g_fClampMaximum is defined elsewhere (DAT_00d5e288).
    if (g_fClampMaximum < value) {
        *(float *)(this + 0x4c) = g_fClampMaximum;  // +0x4c: clamped float field
    } else {
        *(float *)(this + 0x4c) = (value >= 0.0f) ? value : 0.0f;
    }
}