// FUNC_NAME: SomeManager::removeEntityFromList
void __thiscall SomeManager::removeEntityFromList(int this, int entityId)
{
  int iVar1;
  int *piVar2;
  uint index;
  
  index = 0;
  if (*(uint *)(this + 100) != 0) {
    piVar2 = (int *)(*(int *)(this + 0x60) + 4);
    while( true ) {
      // Check if the entity at +0x168 is valid (non-zero) and compute adjusted ID
      if (*(int *)(*piVar2 + 0x168) == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(*piVar2 + 0x168) + -0x48;
      }
      if (iVar1 == entityId) break;
      index = index + 1;
      piVar2 = piVar2 + 2;
      if (*(uint *)(this + 100) <= index) {
        return;
      }
    }
    // Found the entity at index; get its pointer from the array (offset +0x60 is array base, +4 is first element)
    entityId = **(int **)(*(int *)(this + 0x60) + 4 + index * 8);
    iVar1 = FUN_00949380(&entityId);
    if (-1 < iVar1) {
      FUN_0094aca0();
    }
  }
  return;
}