// FUNC_NAME: StringTable::hashStrings
void StringTable::hashStrings(int *param_1)

{
  int *piVar1;
  byte bVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  byte *pbVar6;
  int iVar7;
  int iVar8;
  int unaff_EDI;
  
  piVar4 = param_1;
  iVar8 = 0;
  piVar1 = param_1 + 2;  // +0x08: count of strings
  param_1 = (int *)0x0;
  iVar7 = 0;
  if (0 < *piVar1) {
    do {
      pbVar6 = *(byte **)(*piVar4 + iVar8 * 4);  // get string pointer from array
      iVar7 = 0;
      if (pbVar6 != (byte *)0x0) {
        bVar2 = *pbVar6;
        while (bVar2 != 0) {
          uVar5 = (uint)bVar2;
          pbVar6 = pbVar6 + 1;
          if (uVar5 - 0x41 < 0x1a) {  // ASCII uppercase A-Z range
            uVar5 = uVar5 + 0x20;  // convert to lowercase
          }
          iVar7 = iVar7 * 0x1003f + uVar5;  // hash computation
          bVar2 = *pbVar6;
        }
      }
      if ((unaff_EDI != 0) && (*(int *)(unaff_EDI + 0x70) != 0)) {
        iVar3 = *(int *)(*(int *)(*(int *)(unaff_EDI + 0x70) + 0x1c) + 0x14 +
                        *(short *)(unaff_EDI + 0x74) * 0x18);
        iVar7 = FUN_005828a0(iVar7,iVar3);
        if ((iVar7 != -1) &&
           ((iVar7 = *(int *)(iVar3 + 0x10 + iVar7 * 0x14), iVar7 != -1 && (-1 < iVar7)))) {
          *(short *)(piVar4[1] + (int)param_1 * 2) = (short)iVar7;  // store result in output array
          param_1 = (int *)((int)param_1 + 1);
        }
      }
      iVar8 = iVar8 + 1;
      iVar7 = (int)param_1;
    } while (iVar8 < piVar4[2]);
  }
  piVar4[2] = iVar7;  // update count of successful hashes
  return;
}