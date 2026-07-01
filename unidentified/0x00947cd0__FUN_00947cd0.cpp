// FUNC_NAME: SomeClass::constructor
int __thiscall SomeClass::constructor(int thisPtr, byte flags)
{
  // Set vtable pointer to class's virtual function table
  *(undefined ***)(thisPtr + 0x18) = &PTR_LAB_00e355fc;
  
  // Call base class constructor or initialization function
  FUN_0064d150();
  
  // If flag bit 0 is set, call additional initialization
  if ((flags & 1) != 0) {
    FUN_009c8eb0(thisPtr);
  }
  
  return thisPtr;
}