// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d91ad4;
  
  // Set function pointers at offsets +0x3C (0xF * 4) and +0x48 (0x12 * 4)
  this[0xf] = &PTR_LAB_00d91ac4;  // +0x3C
  this[0x12] = &PTR_LAB_00d91ac0; // +0x48
  
  // Initialize/release sub-objects at +0x50 (0x14 * 4) and +0x58 (0x16 * 4)
  FUN_004086d0(this + 0x14);  // +0x50 - likely a sub-object destructor or cleanup
  FUN_00408310(this + 0x14);  // +0x50 - another cleanup step
  FUN_004086d0(this + 0x16);  // +0x58 - sub-object cleanup
  FUN_00408310(this + 0x16);  // +0x58 - another cleanup step
  
  // Global static cleanup
  FUN_004086d0(&DAT_0120e93c);  // Global object cleanup
  
  // Cleanup pointer at +0x7C (0x1F * 4)
  if ((this[0x1f] != 0) && (DAT_01129934 != 0)) {  // +0x7C
    FUN_0098f9e0(this[0x1f]);  // Release resource
    this[0x1f] = 0;  // Null out pointer
  }
  
  // Call function pointer at +0x78 (0x1E * 4) on object at +0x6C (0x1B * 4)
  if (this[0x1b] != 0) {  // +0x6C
    (*(code *)this[0x1e])(this[0x1b]);  // +0x78 - function pointer call
  }
  
  // Final cleanup
  FUN_0046c640();  // Global cleanup function
  return;
}