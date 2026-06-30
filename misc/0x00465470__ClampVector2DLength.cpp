// FUNC_NAME: ClampVector2DLength
// Clamps the magnitude of a 2D vector (x, y) to a maximum length stored in global s_fMaxVectorLength.
void __fastcall ClampVector2DLength(float* pX, float* pY)
{
    float x = *pX;
    float y = *pY;
    float length = sqrtf(x * x + y * y);
    // Global maximum allowed vector length (DAT_00e2b1a4)
    if (g_fMaxVectorLength < length)
    {
        float scale = g_fMaxVectorLength / length;
        *pX = x * scale;
        *pY = y * scale;
    }
}