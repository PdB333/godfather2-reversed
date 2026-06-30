// FUNC_NAME: SomeClass::setSomePointer
void __thiscall SomeClass::setSomePointer(int thisPtr, int newPointer)
{
  // Check if current pointer at +0x34 is non-null
  if (*(int *)(thisPtr + 0x34) != 0) {
    // If so, call cleanup/release functions
    FUN_009f1b20(thisPtr);
    FUN_009f01a0();
  }
  // Store the new pointer at +0x34
  *(int *)(thisPtr + 0x34) = newPointer;
  // If new pointer is non-null, call initialization/setup functions
  if (newPointer != 0) {
    FUN_009f1f90(thisPtr);
    FUN_009f0190();
  }
  return;
}