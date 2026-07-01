// FUNC_NAME: EntityManager::removeEntityFromList
void __thiscall EntityManager::removeEntityFromList(int this, int entity)
{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  int local_4;
  
  iVar6 = entity;
  local_4 = this;
  local_4 = FUN_007914e0(); // getEntityList
  iVar4 = FUN_007923a0(&local_4); // findEntityListIndex
  if (-1 < iVar4) {
    uVar2 = *(uint *)(iVar4 * 0x10 + 8 + *(int *)(this + 0x20)); // +0x20: entityListArray, +0x08: count
    piVar1 = (int *)(iVar4 * 0x10 + 4 + *(int *)(this + 0x20)); // +0x04: data pointer
    uVar5 = 0;
    if (uVar2 != 0) {
      piVar3 = (int *)*piVar1;
      piVar7 = piVar3;
      while (*piVar7 != entity) {
        uVar5 = uVar5 + 1;
        piVar7 = piVar7 + 1;
        if (uVar2 <= uVar5) {
          return;
        }
      }
      if (-1 < (int)uVar5) {
        if (uVar5 != uVar2 - 1) {
          piVar3[uVar5] = piVar3[uVar2 - 1]; // swap with last element
        }
        piVar1 = piVar1 + 1;
        *piVar1 = *piVar1 + -1; // decrement count
        *(uint *)(entity + 0x5c) = *(uint *)(entity + 0x5c) & 0xffdfffff; // clear flag at bit 21
        local_4 = *(int *)(entity + 0xd8); // +0xD8: parentEntity
        if (((local_4 != 0) && (iVar6 = FUN_007923a0(&local_4), -1 < iVar6)) &&
           (iVar6 = FUN_006b1b10(&param_2), -1 < iVar6)) {
          FUN_006b1aa0(iVar6); // remove from parent's child list
        }
      }
    }
  }
  return;
}