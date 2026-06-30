// FUNC_NAME: CameraSmoother::smoothTransform
void CameraSmoother::smoothTransform()
{
    float alpha;
    float beta;
    
    // Global smoothing factors: g_smoothAlpha (DAT_00e2b1a4) and g_smoothAccum (DAT_01206720)
    // Compute interpolation weight: alpha = g_smoothAlpha / (g_smoothAccum + g_smoothAlpha)
    // beta = g_smoothAlpha - alpha (likely intended to be 1.0 - alpha, but decompiler shows subtraction from global)
    alpha = g_smoothAlpha / (g_smoothAccum + g_smoothAlpha);
    beta = g_smoothAlpha - alpha;
    
    // Smooth position (offsets +0x20, +0x24, +0x28)
    g_smoothPosX = *(float *)(this + 0x20) * alpha + beta * g_smoothPosX;
    g_smoothPosY = *(float *)(this + 0x24) * alpha + beta * g_smoothPosY;
    g_smoothPosZ = *(float *)(this + 0x28) * alpha + beta * g_smoothPosZ;
    
    // Smooth rotation (quaternion at offsets +0x10, +0x14, +0x18, +0x1c)
    g_smoothRotW = (*(float *)(this + 0x10) - g_smoothRotW) * alpha + g_smoothRotW;
    g_smoothRotX = (*(float *)(this + 0x14) - g_smoothRotX) * alpha + g_smoothRotX;
    g_smoothRotY = (*(float *)(this + 0x18) - g_smoothRotY) * alpha + g_smoothRotY;
    g_smoothRotZ = (*(float *)(this + 0x1c) - g_smoothRotZ) * alpha + g_smoothRotZ;
    
    // Accumulate frame count or time
    g_smoothAccum += g_smoothAlpha;
}