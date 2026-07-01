// FUNC_NAME: Truck::constructor
undefined4 * __thiscall Truck::constructor(undefined4 *this,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  GameBase::constructor(param_2,param_3); // +0x0 (base class)
  *this = &TRUCK_VTABLE; // +0x0 vtable pointer
  if (this[0x12] == 0) { // +0x48 check if collision data exists
    iVar2 = 0;
  }
  else {
    iVar2 = this[0x12] + -0x48; // +0x48 adjust collision pointer base
  }
  this[0x16] = iVar2; // +0x58 mCollisionDataBase
  this[0x18] = 0; // +0x60 mSomeFlag1
  this[0x19] = 0; // +0x64 mSomeFlag2
  this[0x1a] = 0; // +0x68 mSomeFlag3
  if (iVar2 != 0) {
    uVar1 = FUN_0043b870(DAT_01131018); // allocate something from resource manager
    this[0x17] = uVar1; // +0x5c mResourceHandle
    return this;
  }
  this[0x17] = 0; // +0x5c clear handle if no collision
  return this;
}