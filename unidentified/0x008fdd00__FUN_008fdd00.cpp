// FUNC_NAME: SomeClass::releaseOrDecrementRefCount
void __fastcall SomeClass::releaseOrDecrementRefCount(int thisPtr)
{
  // Clear bit 1 (0x2) of the flags at offset +0xD0
  *(ushort *)(thisPtr + 0xD0) = *(ushort *)(thisPtr + 0xD0) & 0xFFFD;
  
  // Call some function with a global/static data pointer (likely a mutex or reference counter manager)
  FUN_004086d0(&DAT_012069c4);
  
  // Decrement reference count at offset +0xD4
  *(int *)(thisPtr + 0xD4) = *(int *)(thisPtr + 0xD4) + -1;
}