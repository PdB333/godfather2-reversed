// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d8c8f0;
  // Set some internal pointers
  this[4] = &PTR_LAB_00d8c8cc;
  this[0x13] = &PTR_LAB_00d8c8c8;
  
  // Call destructor on member at offset 0x4c * 4 = 0x130
  FUN_009c8f10(this[0x4c]);
  
  // Delete child objects if they exist, calling their destructors via vtable
  if (this[0x48] != 0) {
    (*(code *)this[0x4b])(this[0x48]); // +0x120 member destructor
  }
  if (this[0x44] != 0) {
    (*(code *)this[0x47])(this[0x44]); // +0x110 member destructor
  }
  if (this[0x40] != 0) {
    (*(code *)this[0x43])(this[0x40]); // +0x100 member destructor
  }
  if (this[0x3b] != 0) {
    (*(code *)this[0x3e])(this[0x3b]); // +0xEC member destructor
  }
  
  // Update another pointer
  this[0x1a] = &PTR_LAB_00d83b18;
  
  // Delete member at +0x50
  if (this[0x14] != 0) {
    (*(code *)this[0x17])(this[0x14]); // +0x50 member destructor
  }
  
  // Finalize vtable
  this[0x13] = &PTR_LAB_00d8c8c4;
  
  // Clear global flag
  DAT_011307e8 = 0;
  
  // Call cleanup function
  FUN_005c16e0();
}