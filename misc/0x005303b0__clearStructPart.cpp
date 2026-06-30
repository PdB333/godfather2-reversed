// FUNC_NAME: clearStructPart
void clearStructPart(float* pData)
{
    // Zero out first 6 floats (indices 0-5) by multiplying by 0.0 (compiler idiom)
    pData[0] = pData[0] * 0.0f;
    pData[1] = pData[1] * 0.0f;
    pData[2] = pData[2] * 0.0f;
    pData[3] = pData[3] * 0.0f;
    pData[4] = pData[4] * 0.0f;
    pData[5] = pData[5] * 0.0f;
    // Zero out the 9th float (index 8)
    pData[8] = 0.0f;
    // Indices 6 and 7 are left unchanged
}