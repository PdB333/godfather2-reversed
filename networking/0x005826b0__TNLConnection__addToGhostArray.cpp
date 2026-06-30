// FUNC_NAME: TNLConnection::addToGhostArray
void TNLConnection::addToGhostArray(int *thisPtr, int param_2, char param_3)
{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int ghostIndex;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  *thisPtr = ghostIndex;
  if ((-1 < ghostIndex) && (iVar2 = ghostIndex * 4, *(int *)(thisPtr[2] + ghostIndex * 4) == 0)) {
    uVar4 = FUN_00582470(thisPtr[1]); // allocateGhost
    *(undefined4 *)(thisPtr[2] + iVar2) = uVar4;
    if (param_3 != '\0') {
      puVar1 = (uint *)(**(int **)(thisPtr[2] + iVar2) + (ghostIndex >> 5) * 4);
      *puVar1 = *puVar1 | 1 << ((byte)ghostIndex & 0x1f);
    }
    if (ghostIndex < thisPtr[1]) {
      iVar6 = ghostIndex << 4;
      iVar7 = ghostIndex;
      do {
        if (*(short *)(param_2 + 0x74) < 0) {
LAB_00582767:
          iVar5 = -1;
        }
        else {
          iVar5 = (int)*(short *)(param_2 + 0x74);
          if (((*(int *)(*(int *)(param_2 + 0x70) + 0x18) <= iVar5) || (iVar7 < 0)) ||
             (iVar3 = *(int *)(*(int *)(param_2 + 0x70) + 0x1c),
             *(int *)(iVar3 + 8 + iVar5 * 0x18) <= iVar7)) goto LAB_00582767;
          iVar5 = *(int *)(iVar6 + *(int *)(iVar3 + iVar5 * 0x18 + 0xc));
        }
        if (((*(uint *)(**(int **)(thisPtr[2] + iVar2) + (iVar5 >> 5) * 4) &
             1 << ((byte)iVar5 & 0x1f)) != 0) || (iVar5 == ghostIndex)) {
          puVar1 = (uint *)(**(int **)(thisPtr[2] + iVar2) + (iVar7 >> 5) * 4);
          *puVar1 = *puVar1 | 1 << ((byte)iVar7 & 0x1f);
        }
        iVar7 = iVar7 + 1;
        iVar6 = iVar6 + 0x10;
      } while (iVar7 < thisPtr[1]);
    }
  }
  return;
}