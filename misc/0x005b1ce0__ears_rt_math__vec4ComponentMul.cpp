// FUNC_NAME: ears_rt_math::vec4ComponentMul
void vec4ComponentMul(const float* __restrict a, const float* __restrict b, float* __restrict dest)
{
    // Assert 16-byte alignment for SIMD-friendly pointers
    #ifdef LLMATH_CHECK_ALIGNMENT_16
    if (((uintptr_t)a & 0xf) != 0) {
        LLMATH_CHECK_ALIGNMENT_16("!(((uint32_t)(A)) & 15)", "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h", 0x3d5, 2, a);
    }
    if (((uintptr_t)b & 0xf) != 0) {
        LLMATH_CHECK_ALIGNMENT_16("!(((uint32_t)(B)) & 15)", "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h", 0x3d6, 2, b);
    }
    if (((uintptr_t)dest & 0xf) != 0) {
        LLMATH_CHECK_ALIGNMENT_16("!(((uint32_t)(dest)) & 15)", "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h", 0x3d7, 2, dest);
    }
    #endif

    // Component-wise multiplication of two 4-element vectors
    dest[0] = a[0] * b[0];
    dest[1] = a[1] * b[1];
    dest[2] = a[2] * b[2];
    dest[3] = a[3] * b[3];
}