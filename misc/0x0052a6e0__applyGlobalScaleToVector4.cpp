// FUNC_NAME: applyGlobalScaleToVector4
void applyGlobalScaleToVector4(void)
{
    float ratio;

    ratio = s_scaleNumerator / s_scaleDenominator;
    s_vectorX = ratio * s_vectorX;
    s_vectorY = ratio * s_vectorY;
    s_vectorZ = ratio * s_vectorZ;
    s_vectorW = ratio * s_vectorW;
}