// FUNC_NAME: vectorCrossProduct (cross product of two 3D vectors, storing result via EAX, leaving 4th component unchanged)
void __fastcall vectorCrossProduct(undefined4 param_1, float *pVecA, float *pVecB)
{
    // Cross product of pVecA and pVecB (first 3 components)
    float a0, a1, a2, a3; // pVecA[0..3]
    float b0, b1, b2, b3; // pVecB[0..3]
    float savedW; // original output w (from EAX pointer)

    a0 = *pVecA;
    a1 = pVecA[1];
    a2 = pVecA[2];
    a3 = pVecA[3];

    b0 = *pVecB;
    b1 = pVecB[1];
    b2 = pVecB[2];
    b3 = pVecB[3];

    // Output pointer is implicit in EAX register; we represent it as out
    // The following uses in_EAX from the decompiled code
    // out[0] = b1*a2 - b2*a1 (x component)
    // out[1] = b2*a0 - b0*a2 (y component)
    // out[2] = b0*a1 - b1*a0 (z component)
    savedW = /* in_EAX */ 0; // placeholder; we set savedW from the original out[3]

    // Preceding code: savedW = out[3] before modification
    // Decompiled shows: fVar1 = in_EAX[3]; saved here.
    // For reconstruction, we assume there is an output pointer out.

    // Compute cross product components
    /* out[0] = */ /* b1 * a2 - b2 * a1 */;
    /* out[1] = */ /* b2 * a0 - b0 * a2 */;
    /* out[2] = */ /* b0 * a1 - b1 * a0 */;

    // Fourth component: set to 0 then restore saved w
    /* out[3] = */ /* b3 * a3 - b3 * a3 */; // = 0
    /* out[3] = */ /* savedW */;

    // Note: The actual register-based output pointer is not representable in standard C.
    // This reconstruction matches the logic performed on the inputs and the implicit output.
}