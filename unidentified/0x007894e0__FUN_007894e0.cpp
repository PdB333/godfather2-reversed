// FUNC_NAME: SomeClass::resetOrClearMethod
void __fastcall SomeClass::resetOrClearMethod(int thisPtr)
{
  int iVar1;
  
  // Clear bit 0 of flags at offset 0x50 (likely a status/flags field)
  *(uint *)(thisPtr + 0x50) = *(uint *)(thisPtr + 0x50) & 0xfffffffe;
  
  // Call FUN_004df6e0 twice (likely a sleep or yield function)
  iVar1 = 2;
  do {
    FUN_004df6e0();
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  
  return;
}