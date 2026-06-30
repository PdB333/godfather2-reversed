// FUNC_NAME: addVector3PreserveW
// Function at 0x0051e2c0: component-wise addition of two 4-float vectors,
// but only the x,y,z components are added; the w component of the destination is preserved.
// Parameters: pVecA and pVecB point to source vectors (4 floats each, x,y,z,w order),
// pResult (passed in EAX as implicit parameter) points to destination vector.
// The function returns void, but modifies the destination.

void __fastcall addVector3PreserveW(float* pResult, const float* pVecA, const float* pVecB)
{
    // Save original w component of result
    float originalW = pResult[3];

    // Add x, y, z components (indices 0,1,2)
    pResult[0] = pVecA[0] + pVecB[0];
    pResult[1] = pVecA[1] + pVecB[1];
    pResult[2] = pVecA[2] + pVecB[2];

    // Restore original w component – not summed
    pResult[3] = originalW;
}