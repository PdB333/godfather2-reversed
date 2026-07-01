// FUNC_NAME: EntityManager::findOrCreateEntityByPosition
void __thiscall EntityManager::findOrCreateEntityByPosition(int this, int entityData)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  uVar3 = 0;
  if (*(uint *)(this + 0x18) != 0) {
    piVar4 = *(int **)(this + 0x14); // +0x14: entity array pointer
    do {
      iVar1 = *piVar4;
      // Compare position components (x, y, z, w) at offsets +0x24, +0x28, +0x2c, +0x30
      if ((((*(int *)(iVar1 + 0x24) == *(int *)(entityData + 0x20)) &&
           (*(int *)(iVar1 + 0x28) == *(int *)(entityData + 0x24))) &&
          (*(int *)(iVar1 + 0x2c) == *(int *)(entityData + 0x28))) &&
         (*(int *)(iVar1 + 0x30) == *(int *)(entityData + 0x2c))) {
        *(int *)(entityData + 0x50) = iVar1; // +0x50: entity pointer
        return;
      }
      uVar3 = uVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (uVar3 < *(uint *)(this + 0x18)); // +0x18: entity count
  }
  // Entity not found, create new one
  iVar1 = FUN_009c8e50(0x4c); // Allocate 0x4c bytes for new entity
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00827630(); // Entity constructor
  }
  // Copy position data to new entity
  *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(entityData + 0x20);
  *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(entityData + 0x24);
  *(undefined4 *)(iVar1 + 0x2c) = *(undefined4 *)(entityData + 0x28);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(entityData + 0x2c);
  
  iVar2 = *(int *)(this + 0x1c); // +0x1c: array capacity
  if (*(int *)(this + 0x18) == iVar2) {
    if (iVar2 == 0) {
      iVar2 = 1;
    }
    else {
      iVar2 = iVar2 * 2; // Double capacity
    }
    FUN_00834ec0(iVar2); // Resize entity array
  }
  piVar4 = (int *)(*(int *)(this + 0x14) + *(int *)(this + 0x18) * 4);
  *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1;
  if (piVar4 != (int *)0x0) {
    *piVar4 = iVar1;
  }
  *(int *)(entityData + 0x50) = iVar1; // +0x50: entity pointer
  return;
}