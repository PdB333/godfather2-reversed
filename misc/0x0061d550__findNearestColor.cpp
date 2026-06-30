// FUNC_NAME: findNearestColor
uint findNearestColor(uint colorA, uint colorB, uint colorC, uint colorD, uint targetColor)
{
    // Extract three 8-bit components from each color (likely B, G, R order or R, G, B)
    // Note: bits 16-23 are comp2 (maybe red), bits 8-15 are comp1 (green), bits 0-7 are comp0 (blue)
    uint comp2_C = (colorC >> 16) & 0xFF;
    uint comp1_C = (colorC >> 8) & 0xFF;
    uint comp0_C = colorC & 0xFF;

    uint comp2_T = (targetColor >> 16) & 0xFF;
    uint comp1_T = (targetColor >> 8) & 0xFF;
    uint comp0_T = targetColor & 0xFF;

    // Manhattan distance between colorC and targetColor
    int diff0 = (int)(comp0_C - comp0_T);
    int sign0 = diff0 >> 31;
    int adiff0 = (sign0 ^ diff0) - sign0; // or the expression used: ((sign0 - comp0_T) + comp0_C ^ sign0)

    int diff1 = (int)(comp1_C - comp1_T);
    int sign1 = diff1 >> 31;
    int adiff1 = (sign1 ^ diff1) - sign1;

    int diff2 = (int)(comp2_C - comp2_T);
    int sign2 = diff2 >> 31;
    int adiff2 = (sign2 ^ diff2) - sign2;

    uint distC = adiff0 + adiff1 + adiff2;  // total absolute difference

    // Distance between colorA and targetColor
    uint comp2_A = (colorA >> 16) & 0xFF;
    uint comp1_A = (colorA >> 8) & 0xFF;
    uint comp0_A = colorA & 0xFF;

    diff0 = (int)(comp0_A - comp0_T);
    sign0 = diff0 >> 31;
    uint adiff0_A = ((sign0 - (int)comp0_T) + (int)comp0_A) ^ (uint)sign0;

    diff1 = (int)(comp1_A - comp1_T);
    sign1 = diff1 >> 31;
    uint adiff1_A = ((sign1 - (int)comp1_T) + (int)comp1_A) ^ (uint)sign1;

    diff2 = (int)(comp2_A - comp2_T);
    sign2 = diff2 >> 31;
    uint adiff2_A = ((sign2 - (int)comp2_T) + (int)comp2_A) ^ (uint)sign2;

    uint distA = adiff0_A + adiff1_A + adiff2_A;

    if (distC < distA)
    {
        // colorC is closer to target than colorA
        // Now compare colorC with colorD
        uint comp2_D = (colorD >> 16) & 0xFF;
        uint comp1_D = (colorD >> 8) & 0xFF;
        uint comp0_D = colorD & 0xFF;

        diff0 = (int)(comp0_D - comp0_T);
        sign0 = diff0 >> 31;
        uint adiff0_D = ((sign0 - (int)comp0_T) + (int)comp0_D) ^ (uint)sign0;

        diff1 = (int)(comp1_D - comp1_T);
        sign1 = diff1 >> 31;
        uint adiff1_D = ((sign1 - (int)comp1_T) + (int)comp1_D) ^ (uint)sign1;

        diff2 = (int)(comp2_D - comp2_T);
        sign2 = diff2 >> 31;
        uint adiff2_D = ((sign2 - (int)comp2_T) + (int)comp2_D) ^ (uint)sign2;

        uint distD = adiff0_D + adiff1_D + adiff2_D;

        if (distC < distD)
        {
            // colorC is the best among A, D (C not compared to B yet)
            // Return encoded result: low byte 2 indicates index for colorC?
            // High 24 bits come from component difference between D and target (adiff2_D)
            return (adiff2_D << 8) | 2;
        }

        // colorD is closer than colorC, compare colorD with colorB
        uint comp2_B = (colorB >> 16) & 0xFF;
        uint comp1_B = (colorB >> 8) & 0xFF;
        uint comp0_B = colorB & 0xFF;

        diff0 = (int)(comp0_B - comp0_T);
        sign0 = diff0 >> 31;
        uint adiff0_B = ((sign0 - (int)comp0_T) + (int)comp0_B) ^ (uint)sign0;

        diff1 = (int)(comp1_B - comp1_T);
        sign1 = diff1 >> 31;
        uint adiff1_B = ((sign1 - (int)comp1_T) + (int)comp1_B) ^ (uint)sign1;

        diff2 = (int)(comp2_B - comp2_T);
        sign2 = diff2 >> 31;
        uint adiff2_B = ((sign2 - (int)comp2_T) + (int)comp2_B) ^ (uint)sign2;

        uint distB = adiff0_B + adiff1_B + adiff2_B;

        if (distD < distB)
        {
            // colorD is best; return low byte 3 (index for D)
            return (distB << 8) | 3;   // Note: high 24 bits come from distB (full distance of B)
        }
        else
        {
            // colorB is best; return low byte 1 (index for B)
            return (distB << 8) | 1;
        }
    }
    else
    {
        // colorA is closer than colorC; return distance of C with low byte masked
        // This likely indicates that colorA is the default choice, but function returns C's distance?
        return distC & 0xFFFFFF00;
    }
}