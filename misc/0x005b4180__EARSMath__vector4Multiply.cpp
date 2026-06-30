// FUNC_NAME: EARSMath::vector4Multiply
void EARSMath::vector4Multiply(float *a, float *b, float *dest)
{
    // Alignment check for SSE operations
    if (((uint32_t)a & 0xf) != 0) {
        LLMATH_CHECK_ALIGNMENT_16("!(((uint32_t)(A)) & 15)", "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h", 0x3d5, 2, &DAT_01129026, "LLMATH_CHECK_ALIGNMENT_16: Pointer %08x should be aligned 16\n", a);
    }
    if (((uint32_t)b & 0xf) != 0) {
        LLMATH_CHECK_ALIGNMENT_16("!(((uint32_t)(B)) & 15)", "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h", 0x3d6, 2, &DAT_01129027, "LLMATH_CHECK_ALIGNMENT_16: Pointer %08x should be aligned 16\n", b);
    }
    if (((uint32_t)dest & 0xf) != 0) {
        LLMATH_CHECK_ALIGNMENT_16("!(((uint32_t)(dest)) & 15)", "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h", 0x3d7, 2, &DAT_01129028, "LLMATH_CHECK_ALIGNMENT_16: Pointer %08x should be aligned 16\n", dest);
    }

    // Component-wise multiplication of two 4-element vectors
    float a1 = a[1];
    float a2 = a[2];
    float a3 = a[3];
    float b1 = b[1];
    float b2 = b[2];
    float b3 = b[3];

    dest[0] = a[0] * b[0];
    dest[1] = a1 * b1;
    dest[2] = a2 * b2;
    dest[3] = a3 * b3;
}