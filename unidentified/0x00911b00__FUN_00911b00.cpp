// FUNC_NAME: SomeClass::resetOrClearMethod
void __fastcall SomeClass::resetOrClearMethod(int *thisPtr)
{
  *(byte *)(thisPtr + 0x14) = 0; // +0x14: some flag/byte field
  if (*(byte *)(thisPtr + 0x12) == '\0') { // +0x12: another flag/byte field
    (**(code **)(*thisPtr + 0x28))(); // call virtual function at vtable+0x28
    FUN_005c0d50(thisPtr + 5, &LAB_00911ae0, 0); // call helper with offset 5 (likely a sub-object)
  }
}