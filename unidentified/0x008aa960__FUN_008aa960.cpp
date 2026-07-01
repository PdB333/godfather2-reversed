// FUNC_NAME: SomeClass::getOrCreateSomeMember
int __fastcall SomeClass::getOrCreateSomeMember(int thisPtr)
{
  // Check if the member at offset +0x170 is null (likely a pointer to a sub-object)
  if (*(int *)(thisPtr + 0x170) == 0) {
    // If null, call a function to initialize/create it, passing the value at +0x180 and the address of +0x16c
    // +0x180 might be a size or configuration parameter, +0x16c is likely a handle or ID
    FUN_00603330(*(undefined4 *)(thisPtr + 0x180), thisPtr + 0x16c);
  }
  // Return the address of the member at +0x16c (likely a handle or reference to the sub-object)
  return thisPtr + 0x16c;
}