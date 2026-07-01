// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Set vtable pointer to destructor vtable
  *this = &PTR_FUN_00d860c0;
  this[4] = &PTR_LAB_00d8609c;
  this[0x13] = &PTR_LAB_00d86098;
  this[0x14] = &PTR_LAB_00d86088;
  
  // Call base destructor or cleanup
  FUN_0091f7d0();
  
  // If child object exists at +0x90, call its destructor via vtable
  if (this[0x24] != 0) {
    (*(code *)this[0x27])(this[0x24]);
  }
  
  // If another child object exists at +0x7C, call its destructor via vtable
  if (this[0x1f] != 0) {
    (*(code *)this[0x22])(this[0x1f]);
  }
  
  // Call some cleanup function
  FUN_004083d0();
  
  // Update vtable pointer for destructor phase
  this[0x13] = &PTR_LAB_00d85d88;
  
  // Reset global flag
  DAT_0112a838 = 0;
  
  // Final cleanup
  FUN_005c16e0();
}