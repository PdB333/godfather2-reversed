// FUNC_NAME: Math::generateRandomPair
// Address: 0x006024e0
// Role: Generates two random integer values and packs them into a single uint.
// The low 12 bits come from a scaled random float, the high 20 bits from another.
// Uses global constants for scaling and thresholds; relies on external random function and utility functions.

static uint Math::generateRandomPair() {
    // Global constants (addresses from data section)
    // DAT_00e2b1a4 : likely min threshold
    // DAT_00e2eff4 : likely max threshold
    // DAT_00e4466c : first scale factor
    // DAT_00e2cd54 : rounding bias (0.5)
    // DAT_00e44668 : second scale factor
    // DAT_00e2a848 : offset for inversion condition

    float local_1c = DAT_00e2b1a4;
    double local_18 = (double)DAT_00e2eff4; // reinterpreted as double due to CONCAT44
    float fVar4 = (float)FUN_00b9a660(); // probably returns random float in [0,1)
    local_10[0] = 0.0f;

    // First scaled random integer
    long long lVar1 = (long long)(fVar4 * (float)DAT_00e4466c + (float)DAT_00e2cd54);
    float fVar2 = (float)lVar1;

    if ((fVar2 != 0.0f) && (fVar2 != 5.73832e-42f)) { // skip special values
        unsigned int highPart = (unsigned int)((unsigned long long)lVar1 >> 32);
        double initialDouble;
        initialDouble = CONCAT44(highPart, DAT_00e2b1a4); // reconstruct double from two parts
        local_1c = DAT_00e2eff4;
        double dVar5 = (double)fVar4;

        local_10[0] = fVar4; // store random float
        FUN_00b99fcb(); // some utility, modifies local_10? Or calculates something?
        // unaff_EDI is an implicit pointer (likely from __thiscall or hidden parameter)
        // It is used to access some array or structure.
        local_10[0] = *unaff_EDI / (float)dVar5; // divide value at address by random

        float* pfVar3;
        if (local_10[0] <= DAT_00e2b1a4) {
            if (DAT_00e2eff4 <= local_10[0]) {
                pfVar3 = local_10;
            } else {
                pfVar3 = &local_1c;
            }
        } else {
            pfVar3 = &local_18;
        }

        dVar5 = (double)*pfVar3;
        FUN_00b9b988(); // utility function
        local_1c = (float)dVar5;

        // Optional inversion: if unaff_EDI[2] is negative and non-zero, flip the value
        if (unaff_EDI[2] <= 0.0f && unaff_EDI[2] != 0.0f) {
            local_1c = DAT_00e2a848 - local_1c;
        }

        // Second scaled random integer
        local_10[0] = (float)(long long)(local_1c * (float)DAT_00e44668 + (float)DAT_00e2cd54);
    }

    // Pack: high 20 bits from the second integer, low 12 bits from the first
    return ((uint)(int)local_10[0] << 12) | (uint)fVar2;
}