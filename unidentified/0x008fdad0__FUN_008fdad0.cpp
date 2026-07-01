// FUNC_NAME: SomeClass::decrementRefCountOrRelease
void __fastcall decrementRefCountOrRelease(int thisPtr)
{
  FUN_004086d0(&DAT_012069c4); // likely a mutex lock or reference counting helper
  *(int *)(thisPtr + 0xd4) = *(int *)(thisPtr + 0xd4) - 1; // decrement reference count at +0xd4
  return;
}