// FUNC_NAME: PointerList::resize
void __thiscall PointerList::resize(int *param_1, uint newCapacity)
{
  int *newBuf;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  
  if ((uint)param_1[2] < newCapacity) {
    newBuf = (int *)FUN_009c8e80(newCapacity * 8);
    if (*param_1 != 0) {
      uVar4 = 0;
      piVar5 = newBuf;
      if (param_1[1] != 0) {
        do {
          piVar3 = (int *)(*param_1 + uVar4 * 8);
          if (piVar5 != (int *)0x0) {
            iVar2 = *piVar3;
            *piVar5 = iVar2;
            piVar5[1] = 0;
            if (iVar2 != 0) {
              piVar5[1] = *(int *)(iVar2 + 4);
              *(int **)(iVar2 + 4) = piVar5;
            }
          }
          if (*piVar3 != 0) {
            FUN_004daf90(piVar3);
          }
          uVar4 = uVar4 + 1;
          piVar5 = piVar5 + 2;
        } while (uVar4 < (uint)param_1[1]);
      }
      FUN_009c8f10(*param_1);
    }
    *param_1 = (int)newBuf;
    param_1[2] = newCapacity;
  }
  return;
}