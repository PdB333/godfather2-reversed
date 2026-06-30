// FUNC_NAME: Entity::updateComponents
void Entity::updateComponents(undefined4 param_1)
{
  int iVar1;
  int in_EAX;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  // +0x58: byte count of first component list
  if (*(char *)(in_EAX + 0x58) != '\0') {
    do {
      // +0x1bc: pointer to component manager
      // +0x18: offset to component type array in manager
      // +0x59: byte array of component indices
      if (*(int *)(*(int *)(*(int *)(in_EAX + 0x1bc) + 0x18) +
                  (uint)*(byte *)(in_EAX + 0x59 + iVar3) * 4) != -2) {
        (**(code **)(*DAT_01205590 + 4))();
      }
      FUN_005945a0(param_1); // updateComponentType1
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)(uint)*(byte *)(in_EAX + 0x58));
  }
  
  iVar3 = 0;
  // +0x79: byte count of second component list
  if (*(char *)(in_EAX + 0x79) != '\0') {
    do {
      uVar2 = (uint)*(byte *)(in_EAX + 0x7a + iVar3);
      iVar1 = *(int *)(in_EAX + 0x1bc);
      // +0x24: offset to second component type array
      if (*(int *)(*(int *)(iVar1 + 0x24) + uVar2 * 4) != -2) {
        (**(code **)(*DAT_01205590 + 4))();
      }
      // +0x20: pointer to second component data array
      FUN_00595e70(*(undefined4 *)(*(int *)(iVar1 + 0x20) + uVar2 * 4), param_1);
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)(uint)*(byte *)(in_EAX + 0x79));
  }
  
  iVar3 = 0;
  // +0x9a: byte count of third component list
  if (*(char *)(in_EAX + 0x9a) != '\0') {
    do {
      uVar2 = (uint)*(byte *)(in_EAX + 0x9c + iVar3);
      iVar1 = *(int *)(in_EAX + 0x1bc);
      // +0x30: offset to third component type array
      if (*(int *)(*(int *)(iVar1 + 0x30) + uVar2 * 4) != -2) {
        (**(code **)(*DAT_01205590 + 4))();
      }
      // +0x2c: pointer to third component data array
      // vtable+0xc: update method
      (**(code **)(**(int **)(*(int *)(iVar1 + 0x2c) + uVar2 * 4) + 0xc))(param_1);
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)(uint)*(byte *)(in_EAX + 0x9a));
  }
  
  // +0x1c0: pointer to additional update handler
  if (*(int *)(in_EAX + 0x1c0) != 0) {
    FUN_00598980(param_1); // updateAdditionalComponents
  }
  return;
}