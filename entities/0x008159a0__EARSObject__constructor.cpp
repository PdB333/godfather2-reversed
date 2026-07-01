// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this,byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d73158;
  
  // Initialize member pointers
  this[0xf] = &PTR_LAB_00d73148;  // +0x3C - some pointer member
  this[0x12] = &PTR_LAB_00d73144; // +0x48 - another pointer member
  
  // Call base class constructor
  FUN_00815be0(this);
  
  // If there's a callback object at +0x58, invoke its method at +0x64
  if (this[0x16] != 0) {           // +0x58 - callback object pointer
    (*(code *)this[0x19])(this[0x16]); // +0x64 - callback function pointer
  }
  
  // Global initialization call
  FUN_0046c640();
  
  // If flag bit 0 is set, free memory (operator delete with size 0xA0)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0xa0);      // operator delete(this, 0xA0)
  }
  
  return this;
}