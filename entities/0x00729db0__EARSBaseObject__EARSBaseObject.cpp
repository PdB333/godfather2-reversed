// FUNC_NAME: EARSBaseObject::EARSBaseObject
undefined4 * __thiscall EARSBaseObject::constructor(EARSBaseObject *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  // Call base class constructor or engine initialization routine
  baseConstructor(param_2);
  uVar1 = g_invalidHandle; // _DAT_00d5780c - likely invalid/null handle
  // Set primary vtable pointer at offset 0x00
  this->vtable = &s_primaryVtable; // PTR_FUN_00d62544
  // Set secondary vtable pointers for multiple interface inheritance
  this->interface1Vtable = &s_interface1Vtable; // +0x3C (0xf * 4)
  this->interface2Vtable = &s_interface2Vtable; // +0x48 (0x12 * 4)
  // Initialize an array of handles (10 elements) starting at +0x50
  this->handleArray[0] = uVar1;  // +0x50
  this->handleArray[1] = uVar1;  // +0x54
  this->handleArray[2] = uVar1;  // +0x58
  this->handleArray[3] = uVar1;  // +0x5C
  this->handleArray[4] = uVar1;  // +0x60
  this->handleArray[5] = uVar1;  // +0x64
  this->handleArray[6] = uVar1;  // +0x68
  this->handleArray[7] = uVar1;  // +0x6C
  this->handleArray[8] = uVar1;  // +0x70
  this->handleArray[9] = uVar1;  // +0x74
  // Continue with member initialization
  FUN_00729ab0(this);
  return this;
}