// FUNC_NAME: SomeClass::getSomeField
undefined4 __fastcall SomeClass::getSomeField(int *thisPtr)
{
  // Dereference the vtable pointer (first member) and return the value at offset 0x30 from the vtable.
  // This is likely a virtual function table lookup, returning a function pointer or some data stored in the vtable.
  return *(undefined4 *)(*thisPtr + 0x30);
}