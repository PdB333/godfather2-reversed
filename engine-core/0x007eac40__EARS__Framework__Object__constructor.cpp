// FUNC_NAME: EARS::Framework::Object::constructor
undefined4 * __thiscall EARSFrameworkObjectConstructor(undefined4 *this, undefined4 param_2, undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  
  FUN_007ab5e0(param_2,param_3);
  *this = &PTR_LAB_00d6fe74;
  this[0x1d] = 0;  // +0x74 - some pointer/flag
  this[0x1e] = 0;  // +0x78 - some pointer/flag
  FUN_007f63e0(0x11); // allocate 0x11 bytes? or some initialization
  iVar1 = FUN_007ab150(); // get some manager/singleton
  this[0x1f] = *(undefined4 *)(iVar1 + 4); // +0x7c - store pointer from manager+4
  puVar2 = (undefined4 *)FUN_007ab150(); // get same manager again
  (**(code **)*puVar2)(2); // call virtual function with arg 2
  iVar1 = FUN_007ab130(); // get another manager/singleton
  this[0x1d] = *(undefined4 *)(iVar1 + 4); // +0x74 - store pointer from other manager+4
  puVar2 = (undefined4 *)FUN_007ab130(); // get same manager again
  (**(code **)*puVar2)(0x3f); // call virtual function with arg 0x3f
  return this;
}