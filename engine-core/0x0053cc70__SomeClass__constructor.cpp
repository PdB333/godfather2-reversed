// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(int this)
{
  // Call base class constructor at 0x00612e00
  FUN_00612e00();
  
  // Initialize member variables at +0x10 and +0x14 to zero (likely flags or handles)
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x14) = 0;
  
  return;
}