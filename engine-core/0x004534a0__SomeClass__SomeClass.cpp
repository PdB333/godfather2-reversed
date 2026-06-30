// FUNC_NAME: SomeClass::SomeClass

int __thiscall SomeClass::SomeClass(int thisPtr, byte flag)
{
  // Set virtual function table at offset 0x28 (likely a second vtable or interface pointer)
  *(undefined ***)(thisPtr + 0x28) = &PTR_LAB_00e317cc;

  // Call base class constructor (FUN_004530e0)
  FUN_004530e0();

  // If flag bit 0 is set, call additional cleanup/registration function (FUN_009c8eb0)
  if ((flag & 1) != 0) {
    FUN_009c8eb0(thisPtr);
  }

  return thisPtr;
}