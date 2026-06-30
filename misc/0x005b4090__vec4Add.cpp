// FUNC_NAME: vec4Add
void vec4Add(float *src1, float *src2, float *dest)
{
    // Alignment check for SSE operations (16-byte alignment)
    if (((uint32_t)src1 & 0xf) != 0) {
        earsAssert("!(((uint32_t)(src1)) & 15)", "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h", 0x27a);
        LLMATH_CHECK_ALIGNMENT_16("Pointer %08x should be aligned 16\n", src1);
    }
    if (((uint32_t)src2 & 0xf) != 0) {
        earsAssert("!(((uint32_t)(src2)) & 15)", "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h", 0x27b);
        LLMATH_CHECK_ALIGNMENT_16("Pointer %08x should be aligned 16\n", src2);
    }
    if (((uint32_t)dest & 0xf) != 0) {
        earsAssert("!(((uint32_t)(dest)) & 15)", "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h", 0x27c);
        LLMATH_CHECK_ALIGNMENT_16("Pointer %08x should be aligned 16\n", dest);
    }

    // Perform component-wise addition of two 4-element vectors
    float x1 = src1[0];
    float y1 = src1[1];
    float z1 = src1[2];
    float w1 = src1[3];
    float x2 = src2[0];
    float y2 = src2[1];
    float z2 = src2[2];
    float w2 = src2[3];

    dest[0] = x1 + x2;
    dest[1] = y1 + y2;
    dest[2] = z1 + z2;
    dest[3] = w1 + w2;
}