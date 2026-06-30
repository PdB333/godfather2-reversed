// FUNC_NAME: AptNativeHash::findItem
int AptNativeHash::findItem(byte *param_1)
{
  code *pcVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int unaff_EDI;
  int unaff_FS_OFFSET;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  if (unaff_EDI != 0) goto LAB_005bb333;
  local_14 = "pItem";
  local_10 = "..\\source\\Apt\\AptNativeHash.cpp";
  local_c = 0x169;
  local_8 = 2;
  local_4 = &DAT_0112916a;
  if (DAT_0112916a == '\0') goto LAB_005bb333;
  piVar4 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar2 = 1;
  if (piVar4 == (int *)0x0) {
LAB_005bb311:
    if ((uVar2 & 2) != 0) {
      *local_4 = 0;
    }
  }
  else {
    uVar2 = (**(code **)(*piVar4 + 8))(&local_14,"pItem");
    if (local_4 != (undefined1 *)0x0) goto LAB_005bb311;
  }
  if (((piVar4 != (int *)0x0) || (local_8 != 4)) &&
     (((uVar2 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
    pcVar1 = (code *)swi(3);
    iVar3 = (*pcVar1)();
    return iVar3;
  }
LAB_005bb333:
  // +0x08: hash table bucket count
  iVar3 = *(int *)(unaff_EDI + 8);
  if (iVar3 == 0) {
    // Compute hash bucket index from first byte of key
    iVar5 = 1 << (*param_1 & 0x1f);
    // +0x0C: hash table mask
    iVar3 = (iVar5 - 1U & *(uint *)(unaff_EDI + 0xc)) + 1;
    if (iVar3 < iVar5) {
      // +0x04: pointer to hash table entries array
      piVar4 = (int *)(*(int *)(param_1 + 4) + iVar3 * 4);
      do {
        if (*piVar4 != 0) {
          return *(int *)(*(int *)(param_1 + 4) + iVar3 * 4);
        }
        iVar3 = iVar3 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar3 < iVar5);
    }
    iVar3 = 0;
  }
  return iVar3;
}