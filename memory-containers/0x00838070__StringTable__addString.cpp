// FUNC_NAME: StringTable::addString
void __thiscall StringTable::addString(char *this, int stringId, char *stringPtr, char *param_4)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  char *pcVar6;
  char *pcVar7;
  
  pcVar1 = param_4;
  pcVar7 = stringPtr;
  if (stringPtr != (char *)0x0) {
    do {
      pcVar6 = pcVar1;
      if (*pcVar7 == '\0') break;
      cVar2 = FUN_00837e90(pcVar7,&param_4); // likely hashString or findBucket
      if (cVar2 == '\0') {
        iVar4 = FUN_009c8e50(0x2c); // allocate memory for new string node (size 0x2c)
        if (iVar4 == 0) {
          this = (char *)0x0;
        }
        else {
          this = (char *)FUN_00837d90(pcVar7,this); // copyString or createStringNode
        }
        stringPtr = this;
        FUN_00838010(&stringPtr); // insertIntoHashTable
      }
      else {
        this = *(char **)(*(int *)(this + 0x20) + (int)param_4 * 4); // follow hash chain
      }
      pcVar1 = (char *)0x0;
      pcVar7 = pcVar6;
    } while (pcVar6 != (char *)0x0);
  }
  uVar3 = 0;
  if (*(uint *)(this + 0x18) != 0) { // +0x18: count of stored IDs
    piVar5 = *(int **)(this + 0x14); // +0x14: array of IDs
    do {
      if (*piVar5 == stringId) {
        return;
      }
      uVar3 = uVar3 + 1;
      piVar5 = piVar5 + 1;
    } while (uVar3 < *(uint *)(this + 0x18));
  }
  iVar4 = *(int *)(this + 0x1c); // +0x1c: capacity of ID array
  if (*(int *)(this + 0x18) == iVar4) {
    if (iVar4 == 0) {
      iVar4 = 1;
    }
    else {
      iVar4 = iVar4 * 2;
    }
    FUN_00837cb0(iVar4); // resizeIDArray
  }
  piVar5 = (int *)(*(int *)(this + 0x14) + *(int *)(this + 0x18) * 4);
  *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1;
  if (piVar5 != (int *)0x0) {
    *piVar5 = stringId;
  }
  return;
}