// FUNC_NAME: HashTable::addEntry
void __thiscall HashTable::addEntry(int this, int key, int value)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  
  // +0x64 (100) seems to indicate if value is valid
  if (*(int *)(key + 100) != 0) {
    iVar2 = *(int *)(key + 0x50);  // +0x50: hash key computation
    iVar1 = DAT_01205224 + *(int *)(key + 100);  // global base + offset
    // +0x120: flags bit 0 = "allow duplicates" or "overwrite existing"
    if ((*(byte *)(this + 0x120) & 1) != 0) {
      uVar3 = 0;
      if (*(uint *)(this + 0x20) != 0) {  // +0x20: entry count
        piVar5 = *(int **)(this + 0x1c);  // +0x1c: pointer to entry array (pair of ints)
        do {
          if (*piVar5 == iVar2) {  // key match
            piVar5[1] = iVar1;  // overwrite value
            return;
          }
          uVar3 = uVar3 + 1;
          piVar5 = piVar5 + 2;  // each entry is 8 bytes (2 ints)
        } while (uVar3 < *(uint *)(this + 0x20));
      }
    }
    iVar4 = *(int *)(this + 0x24);  // +0x24: capacity
    if (*(int *)(this + 0x20) == iVar4) {  // full, need to grow
      if (iVar4 == 0) {
        iVar4 = 1;
      }
      else {
        iVar4 = iVar4 * 2;
      }
      FUN_0077d9b0(iVar4);  // likely reallocate/resize array
    }
    piVar5 = (int *)(*(int *)(this + 0x1c) + *(int *)(this + 0x20) * 8);
    *(int *)(this + 0x20) = *(int *)(this + 0x20) + 1;  // increment count
    if (piVar5 != (int *)0x0) {
      *piVar5 = iVar2;  // store key
      piVar5[1] = iVar1;  // store value
    }
  }
  return;
}