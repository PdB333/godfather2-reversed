// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)

{
  // Set vtable pointer
  *this = &PTR_FUN_00d8d370;
  
  // Initialize member pointers
  this[4] = &PTR_LAB_00d8d348;  // +0x10 - some vtable or function pointer
  this[0x13] = &PTR_LAB_00d8d344; // +0x4C - another pointer
  this[0x13] = &PTR_LAB_00d8d340; // +0x4C - overwritten with different pointer
  
  // Reset global state
  _DAT_0113087c = 0;  // Global flag or counter
  
  // Call base class or initialization function
  FUN_005c16e0();  // Likely base class constructor or common init
  
  // If flag bit 0 is set, call destructor/free
  if ((flags & 1) != 0) {
    FUN_005c4480(this);  // Likely operator delete or destructor
  }
  
  return this;
}