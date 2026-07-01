// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Set vtable pointer to the first vtable (likely the base class vtable)
  *this = &PTR_FUN_00d74d3c;
  
  // If there is a non-null pointer at offset +0x08, free it
  if (this[2] != 0) {
    FUN_009c8f10(this[2]); // Likely operator delete or a custom deallocation function
  }
  
  // Set vtable pointer to the second vtable (likely the derived class vtable or a sentinel)
  *this = &PTR_LAB_00d74d38;
  
  // Reset a global flag/variable to 0
  DAT_0112a590 = 0;
  
  return;
}