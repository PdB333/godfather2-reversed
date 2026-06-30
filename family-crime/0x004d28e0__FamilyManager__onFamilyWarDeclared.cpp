// FUNC_NAME: FamilyManager::onFamilyWarDeclared
void FamilyManager::onFamilyWarDeclared(int thisPtr, undefined4 param_2, int familyId)
{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint local_24;
  int local_20;
  int local_1c [2];
  int local_14;
  uint local_10;
  
  if (familyId == *(int *)(thisPtr + 8)) {
    *(undefined1 *)(thisPtr + 0x18) = 1; // +0x18: warActive flag
    FUN_00497ca0(param_2); // likely some notification/event trigger
    local_24 = 0;
    if (local_10 != 0) {
      do {
        iVar4 = *(int *)(local_14 + local_24 * 4);
        local_1c[0] = iVar4;
        if (iVar4 != *(int *)(thisPtr + 4)) {
          cVar1 = FUN_00497a60(iVar4,*(int *)(thisPtr + 4)); // check if family is allied
          if (cVar1 == '\0') {
            local_20 = iVar4;
            piVar2 = (int *)FUN_004986e0(&local_20); // get family data
            if (*piVar2 == 0) {
              iVar4 = 0;
            }
            else {
              iVar4 = *piVar2 + 8; // +8: family member count or similar
            }
            cVar1 = '\0';
            if (familyId == 1) {
              cVar1 = FUN_00497040(*(undefined1 *)(thisPtr + 0x1c)); // check if player family
            }
            else if (familyId == 2) {
              iVar3 = FUN_004971f0(); // check if AI family
              cVar1 = iVar3 != -1;
            }
            if ((iVar4 != 0) && (cVar1 != '\0')) {
              FUN_004866e0(local_1c); // declare war on this family
            }
          }
        }
        local_24 = local_24 + 1;
      } while (local_24 < local_10);
    }
    if (local_14 != 0) {
      FUN_009c8f10(local_14); // free memory
    }
  }
  return;
}