// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  *this = &PTR_LAB_00d761ec; // vtable pointer
  iVar1 = (**(code **)(*(int *)this[0x14] + 0x24))(); // +0x50: some manager/component
  if (iVar1 != 0) {
    uVar3 = 5;
    uVar2 = (**(code **)(*(int *)this[0x14] + 0x24))(5); // query for type 5
    FUN_0043c5b0(uVar2, uVar3); // register/attach something
  }
  if (this[0x19] != 0) { // +0x64: some pointer
    FUN_004daf90(this + 0x19); // release/destroy
  }
  FUN_0086aff0(); // base class constructor
  if ((param_2 & 1) != 0) {
    FUN_00624da0(this); // delete operator
  }
  return this;
}