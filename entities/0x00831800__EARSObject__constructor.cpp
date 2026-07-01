// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte param_2)

{
  int *piVar1;
  
  *this = &PTR_FUN_00d73868;  // vtable setup
  EARSObject::baseConstructor();  // FUN_0082b7a0 - likely base class constructor
  this[0xc] = &PTR_LAB_00e32854;  // +0x30: another vtable or data pointer
  EARSObject::init();  // FUN_00821f60 - initialization
  if ((param_2 & 1) != 0) {
    piVar1 = (int *)EARSObject::getAllocator();  // FUN_009c8f80 - get memory allocator
    (**(code **)(*piVar1 + 4))(this, 0xa0);  // operator delete with size 0xa0 (160 bytes)
  }
  return this;
}