// FUNC_NAME: scaleVector3PreserveW
// Function address: 0x0051e290
// FastCall convention: passes destination pointer in ECX (unused?), source in EDX, scale on stack.
// Actually decompilation shows param_1 (ECX) unused, source in param_2 (EDX), scale in param_3 (stack),
// and destination pointer read from EAX register (in_EAX). Reconstructed as explicit parameters.
void __fastcall scaleVector3PreserveW(float *dest, float *src, float scale)
{
    // Scale the first three components of a 4-element vector, preserving the fourth.
    // Equivalent to: dest[0..2] *= scale, dest[3] unchanged.
    dest[0] = scale * src[0];
    dest[1] = scale * src[1];
    dest[2] = scale * src[2];
    // dest[3] is not overwritten; remains as originally stored.
}