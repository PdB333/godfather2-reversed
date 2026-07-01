// FUNC_NAME: vec4ScaleXYZ
void __fastcall vec4ScaleXYZ(void* outPtr, const float* inVec, float scale)
{
    float* out = (float*)outPtr; // Output vector (ECX -> EAX)
    float w = out[3];            // Save original W component (+0x0C)
    out[0] = scale * inVec[0];   // Scale X (+0x00)
    out[1] = scale * inVec[1];   // Scale Y (+0x04)
    out[2] = scale * inVec[2];   // Scale Z (+0x08)
    out[3] = scale * inVec[3];   // Temporarily scale W (+0x0C)
    out[3] = w;                  // Restore original W (leave unchanged)
}