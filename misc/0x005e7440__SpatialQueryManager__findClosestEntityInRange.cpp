// FUNC_NAME: SpatialQueryManager::findClosestEntityInRange
undefined1 FUN_005e7440(float *param_1)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  int unaff_ESI;
  float *unaff_EDI;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined1 local_25;
  
  *unaff_EDI = DAT_00e2e50c; // +0x0: maxDistanceSq (initialized to large value)
  bVar2 = *(byte *)(unaff_ESI + 0x1c); // +0x1c: entityCount
  uVar3 = (uint)bVar2;
  uVar4 = 0;
  local_25 = 0;
  if (bVar2 == 0) {
    return 0;
  }
  do {
    if ((((*(char *)(unaff_ESI + 0x18 + uVar4) != '\0') && ((byte)uVar4 < 4)) &&
        ((uVar4 & 0xff) < uVar3)) &&
       (((bVar2 != 0 && ((byte)uVar4 < bVar2)) &&
        ((iVar1 = *(int *)(unaff_ESI + 4 + (uVar4 & 0xff) * 4), iVar1 != 0 &&
         (fVar7 = param_1[1] - *(float *)(iVar1 + 0x44), fVar6 = *param_1 - *(float *)(iVar1 + 0x40)
         , fVar5 = param_1[2] - *(float *)(iVar1 + 0x48),
         fVar5 = fVar5 * fVar5 + fVar7 * fVar7 + fVar6 * fVar6, fVar5 < *unaff_EDI)))))) {
      *unaff_EDI = fVar5;
      local_25 = 1;
    }
    bVar2 = *(byte *)(unaff_ESI + 0x1c);
    uVar3 = (uint)bVar2;
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < (int)uVar3);
  return local_25;
}