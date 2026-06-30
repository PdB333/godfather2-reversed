// FUNC_NAME: Math::scaleVector3D
void __fastcall scaleVector3D(uint unused, float* src, float scale)
{
    // In the original code, dest is passed via ECX? Actually, the decompiler shows writing to in_EAX.
    // We reinterpret as a function that takes a destination pointer in ECX (implicit this or first param).
    // For clarity, we treat ECX as dest (float*) and src as second param, scale as third.
    float* dest = reinterpret_cast<float*>(unused); // ECX holds destination pointer
    float origW = dest[3]; // Preserve fourth component (e.g., w)
    dest[0] = src[0] * scale;
    dest[1] = src[1] * scale;
    dest[2] = src[2] * scale;
    dest[3] = origW; // Restore w unchanged
}