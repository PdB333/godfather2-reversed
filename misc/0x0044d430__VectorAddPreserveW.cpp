// FUNC_NAME: VectorAddPreserveW
void __fastcall VectorAddPreserveW(void* unused, const float* a, const float* b) {
    // This function adds two 4-component homogeneous vectors (a and b) and stores the result
    // in the vector pointed by the EAX register (treated as the output pointer).
    // It preserves the original w-component (index 3) of the output vector.
    float w = ((float*)unused)[3]; // Save original w from output (passed as param_1 in ECX? Actually it's in EAX)
    // Note: The decompiler shows param_1 (ECX) is unused; the actual output pointer comes from EAX.
    // To match the original signature, we reinterpret: EAX points to output, ECX is ignored.
    float a1 = a[1];
    float a2 = a[2];
    float a3 = a[3];
    float b1 = b[1];
    float b2 = b[2];
    float b3 = b[3];
    float* out = (float*)unused; // Actually it's the EAX pointer, but we use param_1 as output for this reconstruction
    // Write sum of x,y,z, then temporarily set w to sum, then restore original w.
    out[0] = a[0] + b[0];
    out[1] = a1 + b1;
    out[2] = a2 + b2;
    out[3] = a3 + b3;
    out[3] = w;  // preserve original w
}