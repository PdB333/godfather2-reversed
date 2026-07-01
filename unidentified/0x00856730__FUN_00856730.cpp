// FUNC_NAME: UnknownClass::constructor
void __fastcall UnknownClass::constructor(int this)
{
  // Call base class constructor
  FUN_00855830();
  
  // Set vtable pointer to class-specific vtable
  *(void ***)(this + 0x18) = &PTR_LAB_00e355fc;
  
  // Call another initialization function
  FUN_0064d150();
  
  return;
}