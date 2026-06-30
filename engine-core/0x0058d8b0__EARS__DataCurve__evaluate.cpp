// FUNC_NAME: EARS::DataCurve::evaluate
uint32 EARS::DataCurve::evaluate(void *thisPtr, void *pData, int *pArrayDescriptor, uint32 param4, uint32 param5, uint32 flags, uint32 param7)
{
  byte *pTypeInfo;
  int iVar3;
  uint uVar4;
  int iVar5;
  int *pArrayBase;
  uint32 result;
  float fVar8;

  pArrayBase = pArrayDescriptor;
  iVar5 = (int)pData;

  if (*(char *)(iVar5 + 1) < 1) {
    return 0;
  }

  pTypeInfo = *(byte **)(iVar5 + 0xC);
  iVar3 = *(int *)(iVar5 + 4);
  short sIndex = *(short *)(pTypeInfo + 2);

  if ((uint)pArrayDescriptor[1] <= (uint)(int)sIndex) {
    float localZero = 0.0f;
    FUN_00591c00(&localZero); // ErrorHandler: out of bounds
  }

  uVar4 = *(uint *)(iVar3 + 0xC);
  fVar8 = *(float *)(*pArrayBase + sIndex * 4) - 0.0f; // DAT_00e2b1a4 likely 0.0f or 1.0f, here probably 0.0f

  if ((uint)pArrayBase[1] <= uVar4) {
    float localZero = 0.0f;
    FUN_00591c00(&localZero);
  }

  iVar3 = *pArrayBase;
  float param2Value = *(float *)(iVar3 + uVar4 * 4) * fVar8;
  FUN_00591730(thisPtr, iVar5, pArrayBase); // PrepareArray or BoundCheck
  fVar8 = *(float *)(iVar3 + uVar4 * 4) * fVar8;

  if (fVar8 < param2Value) {
    flags ^= 2;
  }

  if ((*pTypeInfo & 0x3F) < 0x23) {
    result = ((code *)(&DAT_0103afc0)[*pTypeInfo & 0x3F])(thisPtr, pTypeInfo, pArrayBase, fVar8, param2Value, flags, param7);
  } else {
    result = 0;
  }

  if (*(int *)((int)thisPtr + 0x7C) != 0) {
    *(float *)(*(int *)((int)thisPtr + 0x7C) + 0x20) = param2Value;
    *(float *)(*(int *)((int)thisPtr + 0x7C) + 0x1C) = fVar8;
  }

  return result;
}