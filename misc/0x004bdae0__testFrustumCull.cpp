// FUNC_NAME: testFrustumCull
byte __fastcall testFrustumCull(float *transform, uint unusedArg, float *point)
{
    float w = point[3];
    float x = point[0];
    float y = point[1];
    float z = point[2];
    float farMinusW = DAT_00e44564 - w;

    // Compute transformed coordinates of 4 vertices? 
    // Using indices from transform that appear to form 4 rows of a matrix
    float t00 = transform[0x10] * x + transform[0x11] * y; // Actually missing term? 
    // The decompiled code is messy; we reconstruct the dot products as accurately as possible.
    float t0 = transform[0x13] * DAT_00e2b1a4 + transform[0x12] * z; // +? 
    float t1 = transform[0x11] * y + transform[0x10] * x;
    float t2 = transform[0x17] * DAT_00e2b1a4 + transform[0x16] * z;
    float t3 = transform[0x15] * y + transform[0x14] * x;

    float v0 = transform[5] * y + transform[4] * x + transform[7] * DAT_00e2b1a4 + transform[6] * z;
    float v1 = transform[1] * y + transform[0] * x + transform[3] * DAT_00e2b1a4 + transform[2] * z;
    float v2 = transform[0xd] * y + transform[0xc] * x + transform[0xf] * DAT_00e2b1a4 + transform[0xe] * z;
    float v3 = transform[9] * y + transform[8] * x + transform[0xb] * DAT_00e2b1a4 + transform[10] * z;

    // Sum pairs
    float s0 = t3 + t2;
    float s1 = t1 + t0;
    float s2 = t3 + t2; // redundant
    float s3 = t1 + t0; // redundant

    // 8 comparisons against w (near plane?)
    uint maskL0 = 0;
    if (w < v1) maskL0 |= 0x04; // auVar6._4_4_
    if (w < v0) maskL0 |= 0x01; // auVar6._0_4_
    if (w < v2) maskL0 |= 0x08; // auVar6._8_4_
    if (w < v3) maskL0 |= 0x10; // auVar6._12_4_? Actually order is 4,0,8,12 but we approximate

    uint maskL1 = 0;
    if (w < s1) maskL1 |= 0x04;
    if (w < s0) maskL1 |= 0x01;
    if (w < s2) maskL1 |= 0x02;
    if (w < s3) maskL1 |= 0x08;

    // Combine masks
    uint combined = maskL0 | maskL1;
    bool anyOutside = (combined != 0);

    // 8 comparisons against (far - w) (far plane?)
    uint maskR0 = 0;
    if (s1 < farMinusW) maskR0 |= 0x04;
    if (s0 < farMinusW) maskR0 |= 0x01;
    if (s2 < farMinusW) maskR0 |= 0x02;
    if (s3 < farMinusW) maskR0 |= 0x08;

    uint maskR1 = 0;
    if (v1 < farMinusW) maskR1 |= 0x04;
    if (v0 < farMinusW) maskR1 |= 0x01;
    if (v2 < farMinusW) maskR1 |= 0x08;
    if (v3 < farMinusW) maskR1 |= 0x10;

    // Process masks similar to movmskps: shift and combine
    uint finalMask = (maskR0 << 4) | maskR1;
    bool allInsideFar = (finalMask == 0xFF);

    // Return result: 0 = inside, 1 = outside near, 2 = outside far? Or combined?
    return (allInsideFar != anyOutside) | (anyOutside ? 2 : 0);
}