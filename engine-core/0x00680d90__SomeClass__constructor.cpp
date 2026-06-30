// FUNC_NAME: SomeClass::constructor
int __thiscall SomeClass::constructor(int thisPtr, byte flags)
{
  undefined4 *vtablePtr;
  
  if (thisPtr == 0) {
    vtablePtr = (undefined4 *)0x0;
  }
  else {
    vtablePtr = (undefined4 *)(thisPtr + 0x20); // +0x20: vtable pointer offset
  }
  *vtablePtr = &PTR_LAB_00d580e8; // Set vtable to class-specific table
  DAT_011298f4 = 0; // Reset global flag
  FUN_007edfb0(); // Call base class or initialization function
  if ((flags & 1) != 0) {
    FUN_009c8eb0(thisPtr); // Call destructor or cleanup if flag set
  }
  return thisPtr;
}