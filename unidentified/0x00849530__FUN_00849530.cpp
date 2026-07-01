// FUNC_NAME: SomeClass::getOrCreateSomething
int __fastcall SomeClass::getOrCreateSomething(int thisPtr)
{
  // Check if the pointer at offset +0x70 is null
  if (*(int *)(thisPtr + 0x70) == 0) {
    // If null, call a function to create/initialize something
    // Parameters: value at +0x54, and address of +0x6c
    FUN_00603330(*(undefined4 *)(thisPtr + 0x54), thisPtr + 0x6c);
  }
  // Return the address of the field at +0x6c
  return thisPtr + 0x6c;
}