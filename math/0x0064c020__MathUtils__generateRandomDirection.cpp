// FUNC_NAME: MathUtils::generateRandomDirection
// Address: 0x0064c020
// Generates a random 3D direction vector using two random numbers and trigonometric functions.
// param_1: bit count for random number range (e.g., spread factor)
// Output is written to three floats pointed to by EDI (caller-set register).

void generateRandomDirection(byte param_1) {
    // Generate first random integer and scale to [0,1] * constant
    int randomInt1 = randomInt(); // FUN_0064be80
    float fVar2 = ((float)randomInt1 / (float)((1 << (param_1 & 0x1f)) - 1)) * DAT_00e2afac;

    // Generate second random integer and scale to [0,1] * constant
    int randomInt2 = randomInt(); // FUN_0064be80
    float fVar3 = ((float)randomInt2 / (float)((1 << ((param_1 - 1) & 0x1f)) - 1)) * DAT_00e2a850;

    // Trigonometric transformations (likely sin/cos)
    double dVar4 = (double)fVar3;
    sin(dVar4); // FUN_00b99e20 — result used implicitly? Exact semantics unknown.
    double dVar5 = (double)fVar2;
    cos(dVar5); // FUN_00b99fcb — assumed order.

    // Build output vector: x = fVar2 * fVar3 (cos*sin?), y = same, z = fVar3
    // Due to unclear FPU stack usage, this is a best-effort reconstruction.
    *unaff_EDI = (float)dVar5 * (float)dVar4; // x = fVar2 * fVar3
    dVar5 = (double)fVar2;
    sin(dVar5); // FUN_00b99e20 repeated
    unaff_EDI[1] = (float)dVar5 * (float)dVar4; // y = fVar2 * fVar3
    dVar4 = (double)fVar3;
    cos(dVar4); // FUN_00b99fcb
    unaff_EDI[2] = (float)dVar4; // z = fVar3
}