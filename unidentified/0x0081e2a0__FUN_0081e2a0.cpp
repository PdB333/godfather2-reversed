// FUNC_NAME: SomeClass::checkAndProcessSomething
void __fastcall SomeClass::checkAndProcessSomething(int thisPtr)
{
  // Check if field at offset +0xF0 is non-zero (likely a flag or pointer)
  if (*(int *)(thisPtr + 0xf0) != 0) {
    // Call two functions when condition is met
    FUN_004df710();  // Likely some processing or update function
    FUN_00939960();  // Another processing or cleanup function
    return;
  }
  return;
}