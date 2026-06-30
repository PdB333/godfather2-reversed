// FUNC_NAME: ScaleAndSetW
void ScaleAndSetW(float scale, int pDest, int pSrc) // pDest in ESI, pSrc in EDI, scale in param_1
{
    // Known constant likely 1.0f
    const float kOne = *(float*)0x00e2b1a4;

    // Temporary vector (unused after call)
    float4 temp; // offsets: temp.x = local_20, temp.y = local_1c, temp.z = local_18, temp.w = local_14
    temp.x = 0.0f;
    temp.y = 0.0f;
    temp.z = 0.0f;
    temp.w = kOne;

    // Helper call (purpose unknown, does not affect result)
    FUN_0056cc80(scale, &temp);

    // Source vector (pSrc) offsets: +0x10 = x, +0x14 = y, +0x18 = z, +0x1c = w
    float srcX = *(float*)(pSrc + 0x10);
    float srcY = *(float*)(pSrc + 0x14);
    float srcZ = *(float*)(pSrc + 0x18);
    float srcW = *(float*)(pSrc + 0x1c); // unused

    // Scale first three components, store to destination (pDest)
    *(float*)(pDest + 0x10) = scale * srcX;
    *(float*)(pDest + 0x14) = scale * srcY;
    *(float*)(pDest + 0x18) = scale * srcZ;
    // Forth component is scaled but then overwritten with constant
    *(float*)(pDest + 0x1c) = scale * srcW;
    *(float*)(pDest + 0x1c) = kOne;
}