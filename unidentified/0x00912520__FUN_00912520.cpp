// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(int this)
{
  // Call base class constructor or initialization function
  FUN_00957eb0();
  
  // Initialize member at offset 0x54 to 0
  *(int *)(this + 0x54) = 0;
  
  return;
}