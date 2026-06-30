// FUNC_NAME: SomeClass::incrementCounter
void __fastcall SomeClass::incrementCounter(int thisPtr)
{
  if ((thisPtr != 0) && ((*(byte *)(thisPtr + 0x13) & 1) != 0)) {
    // +0x2d4: counter field, masked with global limit
    *(uint *)(thisPtr + 0x2d4) = *(int *)(thisPtr + 0x2d4) + 1U & DAT_010c2678;
    return;
  }
  // Global fallback counter
  DAT_012054b4 = DAT_012054b4 + 1;
  return;
}