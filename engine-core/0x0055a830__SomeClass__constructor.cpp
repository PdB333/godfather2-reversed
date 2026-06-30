// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(int thisPtr)
{
  FUN_009f1b20(thisPtr + -4);  // Call base class constructor (offset -4 suggests this is a derived class with base at thisPtr-4)
  FUN_009f01a0();              // Initialize some subsystem or member
  *(undefined4 *)(thisPtr + 0x30) = 0;  // Clear member at +0x30 (likely a pointer or handle)
  return;
}