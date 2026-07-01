// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d8b050;
  // Set additional function pointers at offsets +0x3C and +0x48
  this[0xf] = &PTR_LAB_00d8b040;  // +0x3C
  this[0x12] = &PTR_LAB_00d8b03c; // +0x48
  
  // Call sub-object destructors
  FUN_004086d0(this + 0x14); // +0x50 sub-object destructor
  FUN_00408310(this + 0x14); // +0x50 sub-object destructor
  
  // Delete owned pointer at +0x70
  if (this[0x1c] != 0) { // +0x70
    (*(code *)this[0x1f])(this[0x1c]); // +0x7C function pointer
  }
  
  // Delete owned pointer at +0x5C
  if (this[0x17] != 0) { // +0x5C
    (*(code *)this[0x1a])(this[0x17]); // +0x68 function pointer
  }
  
  // Global cleanup
  FUN_0046c640();
  return;
}