// FUNC_NAME: SomeClass::isStringUnique
undefined4 __thiscall SomeClass::isStringUnique(int this, char *str)
{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  uint local_20;
  uint local_1c;
  undefined4 local_18;
  code *local_14;
  int local_10 [3];
  code *local_4;
  
  local_20 = 0;
  local_18 = 0;
  local_1c = 0;
  FUN_004d3bc0(str); // likely string validation or normalization
  FUN_004dd9e0(local_10,&local_20); // some initialization
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]); // cleanup if needed
  }
  if (0xf < local_1c) { // if some count > 15, fail
LAB_00698a96:
    if (local_20 != 0) {
      (*local_14)(local_20); // cleanup
    }
    return 0;
  }
  pcVar2 = str;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = FUN_004db320(str,(int)pcVar2 - (int)(str + 1)); // hash or compute key from string
  uVar5 = (uint)*(ushort *)(*(int *)(this + 0x14) + 4); // +0x14: pointer to some container, +4: count of items
  if (uVar5 != 0) {
    piVar6 = (int *)(*(int *)(this + 4) + 0x40); // +0x04: pointer to array, +0x40: offset to first item's key
    iVar4 = 0;
    do {
      if (iVar3 == *piVar6) goto LAB_00698a96; // duplicate found
      iVar4 = iVar4 + 1;
      piVar6 = piVar6 + 0x141; // each item is 0x141 ints (0x504 bytes)
    } while (iVar4 < (int)uVar5);
  }
  if (local_20 != 0) {
    (*local_14)(local_20); // cleanup
  }
  return 1; // string is unique
}