// FUNC_NAME: Vector4::subtract
void __fastcall Vector4::subtract(float *thisResult, float *vecA, float *vecB)
{
    float a1, a2, a3, a4;
    float b1, b2, b3, b4;
    float savedW;

    // Load vecA components
    a1 = vecA[0]; // +0x00
    a2 = vecA[1]; // +0x04
    a3 = vecA[2]; // +0x08
    a4 = vecA[3]; // +0x0C

    // Load vecB components
    b1 = vecB[0]; // +0x00
    b2 = vecB[1]; // +0x04
    b3 = vecB[2]; // +0x08
    b4 = vecB[3]; // +0x0C

    // Preserve the W component of the result vector before overwriting
    savedW = thisResult[3]; // +0x0C

    // Compute component-wise subtraction: result = vecA - vecB
    thisResult[0] = a1 - b1; // +0x00
    thisResult[1] = a2 - b2; // +0x04
    thisResult[2] = a3 - b3; // +0x08
    thisResult[3] = a4 - b4; // +0x0C

    // Restore the original W component of the result (likely for homogeneous coordinates)
    thisResult[3] = savedW; // +0x0C
}