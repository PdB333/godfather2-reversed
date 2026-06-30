// FUNC_NAME: AnimMath::lerpDirectionVectors
void __cdecl AnimMath::lerpDirectionVectors(float blendFactor, Vector3* pSrc1, Vector3* pSrc2, Vector3* pDst)
{
  float invBlend;
  float x;
  float y;
  float z;
  float w;

  // Call setup/fixup function with global data
  FUN_0056cc80(blendFactor, (int)pSrc1, (int)pSrc2, (int)pDst, DAT_00e2e780);

  // (1 - t) factor
  invBlend = DAT_00e2b1a4 - blendFactor;

  // Weight src1 by (1-t) and store temporarily
  x = invBlend * pSrc1->x;
  y = invBlend * pSrc1->y;
  z = invBlend * pSrc1->z;
  w = invBlend * pSrc1->w;

  // Write weighted src1 to output
  pDst->x = x;
  pDst->y = y;
  pDst->z = z;
  pDst->w = w;

  // Accumulate weighted src2: result = (1-t)*src1 + t*src2
  pDst->x = blendFactor * pSrc2->x + x;
  pDst->y = blendFactor * pSrc2->y + y;
  pDst->z = blendFactor * pSrc2->z + z;
  pDst->w = blendFactor * pSrc2->w + w;

  // Force w to zero to maintain direction vector format
  pDst->w = 0.0f;
}