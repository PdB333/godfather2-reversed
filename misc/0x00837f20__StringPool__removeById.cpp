// FUNC_NAME: StringPool::removeById
void __thiscall StringPool::removeById(int this, int id, char *name, undefined4 param_4)
{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  char cVar4;
  uint uVar5;
  int *piVar6;
  
  // If name is null or empty, remove by id from the pool
  if ((name == (char *)0x0) || (*name == '\0')) {
    uVar2 = *(uint *)(this + 0x18); // +0x18: pool count
    uVar5 = 0;
    if (uVar2 != 0) {
      piVar6 = *(int **)(this + 0x14); // +0x14: pool entries array
      do {
        if (*piVar6 == id) {
          // Found the entry, shift remaining entries down
          if (uVar5 != uVar2 - 1) {
            *(undefined4 *)(*(int *)(this + 0x14) + uVar5 * 4) =
                 *(undefined4 *)(*(int *)(this + 0x14) + -4 + uVar2 * 4);
          }
          // Decrement pool count
          *(int *)(this + 0x18) = *(int *)(this + 0x18) + -1;
          return;
        }
        uVar5 = uVar5 + 1;
        piVar6 = piVar6 + 1;
      } while (uVar5 < uVar2);
      return;
    }
  }
  else {
    // Remove by name - first get the hash/index for the name
    cVar4 = FUN_00837e90(name, &name); // likely hash function that also advances name pointer
    pcVar3 = name;
    if (cVar4 != '\0') {
      // Get slot from hash table (+0x20) using the updated name pointer as index
      iVar1 = *(int *)(*(int *)(this + 0x20) + (int)name * 4); // +0x20: hash table
      // Recursive call to remove by id (with null name)
      FUN_00837f20(id, param_4, 0);
      // If the slot is now empty (count == 0 and some other condition)
      if ((*(int *)(iVar1 + 0x18) == 0) && (*(int *)(iVar1 + 0x24) == 0)) {
        // Free the slot resources
        FUN_00837c70(pcVar3);
        FUN_00837dc0();
        FUN_009c8eb0(iVar1);
      }
    }
  }
  return;
}