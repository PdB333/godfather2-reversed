// FUNC_NAME: NounHashTable::findByKey
int __thiscall NounHashTable::findByKey(int this, int *keyParts)
// this: pointer to NounHashTable (likely a hash table storing noun data by a 4-part key)
// keyParts: array of 4 ints forming the composite key
// Each noun entry at +0x1c..+0x28 stores the 4 key components
// Returns pointer to noun data if found, 0 otherwise
{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (*(uint *)(this + 0xc) != 0) {
    piVar2 = *(int **)(this + 8); // +0x08: pointer to array of noun entries
    do {
      iVar1 = *piVar2;
      if ((((*(int *)(iVar1 + 0x1c) == *keyParts) &&        // +0x1c: key part 0
            (*(int *)(iVar1 + 0x20) == keyParts[1])) &&      // +0x20: key part 1
            (*(int *)(iVar1 + 0x24) == keyParts[2])) &&      // +0x24: key part 2
            (*(int *)(iVar1 + 0x28) == keyParts[3])) {       // +0x28: key part 3
        return iVar1;
      }
      uVar3 = uVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (uVar3 < *(uint *)(this + 0xc)); // +0x0c: entry count
  }
  return 0;
}