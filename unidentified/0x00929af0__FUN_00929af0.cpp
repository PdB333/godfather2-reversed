// FUNC_NAME: SomeClass::resetState
void __fastcall SomeClass::resetState(int *thisPtr)
{
  if ((char)thisPtr[0x12] == '\0') {
    // Reset state fields when the flag at offset 0x48 is clear
    thisPtr[0x15] = 0;   // +0x54
    thisPtr[0x16] = 0;   // +0x58
    thisPtr[0x17] = 0;   // +0x5C
    *(undefined1 *)(thisPtr + 0x14) = 0;  // +0x50
    *(undefined1 *)((int)thisPtr + 0x51) = 0;  // +0x51
    // Call virtual function at vtable+0x28 (likely a reset/initialize method)
    (**(code **)(*thisPtr + 0x28))();
    return;
  }
  return;
}