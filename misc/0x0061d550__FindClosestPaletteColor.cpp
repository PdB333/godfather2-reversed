// FUNC_NAME: FindClosestPaletteColor
// Address: 0x0061d550
// Purpose: Computes Manhattan color distance to target and returns an encoded best match among four candidates.
// Likely from rendering or texture palette system.

unsigned int FindClosestPaletteColor(unsigned int param1, unsigned int param2, unsigned int param3, unsigned int param4, unsigned int param5)
{
    // Extract target color (param5) components
    unsigned int rT = param5 >> 16 & 0xff;   // +0x2
    unsigned int gT = param5 >> 8 & 0xff;    // +0x1
    unsigned int bT = param5 & 0xff;         // +0x0

    // Compute Manhattan distance for param3 (colorA)
    unsigned int rA = param3 >> 16 & 0xff;
    unsigned int gA = param3 >> 8 & 0xff;
    unsigned int bA = param3 & 0xff;

    int signR_A = (int)(rA - rT) >> 31;
    int signG_A = (int)(gA - gT) >> 31;
    int signB_A = (int)(bA - bT) >> 31;
    unsigned int distA = ((signB_A - bT) + bA ^ signB_A) + ((signG_A - gT) + gA ^ signG_A) + ((signR_A - rT) + rA ^ signR_A);

    // Compute Manhattan distance for param1 (colorB)
    unsigned int rB = param1 >> 16 & 0xff;
    unsigned int gB = param1 >> 8 & 0xff;
    unsigned int bB = param1 & 0xff;

    int signR_B = (int)(rB - rT) >> 31;
    int signG_B = (int)(gB - gT) >> 31;
    int signB_B = (int)(bB - bT) >> 31;
    unsigned int distB = ((signB_B - bT) + bB ^ signB_B) + ((signG_B - gT) + gB ^ signG_B) + ((signR_B - rT) + rB ^ signR_B);

    if ((int)distA < (int)distB) {
        // param3 (colorA) is closer than param1 (colorB)
        // Now consider param4 (colorC)
        unsigned int rC = param4 >> 16 & 0xff;
        unsigned int gC = param4 >> 8 & 0xff;
        unsigned int bC = param4 & 0xff;

        int signR_C = (int)(rC - rT) >> 31;
        int signG_C = (int)(gC - gT) >> 31;
        int signB_C = (int)(bC - bT) >> 31;
        unsigned int absRC = (signR_C - rT) + rC ^ signR_C;
        unsigned int distC = ((signB_C - bT) + bC ^ signB_C) + ((signG_C - gT) + gC ^ signG_C) + absRC;

        if ((int)distA < (int)distC) {
            // param3 (colorA) is closer than param4 (colorC)
            // Now consider param2 (colorD) as final candidate
            unsigned int rD = param2 >> 16 & 0xff;
            unsigned int gD = param2 >> 8 & 0xff;
            unsigned int bD = param2 & 0xff;

            int signR_D = (int)(rD - rT) >> 31;
            int signG_D = (int)(gD - gT) >> 31;
            int signB_D = (int)(bD - bT) >> 31;
            unsigned int distD = ((signB_D - bT) + bD ^ signB_D) + ((signG_D - gT) + gD ^ signG_D) + ((signR_D - rT) + rD ^ signR_D);

            // Encode distD into upper 24 bits, lower byte identifies result
            unsigned int encoded = ((distD >> 8) & 0xFFFFFF) | 0x1;  // lower byte 1 (param2)
            if ((int)distC < (int)distD) {
                // param4 (colorC) is closer than param2 (colorD)
                return ((distD >> 8) & 0xFFFFFF) | 0x3;  // lower byte 3
            }
            return encoded;  // lower byte 1
        }
        else {
            // distA >= distC: param4 (colorC) is closer than param3 (colorA)
            // Return with lower byte 2 encoding red component difference? (special case)
            return ((absRC >> 8) & 0xFFFFFF) | 0x2;  // lower byte 2
        }
    }
    else {
        // distA >= distB: param1 (colorB) is equal or closer than param3 (colorA)
        // Return distA with lower byte zeroed
        return distA & 0xFFFFFF00;
    }
}