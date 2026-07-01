// FUNC_NAME: ResourceFile::fixupPointers
uint __fastcall ResourceFile::fixupPointers(int *param_1)
{
  int iVar1;
  uint in_EAX;
  int *piVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = in_EAX & 0xffffff00;
  if ((*param_1 == 0x3b004eb9) && (param_1[1] == 7)) {
    // Fixup relative offsets to absolute pointers (base = param_1)
    if (param_1[2] != 0) {
      param_1[2] = param_1[2] + (int)param_1;
    }
    if (param_1[4] != 0) {
      param_1[4] = param_1[4] + (int)param_1;
    }
    piVar2 = (int *)param_1[6];
    if (piVar2 != (int *)0x0) {
      piVar2 = (int *)((int)piVar2 + (int)param_1);
      param_1[6] = (int)piVar2;
    }
    uVar4 = 0;
    if (param_1[3] != 0) {
      iVar3 = 0;
      do {
        iVar1 = *(int *)(param_1[2] + 0x14 + iVar3);
        piVar2 = (int *)(param_1[2] + 0x14 + iVar3);
        if (iVar1 != 0) {
          *piVar2 = iVar1 + (int)param_1;
        }
        uVar4 = uVar4 + 1;
        iVar3 = iVar3 + 0x18;
      } while (uVar4 < (uint)param_1[3]);
    }
    if (param_1[5] != 0) {
      iVar3 = 0;
      uVar4 = 0;
      do {
        piVar2 = (int *)(iVar3 + 0x6c + param_1[4]);
        iVar1 = *piVar2;
        if (iVar1 != 0) {
          *piVar2 = iVar1 + (int)param_1;
        }
        iVar1 = *(int *)(iVar3 + 0x70 + param_1[4]);
        piVar2 = (int *)(iVar3 + 0x70 + param_1[4]);
        if (iVar1 != 0) {
          *piVar2 = iVar1 + (int)param_1;
        }
        uVar4 = uVar4 + 1;
        iVar3 = iVar3 + 0x80;
      } while (uVar4 < (uint)param_1[5]);
    }
    uVar4 = 0;
    if (param_1[7] != 0) {
      do {
        piVar2 = (int *)(param_1[6] + uVar4 * 4);
        if (*piVar2 != 0) {
          *piVar2 = *piVar2 + (int)param_1;
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < (uint)param_1[7]);
    }
    uVar4 = CONCAT31((int3)((uint)piVar2 >> 8),1);
  }
  return uVar4;
}