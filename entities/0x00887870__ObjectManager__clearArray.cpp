// FUNC_NAME: ObjectManager::clearArray
void ObjectManager::clearArray(int param_1, uint param_2)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (param_2 != 0) {
    do {
      iVar2 = *(int *)(param_1 + uVar3 * 4); // +0x0: array of object pointers
      while (iVar2 != 0) {
        iVar1 = *(int *)(iVar2 + 0x1c); // +0x1c: next pointer in linked list
        FUN_009c8f10(iVar2); // likely Object::release or delete
        iVar2 = iVar1;
      }
      *(undefined4 *)(param_1 + uVar3 * 4) = 0; // clear array slot
      uVar3 = uVar3 + 1;
    } while (uVar3 < param_2);
  }
  return;
}