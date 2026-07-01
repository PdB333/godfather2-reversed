// FUNC_NAME: CharacterEntity::shutdown

void __thiscall CharacterEntity::shutdown(CharacterEntity *this, int reason)
{
  bool bNoRemainingRef;
  int iVar1;
  BaseObject *baseObj;
  int *piVar2;
  int *somePtr;
  
  preShutdownCleanup(this);
  somePtr = (int *)(this->unkA4);
  if ((this->unkA4 != 0) && (this->unkA4 != 0x48)) {
    iVar1 = *somePtr;
    if ((iVar1 == 0) || (iVar1 == 0x48)) {
      iVar1 = 0;
    }
    else {
      iVar1 = iVar1 + -0xc;
    }
    releaseSecondaryResource(reason, iVar1, 0);
  }
  if ((this->flags >> 0x14 & 1) == 0) {
    this->flags |= 0x800000;
  }
  if (this->entityPtr == 0) {
    baseObj = (BaseObject *)0x0;
  }
  else {
    baseObj = (BaseObject *)(this->entityPtr + -0x48);
  }
  if ((baseObj->field40 & 1) != 0) {
    if (this->entityPtr == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = (int)(BaseObject *)(this->entityPtr + -0x48);
    }
    (**(code **)(*(int *)iVar1 + 0x1c4))(this->typeId);
    unloadResource(this->unkCC);
  }
  if ((((this->typeId == 0x637b907) && ((this->flags >> 0x1d & 1) != 0)) && (this->entityPtr != 0)) &&
     ((this->entityPtr != 0x48 && (iVar1 = getGlobalManager(DAT_01131018), iVar1 != 0)))) {
    *(undefined4 *)(iVar1 + 0x50) = 1;
  }
  globalCleanupStep();
  if (this->entityPtr == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = (int)(BaseObject *)(this->entityPtr + -0x48);
  }
  entityCleanup1((BaseObject *)iVar1);
  if (this->entityPtr == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = (int)(BaseObject *)(this->entityPtr + -0x48);
  }
  entityCleanup2((BaseObject *)iVar1);
  getGlobalManager(DAT_01131010);
  debugCleanup();
  this->flags &= 0xfffbffff;
  iVar1 = this->flags;
  if ((iVar1 < 0) || (((this->unkA4 == 0 || this->unkA4 == 0x48) && (this->unkAC == 0)))) {
    bNoRemainingRef = true;
  }
  else {
    bNoRemainingRef = false;
  }
  this->flags &= 0x3fffffff;
  if (this->unkA4 != 0) {
    releasePointer(&this->unkA4);
    this->unkA4 = 0;
  }
  if (((byte)((uint)iVar1 >> 0x1e) & 1) != 0) {
    if (this->entityPtr == 0) {
      piVar2 = (int *)0x0;
    }
    else {
      piVar2 = (int *)(this->entityPtr + -0x48);
    }
    (**(code **)(*piVar2 + 0x288))(2, 0, 0);
    return;
  }
  if (bNoRemainingRef) {
    if (this->entityPtr != 0) {
      deallocateMemory(this->entityPtr + -0xc);
      return;
    }
    deallocateMemory((void *)0x3c);
  }
  return;
}