// FUNC_NAME: SomeClass::getSomeProperty
uint __fastcall SomeClass::getSomeProperty(int thisPtr)
{
  uint result;
  
  // Check if the pointer at offset +0x5F4 is non-null
  if (*(int *)(thisPtr + 0x5f4) != 0) {
    // Call a virtual function at vtable offset 0x38 (index 14) on the object pointed to by +0x5F4
    // This is likely a method that returns a uint
    result = (**(code (__thiscall **)(int))(**(int **)(thisPtr + 0x5f4) + 0x38))(*(int *)(thisPtr + 0x5f4));
    return result;
  }
  
  // If the pointer is null, return the low byte of EAX masked with 0xFFFFFF00
  // This is likely an error/fallback case
  return in_EAX & 0xffffff00;
}