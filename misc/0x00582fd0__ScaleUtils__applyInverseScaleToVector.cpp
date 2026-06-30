// FUNC_NAME: ScaleUtils::applyInverseScaleToVector
void __fastcall applyInverseScaleToVector(ScaleObject* thisObj, int param_2, int param_3)
{
    // thisObj: scale factor source (+0x8 is a float* to [sx, sy, sz, sw])
    // param_2: destination object (+0x8 is float* to output vector)
    // param_3: source object (+0x8 is float* to input vector)

    float* pSrcScale = *(float**)((char*)thisObj + 8);  // +0x8: buffer of 4 floats
    float* pDstVec   = *(float**)(param_2 + 8);          // +0x8: output vector
    float* pSrcVec   = *(float**)(param_3 + 8);          // +0x8: input vector

    float g_globalScale = DAT_00e2b1a4;  // global scaling factor (maybe 1.0 or world scale)

    float invScaleY = g_globalScale / pSrcScale[1];
    float invScaleZ = g_globalScale / pSrcScale[2];

    float tempW = pSrcVec[3] * g_globalScale;
    float invScaleX = g_globalScale / pSrcScale[0];

    pDstVec[0] = pSrcVec[0] * invScaleX;
    pDstVec[1] = pSrcVec[1] * invScaleY;
    pDstVec[2] = pSrcVec[2] * invScaleZ;
    pDstVec[3] = tempW;
    pDstVec[3] = g_globalScale;  // note: overwritten – possibly intentional (set w to identity value)
}