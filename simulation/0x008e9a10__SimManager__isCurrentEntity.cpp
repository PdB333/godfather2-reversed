// FUNC_NAME: SimManager::isCurrentEntity
__thiscall uint SimManager::isCurrentEntity(int this, int entityPtr)

{
  int iVar1;
  
  if (entityPtr != 0) {
    if (*(int *)(this + 0x84) == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(*(int *)(this + 0x84) + 0x1c);
    }
    if (entityPtr == iVar1) {
      return 1;
    }
  }
  return 0;
}