// FUNC_NAME: scaleVector3PreserveW
void __fastcall scaleVector3PreserveW(float *out, const float *in, float scale)
{
    // Scale only XYZ components of a 4D vector, preserving the original W component.
    // "out" is passed in EAX, "in" in EDX, "scale" on stack (ECX unused).
    float w = out[3];
    out[0] = in[0] * scale;
    out[1] = in[1] * scale;
    out[2] = in[2] * scale;
    out[3] = w; // Restore original W
}