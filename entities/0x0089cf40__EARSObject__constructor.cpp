// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 *param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  // Set vtable pointer
  *this = &PTR_FUN_00e2f19c;
  this[1] = 1; // +0x04: refCount or type
  this[2] = 0; // +0x08: some flag
  FUN_004814b0(); // Base class initialization
  this[7] = &PTR_FUN_00e32808; // +0x1C: vtable or function pointer
  this[8] = 0; // +0x20: some pointer
  *this = &PTR_FUN_00d78684; // Override vtable
  this[3] = &PTR_LAB_00d78620; // +0x0C: another vtable/function pointer
  this[7] = &PTR_LAB_00d78618; // +0x1C: override again
  this[9] = 0xfe16702f; // +0x24: some constant/hash
  this[10] = 0; // +0x28: some pointer
  this[0x13] = 0; // +0x4C: some field
  this[0x14] = 0; // +0x50: some field
  FUN_0089b000(param_3, param_4, param_5); // Some initialization with parameters
  uVar1 = param_2[1]; // +0x04 of param_2
  uVar2 = param_2[2]; // +0x08 of param_2
  uVar3 = param_2[3]; // +0x0C of param_2
  this[0xc] = *param_2; // +0x30: copy first 4 words from param_2
  this[0xd] = uVar1; // +0x34
  this[0xe] = uVar2; // +0x38
  this[0xf] = uVar3; // +0x3C
  return this;
}