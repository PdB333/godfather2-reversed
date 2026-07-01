// FUNC_NAME: EntityManager::removeEntityByType
void __thiscall EntityManager::removeEntityByType(int thisPtr, int *entityTypePtr)
{
  undefined4 *listNode;
  int vtableOffset;
  int *currentTypePtr;
  char result;
  int *typePtrCopy;
  
  currentTypePtr = entityTypePtr;
  for (listNode = *(undefined4 **)(thisPtr + 0x28); listNode != (undefined4 *)(thisPtr + 0x28);
      listNode = (undefined4 *)*listNode) {
    if (((currentTypePtr != (int *)0x0) && (vtableOffset = *(int *)(listNode[2] + 8), vtableOffset != 0)) && (vtableOffset != 0x48)
       ) {
      vtableOffset = *(int *)(listNode[2] + 8);
      if (vtableOffset == 0) {
        typePtrCopy = (int *)0x0;
      }
      else {
        typePtrCopy = (int *)(vtableOffset + -0x48);
      }
      if (currentTypePtr == typePtrCopy) {
        entityTypePtr = (int *)0x0;
        result = (**(code **)(*currentTypePtr + 0x10))(0x383225a1, &entityTypePtr);
        if ((result != '\0') && (entityTypePtr != (int *)0x0)) {
          FUN_008a0af0(entityTypePtr);
        }
        if ((undefined4 *)listNode[2] != (undefined4 *)0x0) {
          (*(code *)**(undefined4 **)listNode[2])(1);
        }
      }
    }
  }
  FUN_0089fa20(currentTypePtr);
  return;
}