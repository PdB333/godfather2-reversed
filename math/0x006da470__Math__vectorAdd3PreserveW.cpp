// FUNC_NAME: Math::vectorAdd3PreserveW
void __fastcall Math::vectorAdd3PreserveW(float* pDest, const float* pSrcA, const float* pSrcB)
{
    // Preserve the W component of the destination vector (index 3)
    float fW = pDest[3];
    // Add X, Y, Z components from source vectors
    pDest[0] = pSrcA[0] + pSrcB[0];
    pDest[1] = pSrcA[1] + pSrcB[1];
    pDest[2] = pSrcA[2] + pSrcB[2];
    // Restore the original W component (unchanged)
    pDest[3] = fW;
}