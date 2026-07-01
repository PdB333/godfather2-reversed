// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(SomeClass *this)
{
  // Set vtable pointer to first vtable (likely base class)
  this->vtable = &PTR_FUN_00d7ca00;
  
  // Check if some condition is true (likely a flag or pointer)
  int iVar1 = FUN_006101a0();
  if (iVar1 != 0) {
    // Call cleanup function on member at offset +0x20 (param_1 + 8, assuming 4-byte pointers)
    FUN_00610100(&this->field_0x20); // +0x20
  }
  
  // Set vtable pointer to second vtable (likely derived class or final vtable)
  this->vtable = &PTR_LAB_00e2f638;
  return;
}