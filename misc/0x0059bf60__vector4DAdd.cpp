// FUNC_NAME: vector4DAdd
void vector4DAdd(float *src1, float *src2, float *dest) {
    // Alignment check: src1 must be 16-byte aligned
    if (((uint32_t)src1 & 0xf) != 0) {
        char *expr = "!(((uint32_t)(src1)) & 15)";
        char *file = "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h";
        int line = 0x27a;
        int severity = 2;
        void *condition = &DAT_01128f04; // Probably an address of a debug string
        FUN_00670030(&expr, "LLMATH_CHECK_ALIGNMENT_16: Pointer %08x should be aligned 16\n", src1);
    }
    // Alignment check: src2 must be 16-byte aligned
    if (((uint32_t)src2 & 0xf) != 0) {
        char *expr = "!(((uint32_t)(src2)) & 15)";
        char *file = "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h";
        int line = 0x27b;
        int severity = 2;
        void *condition = &DAT_01128f05;
        FUN_00670030(&expr, "LLMATH_CHECK_ALIGNMENT_16: Pointer %08x should be aligned 16\n", src2);
    }
    // Alignment check: dest must be 16-byte aligned
    if (((uint32_t)dest & 0xf) != 0) {
        char *expr = "!(((uint32_t)(dest)) & 15)";
        char *file = "c:\\packages001_pc\\ears_rt_math\\dev\\include\\ears_rt_math\\win/llmathsse.h";
        int line = 0x27c;
        int severity = 2;
        void *condition = &DAT_01128f06;
        FUN_00670030(&expr, "LLMATH_CHECK_ALIGNMENT_16: Pointer %08x should be aligned 16\n", dest);
    }

    // Perform 4D vector addition (x, y, z, w)
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