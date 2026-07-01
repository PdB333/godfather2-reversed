// FUNC_NAME: SomeClass::incrementAndReturnCounter
undefined4 __fastcall incrementAndReturnCounter(int thisPtr)
{
  // Increment counter at offset 0x1c and return the new value
  *(int *)(thisPtr + 0x1c) = *(int *)(thisPtr + 0x1c) + 1;
  return *(undefined4 *)(thisPtr + 0x1c);
}